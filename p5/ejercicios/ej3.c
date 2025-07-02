/*
Una tecla posee un único registro de E/S : BTN_STATUS. Solo el bit menos significativo y el segundo bit menos significativo son de interés:
    - BTN_STATUS0: vale 0 si la tecla no fue pulsada, 1 si fue pulsada.
    - BTN_STATUS1: escribir 0 en este bit para limpiar la memoria de la tecla.
Escribir un driver para manejar este dispositivo de E/S. El driver debe retornar la constante BTN_PRESSED cuando se presiona la tecla. Usar busy waiting.
*/

// cuando hagamos un read lo tenemos que dejar tildado hasta que se toque la tecla

extern int BTN_STATUS;
extern int BTN_PRESSED;
extern int IO_OK;
typedef semaphore;

semaphore mutex;

int driver_init() {
    sema_init(&mutex,1);
    return IO_OK;
}

int driver_open(void) {
    return IO_OK;
}

int driver_close(void) {
    return IO_OK;
}

// cuando llegamos a leer activamos zona critica
int driver_read(int *udata) {
    sema_wait(&mutex);

    int status;

    // mientras el bit de status sea distinto de 1
    while ((status = IN(BTN_STATUS) & 1) !=1)
    {
        // a esperar que hagan algo
    }
    
    // tocaron la tecla --> mandamos la constante
    int constante = BTN_PRESSED;
    copy_to_user(udata, &constante, sizeof(constante));

    //reseteamos el registro --> le escribimos con out, ponemos los bits en 0 
    OUT(BTN_STATUS, 0x0);
    
    sema_signal(&mutex);

    return IO_OK;
}


int driver_write(int *data) {
    return IO_OK;
}

int driver_remove() {
    return IO_OK;
}
