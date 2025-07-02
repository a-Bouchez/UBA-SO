/*
Considere una modificación a round-robin en la que un mismo proceso puede estar encolado varias
veces en la lista de procesos ready. Por ejemplo, en un RR normal se tendrían en la cola ready a
P1,P2,P3,P4, con esta modificación se podría tener P1,P1,P2,P1,P3,P1,P4.

    a) ¿Qué impacto tendría esta modificación?

        En esta modificacion "rompe" el invariante de que cada  proceso tenga el mismo tiempo del cpu disponible. Por un lado se pueden terminar procesos mas largos si llegan a tener 
        el cpu por mas de quantum pero por el otro no se le esta dando mas prioridad a un proceso que otro ya que no le asegura ejecutarse primero por tenr mas aparaciones.

    b) Dar ventajas y desventajas de este esquema. Piense en el efecto logrado, no en la forma de implementarlo.

        Bueno esto es mas o menos el anterior:

            - Ventajas
                ° Los procesos con mayor tiempo de ejecucion o mas intensivos de CPU tienen mas tiempo del CPU para terminar sus ejecuciones.
                ° Podemos asegurar la ejecución frecuente de algún proceso a pesar de haber muchos procesos en ready si lo intercalamos varias veces en la FIFO.

            - Desventajas:
                ° Renunciamos al invariante del algoritmo RR de otorgar el uso justo del CPU a cada proceso
                ° Nos puede pasar como en las colas FCFS y tener un efecto convoy si le ponemos repetidas veces el mismo proceso si es muy largo
                ° Ocupamos mas espacio en memo si tenemos varias copias de un proceso

    c) ¿Se le ocurre alguna otra modificación para mantener las ventajas sin tener que duplicar las entradas en la lista de procesos ready?

        la verdad que no se me ocurre asi que voy a poner lo que hizo yago y lo intento explicar


        En vez de repetir el proceso en la FIFO, se configura la cantidad de quanta que le toca. Esto solo modela repeticiones contínuas.
        Cada proceso tiene configurado un entero que indica la cantidad de procesos que se saltea cuando es insertado al final de la FIFO. Por defecto los procesos tienen esta configuración en
        0 para replicar el comportamiento normal de una FIFO (los procesos se encolan al final). Cualquier proceso que tenga esta configuración > 0 va a ejecutarse más frecuentemente respecto 
        al resto, pues se está "salteando" posiciones en la FIFO.

        Basicamente cada Proceso va a tener un contador que nos dice cuantas veces lo adelantamos en la cola cuando termina de ejecutarse. 
        Es un RR con "peso" donde le estamos dando mas prioridad a un proceso sobre el resto asegurandonos que en el medio se ejecuten los otros durante un quantum
        Una mezcla entre RR y prioridad pero evita aging y, por ende, starvation. Ademas no guarda mas copias del proceso asi que es mas eficiente en memoria.

*/ 