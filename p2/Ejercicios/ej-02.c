/*
    Ejercicio 2:
    Sean P0, P1 y P2 tales que:
        - P0 tiene ráfagas cortas de E/S a ciertos dispositivos.
        - P1 frecuentemente se bloquea leyendo de la red.
        - P2 tiene ráfagas prolongadas de alto consumo de CPU y luego de escritura a disco.

    a) ¿Conviene usar un algoritmo Round-Robin? ¿Uno de Prioridades? Justifique su respuesta.

    ▸ Resumen del algoritmo Round-Robin (RR):

        - El scheduler recorre la cola de procesos en estado ready y asigna la CPU por turnos (quantum fijo).
        - Si un proceso termina su ráfaga o se bloquea (por I/O) antes de agotar su quantum, libera la CPU voluntariamente.
        - Si no termina, el scheduler lo desaloja y lo pone al final de la cola ready.
        - Favorece la equidad y evita starvation, pero puede generar overhead si el quantum es mal elegido.

    ▸ Resumen del algoritmo de Prioridades:

        - A cada proceso se le asigna una prioridad.
        - El scheduler siempre ejecuta el proceso ready con mayor prioridad.
        - Si varios procesos tienen la misma prioridad, se aplica FIFO.
        - Puede producir starvation si siempre hay procesos de alta prioridad y no se implementa un mecanismo de aging.

    ▸ Análisis del caso:

        - Round-Robin garantiza equidad y un *waiting time* acotado (máximo un quantum), incluso para procesos como P2 con ráfagas largas.
          Además, procesos I/O-bound como P0 y P1 probablemente liberen la CPU antes de agotar su quantum.  P2 aprovecha todo su quantum mientras 
          realiza sus ráfagas intensivas de CPU. Si P2 tiene el CPU y los otros procesos pasan a ready, a lo sumo tendrán que esperar 1 quantum para obtener el CPU.
          (Hay qu fijar bien el tiempo del quantum para que ni dure mucho y se parezca a un fcfs ni dure poco para que gastemos mas tiempo en los context switchs)

        - Con Prioridades preemptivas, si asignamos mayor prioridad a procesos interactivos (P0 y P1) y menor a P2 (CPU-bound),
          se logra mejorar el *response time* para los I/O-bound. Pero puede darse **starvation** para P2 si no se implementa un 
          mecanismo de **aging**, que aumente su prioridad conforme espera.

    En conclusión, ambos algoritmos tienen pros y contras.
    Round-Robin sería más simple y evita starvation, mientras que Prioridades con preemption y aging ofrece mejor rendimiento interactivo.

    Segun los resueltos que vi nos quedamos con RR ya que se asume que no hay desalojo.
*/
