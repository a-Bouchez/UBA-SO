/*
Recordemos que “inanición” == “starvation” == que un proceso
nunca llegue a ejecutarse == tarda muchísimo en ejecutarse.

Enunciado:
    Se tienen n procesos P1, P2, …, Pn que ejecutan este código. Se espera
    que todos terminen preparado() antes de que alguno llame a critica().
    ¿Por qué la solución propuesta *permite inanición*? Modificar el código
    para arreglarlo.

Código original:

    preparado();

    mutex.wait();
    count = count + 1;
    mutex.signal();

    if (count == n)
        barrera.signal();

    barrera.wait();

    critica();

Explicación del problema:
    Cuando el último proceso llega al `if (count == n)`, ejecuta un solo
    `barrera.signal()`. Suponiendo que `barrera` se inicializó en 0, eso
    incrementa su valor a 1, lo que desbloquea únicamente un proceso
    (el mismo u otro que estuviera en `wait()`). El resto se queda
    bloqueado **indefinidamente** en `barrera.wait()`: eso es starvation.

Solución propuesta (efecto cascada):

    preparado();

    mutex.wait();
    count = count + 1;
    if (count == n)
        barrera.signal();  // Solo el último lanza la primera señal
    mutex.signal();

    barrera.wait();       // Uno a uno van pasando a crítica

    critica();

    barrera.signal();     // Cada uno despierta al siguiente

Con este “efecto cascada”, cada proceso que sale de `critica()`
hace `barrera.signal()` para liberar al siguiente, hasta que
todos han pasado.

Otra manera de hacerlo es con n signal como vimos en clase. 

    preparado();

    mutex.wait();
    count = count + 1;
    if (count == n) {
        // Libero barrera para todos los procesos de una vez:
        for (int i = 0; i < n; i++)
            barrera.signal();
    }
    mutex.signal();

    barrera.wait();

    critica();


// habia entendido mal este y el anterior pensé que cada proceso tenía que ejecutar la zona crítica a la vez pero eso no es lo que se nos pedía. Solo tenemos que terminar de procesar
// Podíamos poner el signal despues del wait.
*/
