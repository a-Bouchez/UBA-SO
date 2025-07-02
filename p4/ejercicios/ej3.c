/*
Qué es la paginación a demanda? 

    - En lugar de cargar el programa entero en memoria física para poder ejecutarlo, cargar sólo las páginas que son necesarias en cada momento.

Datos del sistema:

    - Uso de CPU: 20 %.
    - El sistema hace thrashing.
    - Uso del resto de los dispositivos de E/S: 10 %.

Indicar si es probable o no que mejore la utilización de la CPU.

    a) Instalar una CPU más rápida 

        No, como mucho va a disminuir. Como el CPU está lejos de estar saturado, tener uno más rápido es probable que no mejore la utilización del mismo.
    
    b) Instalar un disco de paginado más grande.

        Podemos ver que el sistema hace thrashing y eso es debido al tamaño total de la memoria, no del disco de paginación (recordemos que trashing
        es cuando no dejamos de bajar y de subir cosas del disco a la memoria para poder alocar todos los procesos y gastamos más tiempo en eso que 
        en ejcutar los procesos). Por lo que aumentar el tamaño del disco de paginido no cambia nada. 

    c) Incrementar el grado de multiprogramación.

        Entiendo que mas multiprogramación significa más procesos/programas. Si no tuvieramos thrashing nos mejoraría la utilización del CPU pero en este
        caso NO. Tenemos problemas de thrashing y estamos agregando más programas por lo que básicamente estamos agragando más problemas. 

    d) Disminuir el grado de multiprogramación.

        Masterclass. Sacamos programas y nos sacamos problemas. El cpu se va a utilizar más y vamos a gastar menos tiempo en subir y bajar páginas 
        del disco. Al disminuir la cantidad de programas/procesos nos va a disminuir el problema de thrashing. 

    e) Instalar más memoria principal.

        Masterclass2, recordemos que el problema de thrashing viene de tener poca memoria y muchos procesos, si aumentamos el tamaño de la memoria 
        vamos a tener más páginas disponibles para asignarle a los programas. De esta manera los programas no necesitan competir tanto por la utilización
        de la memoria principal y así debería disminuir el thrashing, liberando a los procesos para usar el CPU.

    f) Instalar un disco más rápido.

        Depende de donde tengamos el swapp, supongo que en este disco nuevo. Va a mejorar un poco ya que va a ser más rápida la subida y bajada de las 
        páginas al disco así que va a aumentar un poco el uso del CPU pero no tanto ya que el problema de thrashing se mantiene.

    g) Incrementar el tamaño de página

        Me mataste, es un depende acá. No queda claro si aumentaría la utilización del CPU. Puede pasar que disminuya el thrashing pero como las páginas 
        son más grandes se requiere más tiempo para cargar y descargarlas.

    h) Incrementar la velocidad del bus de E/S.

        El uso de E/S es del 10%, es bastante bajo. Me parece que no aumentaría mucho.
*/