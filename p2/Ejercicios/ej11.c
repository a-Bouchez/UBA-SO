/*
    Considere un algoritmo de scheduling que favorece a aquellos procesos que han usado la menor cantidad de tiempo de procesador en el pasado reciente.
    ¿Explique por qué favorecería a los procesos que realizan muchas E/S, pero a la vez no dejaría a los intensivos en CPU en starvation?

        Podemos usar un algoritmo de scheduling tipo multilevel feedback queue donde premiamos a aquellos que no usan la totalidad de su quantum y 
        castigamos a aquellos que si lo hagan. Cómo? La idea es meter a todos en la cola de mayor prioridad y mantenerlos en esta sii no usan todo
        el quantum, encambio aquellos procesos que si lo hagan van a bajar a otra cola de menor prioridad. Si por alguna razon los procesos van 
        cambiando cuanto usan de CPU lo que podemos hacer es poner cada vez quantums más grandes y si no lo usan todo los subimos.

        De esta manera los procesos que realizan mucha E/S por lo general no utilizan todo su quantum y por lo tanto no son desalojados, menteniendo su
        prioridad original.

        Por otro lado los procesos intensivos en CPU por lo general utilizan todo su quantum y son desalojados por el scheduler, bajando su prioridad 
        hasta llegar a la más baja. No obstante debido al aging, si no logran obtener el CPU porque hay muchos procesos con prioridad más alta, van a ir
        aumentando su prioridad hasta eventualmente obtener su turno para ejecutar en el CPU. Por esto es que no habría starvation.
*/