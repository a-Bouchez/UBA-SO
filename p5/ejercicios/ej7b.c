/*
    Se desea implementar el driver de una controladora de una vieja unidad de discos ópticos que requiere controlar manualmente el motor de la misma. 
    Esta controladora posee 3 registros de lectura y 3 de escritura. Los registros de escritura son:

        ° DOR_IO: enciende (escribiendo 1) o apaga (escribiendo 0) el motor de la unidad.

        ° ARM: número de pista a seleccionar.

        ° SEEK_SECTOR: número de sector a seleccionar dentro de la pista.

    Los registros de lectura son:

        ° DOR_STATUS: contiene el valor 0 si el motor está apagado (o en proceso de apagarse), 1 si está encendido. Un valor 1 en este registro no 
                      garantiza que la velocidad rotacional del motor sea la suficiente como para realizar exitosamente una operación en el disco.

        ° ARM_STATUS: contiene el valor 0 si el brazo se está moviendo, 1 si se ubica en la pista indicada en el registro ARM.

        ° DATA_READY: contiene el valor 1 cuando el dato ya fue enviado.

    Además, se cuenta con las siguientes funciones auxiliares (ya implementadas):

        ° int cantidad_sectores_por_pista(): Devuelve la cantidad de sectores por cada pista de disco. El sector 0 es el primer sector de la pista.

        ° void escribir_datos(void *src): Escribe los datos apuntados por src en el último sector seleccionado.

        ° void sleep(int ms): Espera durante ms milisegundos.

    Antes de escribir un sector, el driver debe asegurarse que el motor se encuentre encendido. Si no lo está, debe encenderlo, y para garantizar que
    la velocidad rotacional sea suficiente, debe esperar al menos 50 ms antes de realizar cualquier operación. A su vez, para conservar energía, una 
    vez que finalice una operación en el disco, el motor debe ser apagado. El proceso de apagado demora como máximo 200 ms, tiempo antes del cual no 
    es posible comenzar nuevas operaciones.

    a) Implementar la función write(int sector, void *data) del driver, que escriba los datos apuntados por data en el sector en 
       formato LBA indicado por sector. Para esta primera implementación, no usar interrupciones.

    b) Modificar la función del inciso anterior utilizando interrupciones. La controladora del disco realiza una interrupción en el IRQ 6 cada vez
       que los registros ARM_STATUS o DATA_READY toman el valor 1. Además, el sistema ofrece un timer que realiza una interrupción en el IRQ 7 una 
       vez cada 50 ms. Para este inciso, no se puede utilizar la función sleep.
*/

extern int DOR_IO;
extern int ARM;
extern int SEEK_SECTOR;
extern int DOR_STATUS;
extern int ARM_STATUS;
extern int DATA_READY;
extern int IO_OK;
extern int IRQ_6;
extern int IRQ_7;
typedef semaphore;
typedef atomic_int;

semaphore mutex;
semaphore arm_mutex;
semaphore data_mutex;
semaphore ready_4_writing;
semaphore sleep;
atomic_int timer_start = 0;
atomic_int timer = 0;

int driver_init() {
    sema_init(&mutex,1);
    sema_init(&arm_mutex,0);
    sema_init(&data_mutex,0);
    sema_init(&ready_4_writing,0);
    sema_init(&sleep,0);
    request_irq(IRQ_6,sig_6_handler);
    request_irq(IRQ_7,sig_7_handler);
    return IO_OK;
}

void sig_6_handler(int sig) {
    int arm_status;
    if ((arm_status = IN(ARM_STATUS)) == 1 )
    {
        sema_signal(&arm_mutex);
    } else {
        sema_signal(&data_mutex);
    }
}

void sig_7_handler(int sig) {
    if (timer_start == 1)
    {   
        atomic_inc(&timer);
        if (timer == 1)
        {
            sema_signal(&ready_4_writing);
        }
        
        if (timer == 5)
        {
            atomic_set(&timer,0);
            sema_signal(&sleep);
        }
        
    }
    
}

int driver_close() {
    free_irq(IRQ_6);
    free_irq(IRQ_7);
    return IO_OK;
}


int driver_write(int sector, void *data) {
    sema_wait(&mutex);

    int engine_status;

    
    if ((engine_status = IN(DOR_STATUS)) == 0)
    {
        OUT(DOR_IO,1); 
        atomic_inc(&timer_start);       // nos aseguramos de que arranque a contar después de prender el motor
        sema_wait(&ready_4_writing);    // en vez de dormir espera al semáforo
        atomic_set(&timer_start, 0);    // apagamos el timer
    }

    int sectors_per_track = cantidad_sectores_por_pista();
    int track = sector / sectors_per_track;         
    int real_sector = sector % sectors_per_track;   

    OUT(ARM, track);
    OUT(SEEK_SECTOR, real_sector);

    
    sema_wait(&arm_mutex);  // esperamos al semáfor que nos dice si está listo el brazo

    sema_wait(&data_mutex); // idem para el data ready

    int ker_data;
    copy_from_usr(&ker_data,data,sizeof(data));
    escribir_datos(data);

    OUT(DOR_IO,0);

    atomic_set(&timer_start,1);     // avisamos que recién apagamos el motor para arrancar a contar
    sema_wait(&sleep);              // pasaron los 200ms
    atomic_set(&timer_start, 0);    // apagamos el timer

    sema_signal(&mutex);
    return IO_OK;
}