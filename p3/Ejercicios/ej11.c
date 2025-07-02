/*
    simular la comunicación mediante pipes entre dos procesos usando las syscalls read() y
    write(), pero usando memoria compartida (sin usar file descriptors). Se puede pensar al pipe como
    si fuese un buffer de tamaño N, donde en cada posición se le puede escribir un cierto mensaje. El
    read() debe ser bloqueante en caso que no haya ningún mensaje y si el buffer está lleno, el write()
    también debe ser bloqueante. No puede haber condiciones de carrera y se puede suponer que el buffer
    tiene los siguientes métodos: pop() (saca el mensaje y lo desencola), push() (agrega un mensaje al
    buffer)

    int buffer[N];
    semaphore espacios_libres_buffer = N;
    semaphore hay_algo = 0;


    // solo bloquea cuando no tenemos más lugar para escribir
    // la idea va a ser poner un semáforo con el mismo valor que espacios en el buffer
    void write(int msg) {
        espacios_libres_buffer.wait();
        buffer.push(msg);
        hay_algo.signal();
    }

    // se bloquea si no tengo nada para leer pero no entiendo porque quieren que se bloquee si está lleno el buffer
    int read() {
        hay_algo.wait();

        // esta mierda se bloquea si está lleno pero para qué?
        espacios_libres_buffer.wait();
        espacios_libres_buffer.signal();

        int msg = buffer.pop()
        espacios_libres_buffer.signal();
        return msg;
    }
    
*/