/*
a) queremos que salga ABC ABC ABC

    Tenemos 3 procesos y queremos que uno espere al otro por lo que camos a necesitar 3 semaforos

    Mutex es un semaforo sol ocon valor 0 y 1. Si no queremos valores binarios entonces usamos sem(valor inicial del semaforo)

    sem_A = sem(1)
    sem_B = sem(0)
    sem_C = sem(0)

    PA:
        while (true) {
            wait(sem_A)
            code()
            signal(sem_B)
        }

    PB:
        while (true) {
            wait(sem_B)
            code()
            signal(sem_C)
        }

    PC: 
        while (true) {
            wait(sem_C)
            code()
            signal(sem_A)
        }

    no hay inanicion porque solo tenemos un semaforo prendido y los procesos o estan esperando o estan ejecutando su codigo y cuando terminan de ejecturase habilitan otro y pasan de A a b a C a A
    No hay 2 waits() de procesos que dependen del otro y esperan lo mismos
b) idem al anterior pero BBCA

    sem_A = sem(0)
    sem_B = sem(2)
    sem_C = sem(0)
    contadorB = 2

    PA:
        while (true) {
            wait(sem_A)
            code()
            signal(sem_B)
            signal(sem_B)
        }

    PB:
        while (true) {
            wait(sem_B)
            code()
            signal(sem_C)
            wait(sem_B)
            code()
            signal(sem_B)

        }

    PC: 
        while (true) {
            wait(sem_C)
            wait(sem-C)
            code()
            signal(sem_A)
        }

    otra manera es haciendo un contador ya que la anterior puede llegar a tener un deadlock

    sem_A = sem(0)
    sem_B = sem(2)
    sem_C = sem(0)
    contadorB = 2

    PA:
        while (true) {
            wait(sem_A)
            code()
            signal(sem_B)
        }

    PB:
        while (true) {
            wait(sem_B)
            code()
            contadorB --
            if (contador B == 0) {
                contadorB = 2
                signal(sem_C)
            } else {
                signal(sem_B) 
            }
        }

    PC: 
        while (true) {
            wait(sem_C)
            code()
            signal(sem_A)
        }
    No tiene inanicion por lo mimso que el anterior, todos esperan al anterior y cuando terminan le mandan al siguente la señal y B no se traba porque es el unico que toca el contador de B
    No se ejecutan en simultaneo y se ejecutan en cascada.

c) productor(A) y consumidores(C,B). Primero ejecuta el productor y luego consumen B y C. ABB o ABC o ACB o ACC.

    sem_prod = sem(1)
    sem_cons = sem(0)
    mutex(1)
    cant_productos = 0

    // como A es el unico que produce no hace falta cuidar las variables pero dejo igual los mutex
    Productor_A():
        while(true) {
            wait(sem_prod)
            mutex.wait()
            while( cant_productos != 2){
                producir()
                cant_productos++
            }
            mutex.signal()
            signal(sem_cons)
        }
    
    // tampoco hace falta el mutex porque el semaforo nos asegura que solo vamos tener un consumidor a la vez
    consumidor(): 
        wait(sem_cons)

        mutex.wait()
        consumir() 
        cant_prod--
        mutex.signal()
        if (cant_prod == 0) {
            signal(sem_prod)
        } else {
            sigal(semcons) 
        }
    
d) queremos ABB, AC, ABB, AC ...
    Queremos un contador para las ejecuciones de B y luego los consumidores se organizan entre si. Ponemos un bool con mutex y avisamos que toca AC si true y ABB si false
*/