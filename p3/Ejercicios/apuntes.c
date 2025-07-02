// Bibliotecas necesarias
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Declaración de semáforos y variables globales
sem_t barrera; // Semáforo para bloquear hasta que todos terminen implementarTp
sem_t mutex;   // Semáforo tipo "candado" para proteger acceso a counter
int counter = 0; // Contador de estudiantes que terminaron implementarTp
int n; // Número total de estudiantes

// Función que representa el trabajo de cada estudiante
void *ProcesoEstudiantes(void *arg) {
    // Cada estudiante implementa el TP (trabajo independiente)
    implementarTp(); 

    // Antes de tocar el counter, pido el mutex (candado)
    sem_wait(&mutex); 

    // Incremento el contador de estudiantes que terminaron
    counter++;

    // Si soy el último en terminar (counter == n), libero a todos
    if (counter == n) {
        for (int i = 0; i < n; i++) {
            sem_post(&barrera); // Señalizo n veces para desbloquear a todos
        }
    }

    // Libero el mutex para que otro pueda usar counter
    sem_post(&mutex);

    // Espero en la barrera: no puedo seguir hasta que todos hayan terminado
    sem_wait(&barrera);

    // Ahora todos pueden pasar a experimentar
    experimentar(); 

    pthread_exit(NULL);
}

/*
¿Qué es el mutex?

    mutex es un semáforo binario inicializado en 1.

    Se usa para proteger una sección crítica: en este caso, el acceso a la variable counter.

    Solamente un proceso a la vez puede modificar counter gracias a mutex.

    Funciona como un candado:

        mutex.wait() intenta tomar el candado.

        Si el candado está libre (mutex > 0), pasa y baja el contador (mutex--).

        Si está ocupado (mutex == 0), espera.

¿Qué es barrera?

    barrera es otro semáforo, pero inicializado en 0.

    Sirve para bloquear a los procesos que terminaron de implementar el TP hasta que todos estén listos.

    Solo cuando todos los estudiantes terminaron implementarTp(), se libera la barrera.
*/