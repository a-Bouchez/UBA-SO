/*
COmo me austo cada vez que leo demostrar.

Veamos primero algunas definiciones:

    wait(s): 
        while (s<=0) 
            dormir(); 
        s- -;

    signal(s):
        s++; 
        if (alguien espera por s):
            despertar a alguno;

    Operacion atomica: 
        Una operacion es atomica cuando es indivisible. Es decir, cuando no puede ser interrumpida por el procesador hasta terminar.

    Propiedad de exclusión mutua:
        Un recurso no puede estar asignado a más de un proceso

DEMO:

    Suponinedo que la operacion wait() no es atomica nos permite ver que esta puede ser desalojada en cualquier lugar de su ejecucion. 

    QVQ se mantiene la propiedad de exclusión mutua suponinedo que el wait no es atomico.

    Sea P un programa que corre 2 procesos en paralelo, sean p1 y p2 procesos y sea mutex un semafoto tenemos entonces un programa con 2 procesos que tienen esta pinta:
        
        no_crit()       // parte no critica
        mutex.wait()    // avisamos que nos metemos en la seccion critica y pedimos que no nos desalojen hasta que termine
        crit()          // parte critica
        mutex.signal()  // termine de usar todo
        no_crit()       // mas parte no criticas

    Recordemos que mutex es un semaforo inicializado en 1 y que wait lo que hace es ponerlo en 0 para avisarle la resto de procesos que no pueden ejecutar su codigo critico

    supongamos la siguente ejecucion de los procesos a partir de qeu ambos terminan su primer segemnto no critico.

        GLOBAL: 
            mutex = 1

        P1:
            while (s<=0) // mutex es 1 asi que no se mete
                dormir()
        ---- Desalojado ----

        P2: 
            while (s<=0) // mutex es 1 asi que no se mete
                dormir()
            mutex--
            crit()
            .
            .
            .
        --- Desalojado ----

        Global:
            mutex=0 // no se puede ejecutar codigo critico

        P1:
            mutex --
            crit()
            .
            .
            .
        --- Desalojado ----

En este caso podemos ver la ejecucion simultanea de la tareas criticas [crit()] de cada uno de los procesos, salteandose la funcion del semaforo y violando la propiedad de exclusión mutua. 
Llegamos una contradiccion, es decir, un absurdo ya que suponiamos verdadero a propiedad de exclusión mutua con el wait no es atomico. EL absurdo proviene de  creer que el wait puede 
no ser atomico.

para resunir el codigo:
    Como el semáforo MUTEX se inicializó en 1, cuando el proceso P1 revisa while (s <= 0) la condición es falsa y por lo tanto no hace dormir. Al ser desalojado antes de ejecutar mutex--, 
    el semáforo compartido sigue valiendo 1.

    Cuando se ejecuta el proceso P2, s.wait no bloquea y P2 comienza a ejecutar su tarea_crítica.

    Ahí es desalojado y vuelve el proceso P1, que ya pasó la guarda del while. P1 decrementa nuevamente el semáforo, sale del llamado a mutex.wait8() y también comienza a ejecutar su tarea_crítica.

    Esto fue posible por no garantizar que wait sea atómico.
*/