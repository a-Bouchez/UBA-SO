/*
¿Cuáles de los siguientes algoritmos de scheduling pueden resultar en starvation (inanición) y en qué condiciones?

    a) Round-robin.
        No puede haber starvation ya que se asigna el CPU a todos los procesos en orden FIFO, y además si algún proceso utiliza todo su quantum (o time slice), el algoritmo desaloja ese proceso y 
        da lugar al siguiente. De esta forma todos obtienen su turno para usar el CPU sin importar si son procesos intensivos en CPU o en E/S.

    b) Por prioridad.
        Si nos llegan todos procesos de alta prioridad y tenemos algunos que no lo son vamos a tener starvation, se puede prevenir usando aging en esos proceso para que luego de un tiempo 
        aunmente la prioridad de todos los procesos que llevan mucho tiempo esperando (aging).

    c) SJF.
        Al igual que el anterior, si nos llegan muuuuuchos procesos cortos y uno largo, este va a esperar a qeu se ejecuten todos los cortos primero --> starvation (no le toca nunca)
        Es un caso particular del algoritmo por prioridad, en donde la prioridad de un proceso se define como la duración de la próxima ráfaga de CPU. Una ráfaga más corta significa mayor prioridad.

    d) SRTF.
        Peor que el anterior. En este si nos llega una con menor tiempo que la que se esta ejecutando actualmente, se corta la ejecucuion y se salta a ese nuevo proceso
        es básicamente SJF pero con desalojo.

    e) FIFO.
        No puede haber starvation pero se puede producir un efecto "convoy" en donde un proceso con ráfagas intensivas de CPU acapara el uso del mismo por largos períodos de tiempo, y cuando 
        finalmente lo libera, los otros procesos con ráfagas cortas (por ejemplo porque son procesos intensivos en E/S) solo lo usan por un breve período hasta que nuevamente el proceso intensivo 
        acapara el CPU.

    f) Colas de multinivel.
        como las colas de mayor prioridad dominan a las otras si nos llegan procesos para la cola mas prioritaria vamos a tener starvation.
        Si bien ahora hay una cola FIFO por cada nivel de prioridad, si siempre hay procesos ready en la FIFO de nivel N, entonces ningún proceso de nivel > N va a obtener el CPU. No obstante, 
        todos los procesos con misma prioridad ahora tienen garantizado el CPU en algún momento.

    g) Colas de multinivel con feedback (aging).
       No puede haber starvation gracias al feedback / aging. Los procesos de baja prioridad que están siendo bloqueados constantemente por los procesos de prioridad más alta eventualmente 
       van a subir de prioridad hasta entrar en la misma FIFO que esos procesos que lo estaban bloqueado.
*/