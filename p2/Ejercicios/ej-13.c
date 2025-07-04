/*
    - FIFO:

        Desfavorece a los procesos más cortos porque sin importar la ráfaga de CPU de los procesos en ready, siempre se turnan en orden FIFO para utilizar
        el CPU. Podría pasar que haya un proceso con ráfagas cortas porque realiza mucha E/S junto a muchos otros procesos intensivos en CPU. Debido a que
        se turnan en orden FIFO para utilizar el CPU, el proceso corto siempre va a tener que esperar que se ejecuten todos los otros hasta obtener el CPU,
        para luego bloquearse rápidamente. Cuando vuelve a estar en ready tiene que esperar a todos los procesos intensivos otra vez.

    - Round-robin:

        Con una buena duración del quantum se puede lograr un uso justo del CPU. Es mejor que el orden FIFO ya que se limita el tiempo que utilizan el CPU
        los procesos intensivos, llegando así el turno de los procesos cortos de manera más rápida. No obstante se puede dar la situación en donde hay 
        demasiados procesos y los procesos cortos tienen que esperar bastante para obtener el CPU. Si se utiliza un quantum demasiado largo el algoritmo 
        round-robin se degrada a una FIFO.

    - Multilevel feedback queue:

        Éste algoritmo es el que logra el mayor nivel de justicia entre los distintos procesos. Así que podríamos decir que favorecen a los procesos más
        cortos. Los procesos con ráfagas cortas puede mantener una prioridad alta y obtener así el CPU de manera más rápida cuando se desbloquean.
        Cuando no hay procesos cortos se le da prioridad a los procesos más largos, que tienen una prioridad más baja ya que generalmente utilizan todo 
        su quantum y son desalojados por el scheduler. Gracias al aging, los procesos más largos evitan tener starvation ya que si pasan demasiado tiempo
        sin obtener el CPU el algoritmo se encarga de subirles las prioridad.

*/