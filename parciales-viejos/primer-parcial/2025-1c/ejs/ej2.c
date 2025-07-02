/*
    2 procesos:
        - tipo1 = agraga cosas a la cola de tamaño N
        - tipo2 = usa pop() y hace el trabajo
    Code:

        mutex = sem_init(1)
        jobs = sem_init(0)
        buffer cola(N)
        
        p1() {
            trabajo = input()
            mutex.wait()
            cola.add(trabajo)
            mutex.signal()
            jobs.signal()
        }

        p2() {
            mutex.wait()
            job.wait()
            trabajo = cola.pop()
            mutex.signal()
            enviarResultados(trabajo)
        }


    a) Encontrar problemas en el código con respecto a la sincronización de procesos justificar y corregir.

            
        Vemos que el tipo 1 tiene un mutex.wait() y luego hace mutex.signal() y job.signal()

        Vemos que el tipo 2 hace mutex.wait() y luego job.wait() 

        si arranca el tipo 2 tenemos un deadlock.

        si tenemos la traza: p2.. cualquier cosa ya no funciona el código

        podemos directamente hacer un mutex_p2 inicializado en 1 y que espere primero a jobs

            mutex_p2 = sema_init(1)

            ...

            p2() {
                job.wait()
                mutex_p2.wait()
                trabajo = cola.pop()
                mutex_p2.signal()
                enviarResultados(trabajo)
            }

        (Lo que hice en el parcial fue invertirlo pero para hacer algo distinto acá pruebo esto).

        luego nos queda el problema de que nunca nos fijamos de no llenar de más el buffer, vamos a tener que chequear en el p1 y p2

            int<atomic> cant_agregados = 0;

            p1() {
                trabajo = input()
                cant_agregados.inc()
                mutex.wait()
                if(cant_agregados < N):
                    cola.add(trabajo)
                if (cant_agregados >= N):
                    print("tengo la cola llena") // masterclass
                mutex.signal()
                jobs.signal()
            }

            p2() {
                job.wait()
                mutex_p2.wait()
                trabajo = cola.pop()
                cant_agregados.dec()
                mutex_p2.signal()
                enviarResultados(trabajo)
            }
            
        Si no se puede agregar un sem donde puse el int para hacer qeu el P1 se quede espereando a poder meter cosas. Lo inicializamos en tam N 
        y P2 se encarga de mandar signal antes de enviar los resultados.

    b) Se desea que K procesos de tipo 2 (con k << N) trabajen concurrentemente pero solo puedan mandar el resultado cuando los k hayan terminado

        Acá yo hice el mítico efecto molinete pero es verdad que me lo rompe después de que pasan los primeros K. Así que lo vamos a hacer un un For

            sem_k = sema_init(0)
            int procesos = 0;      // está dentro del mutex así que no hace falta que sea un atomic

            p2() {
                job.wait()
                mutex_p2.wait()

                trabajo = cola.pop()
                cant_agregados.dec()

                K++
                if (procesos == K):
                    for i in range(k)
                        sem_k.signal()
                
                mutex_p2.signal()

                sem_k.wait()
                enviarResultados(trabajo)
            }

*/  