/*
Un cronómetro posee 2 registros de E/S:

    CHRONO_CURRENT_TIME que permite leer el tiempo medido,
    CHRONO_CTRL que permite ordenar al dispositivo que reinicie el contador.
    
El cronómetro reinicia su contador escribiendo la constante CHRONO_RESET en el registro de control.
Escribir un driver para manejar este cronómetro. Este driver debe devolver el tiempo actual cuando invoca la operación read(). Si el usuario invoca 
la operación write(), el cronómetro debe reiniciarse.
*/

extern int CHRONO_CURRENT_TIME;
extern int CHRONO_CTRL;
extern int CHRONO_RESET;
extern int IO_OK;
typedef semaphore;

semaphore mutex;

// como tenemos que fiajrnos que no se escriba al mismo tiempo que leemos vamos a necesitar un semaforo, acá inicializamos todas las variables que usamos
int driver_init() {
    sem_init(&mutex,1);
    return IO_OK;
}

int driver_exit() {
    sem_destroy(&mutex);
    return IO_OK;
}

// entiendo que data es como mandarle al usuario
int driver_read(int *data) {
    // entramos en zona critica
    mutex.wait();

    //leemos el registro para saber el tiempo actual
    int tiempo_act = IN(CHRONO_CURRENT_TIME);
    
    //le mandamos al usuario la data
    copy_to_user(data,&tiempo_act, sizeof(tiempo_act));

    //salimos de la zona critica
    mutex.signal();
    return IO_OK;
}


int driver_write(int *data) {
    // entramos en zona critica
    mutex.wait();

    // le mandamos el mensaje de reset al controlador para que lo ponga en 0
    OUT(CHRONO_CTRL, CHRONO_RESET);
    
    //salimos de zona critica
    mutex.signal();
    return IO_OK;
}