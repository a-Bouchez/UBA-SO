/*
Reescribir el driver del ejercicio anterior para que utilice interrupciones en lugar de busy waiting.
Para ello, aprovechar que la tecla ha sido conectada a la línea de interrupción número 7.
Para indicar al dispositivo que debe efectuar una nueva interrupción al detectar una nueva pulsación
de la tecla, debe guardar la constante BTN_INT en el registro de la tecla.
*/

// la idea es hacer un semáforo que hada de while hasta que llegue la interrupción

extern int BTN_STATUS;
extern int BTN_PRESSED;
extern int IO_OK;
extern int LINEA_INT_7;
extern int BTN_INT;
typedef semaphore;

semaphore mutex;
semaphore not_busy_waiting;

// inicializamos el nuevo semáforo y el handler de la interrupción
int driver_init() {
    sema_init(&mutex,1);
    sema_init(&not_busy_waiting,0);
    irq_register(LINEA_INT_7, handler); // me inicializa el handler y lo linkea con la señal 7
    return IO_OK;
}

// me dijeron por la cucaracha que comparar el IN con BTN_INT está mal ya que solo nos importa ver si esta en 1 el bit ( cuando mandamos la cons se pone en1)
void handler(int signal) {
    int status = IN(BTN_STATUS); // lo hice por las dudas pero hace falta? si tocan directo el botón ya está no?
    if ((status & 0x1) == 1) {
        sema_signal(&not_busy_waiting);
    }
}

// cuando llegamos a leer activamos zona critica
int driver_read(int *udata) {
    sema_wait(&mutex);

    // habilitamos las interrupciones para que puedan tocar la tecla --> mandamos contante al regristro
    OUT(BTN_STATUS, BTN_INT);

    // mi nuevo while
    sema_wait(&not_busy_waiting);
    
    // tocaron la tecla --> mandamos la constante
    int constante = BTN_PRESSED;
    copy_to_user(udata, &constante, sizeof(constante));
    
    sema_signal(&mutex);

    return IO_OK;
}

int driver_remove() {
    free_irq(LINEA_INT_7); // liberamos la señal/ deslinkeamos el handler
    return IO_OK;
}