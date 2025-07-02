/*
1.
    Queremos: ABC, ABC, ABC, ...

    La idea en todos estos es la misma que la del ej anterior. Buscamos que se ejecuten en orden y usamos semáforos

    sem_a = sem(1)
    sem_b = sem(0)
    sem_c = sem(0)

    A:
        sem_a.wait()

        code()

        sem_b.signal()

    B: 
        sem_b.wait()

        code()

        sem_c.signal()

    C:
        sem_c.wait()

        code()

        sem_a.signal()

    Por qué no tenemos starvation? bueno acá tenemos un efecto cascada, cada proceso habilita a que se ejecute el siguente cuando termina su código haciendo que la única manera que haya 
    starvation sea si algún proceso falla o se tilda.

2. 
    Queremos: BBCA, BBCA, BBCA, ... 

    Acá tomamos a B como todo el código y no solo la parte que yo llamé code. Si fuera solo eso el ejercício sería poner solo code() 2 veces y tocar un poco los semáforos. Por lo que vamos a 
    tener que hacer otra cosa.
    La idea en este va a ser un contador que puede ser global o estar solo en B que nos dice la cantidad de veces que el proceso se ejecutó. Si lo hizo 2 veces pasamos a C, si solo lo hizo una
    vez le vuelve a mandar signal a B.

    sem_a = sem(0)
    sem_b = sem(1)
    sem_c = sem(0)
    cant_b = 0

    A:
        sem_a.wait()

        code()

        sem_b.signal()

    B: 
        sem_b.wait()

        code()
        cant_b++

        if (cant_b < 2) {

            sem_b.signal()

        } else {

            cant_b = 0
            sem_c.signal() 

        }
        
    C:
        sem_c.wait()

        code()

        sem_a.signal()

3. 
    Queremos: ABB, ABC, ACB o ACC. Nota: ¡Ojo con la exclusión mutua!

    La idea es que primero se ejecuta A y despues puede ser o B o C. Vamos a separar el código en consumidor y productor

    sem_p = sem(1)
    sem_c0ns = sem(0)
    cant_cons = 0

    p: 
       sem_p.wait()

       producir()

       sem_cons.signal()

    cons:
        sem_cons.wait()

        consumir()
        cant_cons++

        if ( cant_cons != 2) {

            sem_cons.signal()

        } else {

            cant_cons = 0
            sem_p.signal() 

        }

    Acá A va a ser del tipo p y B,C van a ser del tipo cons. Esta solución nos dá el patrón que se nos pide ya que nunca decimos si va uno u otro pero peude haber starvation en el caso de que
    solo se ejecuten los C y nunca los B. Raro pero se podría llegar a dar. (Normalmente no va a haber starvation ya que primero arrnaca a ejecutarse el productor y cuando termina manda a 
    los clientes. Estos consumen una vez y se fijan cuantas veces lo hicieron para o volver a prender su semáforo o prender el del productor). 

4. 
    Queremos: ABB, AC, ABB, AC, ABB, AC... En este caso B consume una vez y C lo hace 2 veces

    Acá vamos a tener que usar un booleano para decir si, en este caso, es turno de B o no


    sem_A = sem(1)
    sem_B = sem(0)
    sem_C = sem(0)
    cant_cons = 0
    es_turno_de_B = TRUE

    A: 
        sem_A.wait()

        producir()

        if (es_turno_de_B) {
            sem_B.signal()
        } else {
            sem_C.signal 
        }

    B: 
        sem_B.wait()

        consumir()
        cant_cons++

        if (cant_cons != 2) {
            sem_B.signal()
        } else {
            cant_cons = 0
            es_turno_de_B = FALSE 
            sem_A.signal()
        }

    C: 
        sem_C.wait()

        consumir_todo()
        
        es_turno_de_B = TRUE

        sem_A.signal()
*/