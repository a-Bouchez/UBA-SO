/*
ENUNCIADO: 

    Se tienen N procesos, P0, P1, ..., PN −1 (donde N es un parámetro). Se requiere sincronizarlos de
    manera que la secuencia de ejecución sea Pi, Pi+1, ..., PN −1, P0, ..., Pi−1 (donde i es otro parámetro).
    Escriba el código que deben ejecutar cada uno de los procesos para cumplir con la sincronización
    requerida utilizando semáforos (no olvidar los valores iniciales).

Solución:

    La idea acá es la siguente, nostros queremos qeu un proceso espere al anterior menos cuando somos el primero (en cuyo caso arrancamos nostros) y le "avise" al proximo que puede arrancar
    su ejecución menos cuando somos el último (no le avisamos a nadie o buscamos un ciclo y le avisamos al primero).

    Para esto están muy bueno los semáforos, la idea es inicializar todos en 0 menos el primero ya que arranca él y cuando uno termina de ejecutar le manda signal() al siguiente.

Código:

    sem_0 = sem(0)
    sem_1 = sem(0)
    ...
    sem_i = sem(1)
    ... 
    sem_n-1 = sem(0)

    PO:
        sem0.wait()

        code()

        sem_1.signal()

    Pi:
        sem_i.wait()

        code()

        sem_i+1.signal()

    Pn-1:

        sem_n-1.wait()

        code()

        sem_1.signl()

*/


// codigo de yago que sigue esta idea

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10
#define start 4

sem_t s[N];

void* work(void* arg) {
    int i = *(int*)arg;
    sem_wait(&s[i]);
    printf("%d\n", i);
    sem_post(&s[(i+1) % N]);
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_t workers[N];
    int ids[N];
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        sem_init(&s[i], 0, 0);
        pthread_create(&workers[i], &attr, work, &ids[i]);
    }

    sem_post(&s[start]);

    for (int i = 0; i < N; i++) {
        pthread_join(workers[i], NULL);
    }

    return EXIT_SUCCESS;
}