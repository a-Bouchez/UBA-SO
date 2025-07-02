/*
    no pienso copiar el enunciado

    - 3 jeugos distintos a la vez y 3 personas a la vez 
    - 3 visores que muestran datos
    - También permite activar, desactivar y remapear teclas, y configurar macros, para cada usuario por separado.
    - luces gamer configurables
    - cuando tocan tecla --> IRQ_KEYB iterrupcion y mete en el registro KEYB_REG_DATA un int de 34 bits con los 14 bits menos significativos el 
      código KEYCODE correspondiente a la tecla presionada, y en los 2 bits siguientes un identificador P, que vale 0 cuando la tecla debe ser recibida
      por todas las aplicaciones conectadas, y en caso contrario un número entre 1 y 3 que indica a qué aplicación está destinada esa tecla. 
    - no debe bloquearse ni quedarse esperando
    - informamos de que hicimos todo esto READ_OK en el registro KEYB_REG_CONTROL cc READ_FAILED
    - 3 dirs de memo INPUT_MEM_0, INPUT_MEM_1, INPUT_MEM_2, siendo cada una un arreglo de 100 bytes desde los que el dispositivo leerá el input de las 
      aplicaciones. mapearlas en el init a input_mem
    - APP_UP en el registro KEYB_REG_STATUS y id a KEYB_REG_AUX cuando se conecta app


    char input_mem[3][100];
    char buffer_lectura[3][1000];
    atomic_int buffer_start[3];
    atomic_int buffer_end[3];
    boolean procesos_activos[3];

    semaphore open&close_mutex;

    void keyb_handler {

    }

    void driver_load() {
        // Se corre al cargar el driver al kernel.
        req_irq(IRQ_KEYB, keyb_handler)
        sema_init(&open&close_mutex,1)
        for i in range(3):
            mem_map(INPUT_MEM[i],input_mem[i],100)
    }

    void driver_unload() {
        // Se corre al eliminar el driver del kernel.
        free_irq(IRQ_KEYB)
        for i in range(3):
            mem_unmap(input_mem[i])
    }

    int driver_open() {
        // Debe conectar un proceso, asignandole un ID y retornandolo,
        // o retornando -1 en caso de falla.
        sema_wait(open&close_mutex)
        int id = -1
        for i in range(3):
            if (proceso_act[i] == false)
                procesos_act[i] = true
                id = i
                break

        if (id == -1) 
            return IO_ERROR

        OUT(KEYB_REG_STATUS, APP_UP)
        OUT(KEYB_REG_AUX, id)

        sema_signal(open_mutex,1)
        return id
    }

    void driver_close(int id) {
        // Debe desconectar un proceso dado por parametro.
        sema_wait(open&close_mutex)
        procesos_act[id] = false
        OUT(KEYB_REG_STATUS,APP_DOWN)
        sema_signal(open$close_mutex)
    }

    int driver_read(int id, char* buffer, int length) {
        // Debe leer los bytes solicitados por el proceso ’’id’’
        while(get_buffer_length(id) < length) {};

        copy_from_buffer(id, buffer, length);

        buffer_start[id] += length;

        return length
    }

    int driver_write(char* input, int size, int proceso) {
        copy_from_user(input_mem[proceso], input, size);
        return size;
    }
*/