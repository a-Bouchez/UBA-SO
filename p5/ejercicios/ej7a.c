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
*/

extern int DOR_IO;
extern int ARM;
extern int SEEK_SECTOR;
extern int DOR_STATUS;
extern int ARM_STATUS;
extern int DATA_READY;
extern int IO_OK;
typedef semaphore;

semaphore mutex;

int driver_init() {
    sema_init(&mutex,1);
    return IO_OK;
}


int driver_close() {
    return IO_OK;
}

// nos dicen que no usemos interrupciones --> busy waiting
int driver_write(int sector, void *data) {
    sema_wait(&mutex);
    // antes de escribir en un sector hay que fijarse si el motor esta prendido o no
    int engine_status;

    // prendemos el motor y esperemos por las dudas para que se pueda escribir
    if ((engine_status = IN(DOR_STATUS)) == 0)
    {
        OUT(DOR_IO,1); // prendemos motor
        sleep(50);     // esperamos a que arranque
    }

    // seleccionamos la pista y el sector que se queire escribir 
    // a Que se refiere con formato LBA? que nos van a romper las bolas si me pasan algun numero voy a tener que iterar entre los sectores de las 
    // pistas para ver en cual cae
    int sectors_per_track = cantidad_sectores_por_pista();
    int track = sector / sectors_per_track;         // nos fijamos el numero entero en e l que cae
    int real_sector = sector % sectors_per_track;   // el resto es el sector

    OUT(ARM, track);
    OUT(SEEK_SECTOR, real_sector);

    // Toca escribir
    int arm_status;
    while ((arm_status= IN(ARM_STATUS)) != 1)
    {
        //se esta moviendo el brazo, toca esperar, se prodria hacer con un semáforo e interrupciones pero me dicen quen o
    }

    // entiendo que nos tenemos que fijar que este lista la data antes de escribir pero ni idea
    int data_status;
    while ((data_status=IN(DATA_READY)) == 0)
    {

    }
    
    // ME OLVIDÉ QUE NO PUEDO USAR LOS DATOS DIRECTAMENTE, LOS TENGO QUE COPIAR
    // estamos a lvl kernel ahora, los tengo que "traer"
    int ker_data;

    copy_from_usr(&ker_data,data,sizeof(data));

    //ahora si está todo para escribir
    escribir_datos(data);

    // terminamos de escribir --> apagamos el motor y lo mandamos a dormir para evitar otras operaciones
    // OUT(DOR_STATUS,0); --> esta linea estaba mal porque es un registro de lectura y estoy escribiendo
    OUT(DOR_IO,0);
    sleep(200);
    
    sema_signal(&mutex);
    return IO_OK;
}