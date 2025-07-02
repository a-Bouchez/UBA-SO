/*
Suponer que se tienen N procesos Pi, cada uno de los cuales ejecuta un conjunto de sentencias ai
y bi. ¿Cómo se pueden sincronizar estos procesos de manera tal que los bi se ejecuten después de que
se hayan ejecutado todos los ai?

Yo creo que si. por cada pi vamos a poner 2 semáforos uno para saber si terminamos los ai y otro para los b_i. La idea acá es que tengamos uan variable global de cuantas veces llegamos 
al primer semáforo, si es == N significa que todos hicieron su ai y podemos mandar signal para el semáforo de bi. 

Ahora, cómo manejamos este samáforo? --> usando lo que veníamos haciendo podemos meter un efecto cascada (o molinete del subte para los amigos) para que 
cuando se ejecute uno de los bi habilite a otro más, no nos importa que se ejecuten al mismo tiempo.

Código:

    mutex = sem(1)
    sem_bi = sem(0)
    cant_ai = 0

    P:
        ai()

        // acá no quiero cosas raras, aumenta la var tranquilo sin qeu te saque el scheduler
        // me parece que no hace falta igual pero yo lo pondría
        mutex.wait()

        cant_ai++
        if (cant_ai == N) {
            sem_bi.signal()
        }

        mutex.signal()

        sem_bi.wait()
        sem_bi.signal()

        bi()
*/