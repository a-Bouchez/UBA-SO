/*
mucha paja, lo hace el amigo.

Indicar las acciones que debe tomar el administrador de E/S:

    a) cuando se efectúa un open().

        1 - Validar la ruta y permisos

            ° Comprobar que el dispositivo existe (p. ej. /dev/tty0) y que el proceso tiene permiso de apertura (lectura/escritura según corresponda).

        2 - Resolver major/minor

            ° Traducir el nombre mnemónico del dispositivo a sus números major (tipo de dispositivo) y minor (instancia concreta).

        3 - Crear o actualizar la entrada en la tabla de archivos abiertos

            ° Asignar un file descriptor al proceso.

            ° Instanciar (o localizar) la estructura interna struct file o equivalente que llevará el offset, flags y puntero al driver.

        4 - Invocar al driver

            ° Llamar a driver_open() del módulo correspondiente.

            ° El driver puede inicializar hardware, reservar buffers, preparar interrupciones, etc.

        5 - Inicializar estado de usuario

            ° Dejar el offset de lectura/escritura en cero (o donde corresponda).

            ° Devolver al proceso el descriptor abierto (un entero ≥ 0) o un error (< 0) si algo falla.

    b) cuando se efectúa un write().
        1 - Verificar permisos y flags

            ° Asegurarse de que el descriptor está abierto en modo escritura.

        2 - Copiar datos al kernel

            ° Usar copy_from_user() para traer el buffer de usuario al espacio kernel, o simplemente pasar el puntero si el driver lo maneja.

        3 - Buffering y/o spooling

            ° Si el dispositivo usa buffering (block devices) o spooling (impresoras), encolar los datos en la estructura de buffer/cola del subsistema 
              de E/S.

        4 - Planificar la operación de E/S

            ° Insertar la petición en la cola del scheduler de disco (o del dispositivo), eligiendo el orden de atención (FCFS, SSTF, elevator, 
              prioridades, etc.).

            ° Si es un device de caracter sin buffering, puede invocar directamente al driver.

        5 - Invocar al driver

            ° Llamar a driver_write() con un puntero a los datos en kernel.

            ° El driver iniciará la transferencia (vía polling, interrupción o DMA) y devolverá cuando termine o, si es no‐bloqueante, podrá retornar 
              inmediatamente indicando “pendiente”.

        6 - Actualizar offset y contadores

            ° Ajustar en la struct file el nuevo offset (para block devices).

            ° Llevar contabilidad de bytes efectivamente escritos.

        7 - Devolver el control al proceso

            ° Retornar al usuario el número de bytes escritos (o un código de error) una vez que la operación haya concluido (o al menos, que los datos 
              hayan sido “entregados” al subsistema de E/S, en caso de escritura asíncrona).
*/