/*

CODIGO: 

    x = 0 // Variable compartida
    mutex(1) // Mutex compartido

    while (1) {
        mutex.wait()                // me quedo con el cpu para hacer lo que quiero
            y = x; // Lectura de x
        mutex.signal()              // termine asi qeu te lo devuelvo
        if (y <= 5) {
            x++;
        } else {
            x--;
        }
    }

Puede ser victima de race condition, El codigo espera a que leamos X y le asignemos ese valor a Y pero puede ocurrir de que cuando uno de los procesos termine de leer y cierre el mutex,
el scheduler le de el control a otro proceso, que vuelve e leer el mismo X que el anterior (es decir, sin modificar su valor despues de la lectura).

Basicamente nos puede pasar que uno lea un valor de X y lo saquen pero cuando vuelve esa copia del valor ya no representa nada. 
En palabras lindas:

Puede haber race condition ya que la sección crítica solo contempla la lectura de la variable x pero no la comparación con 5. Cuando uno de los procesos libera el mutex con mutex.signal(), 
el scheduler podría desalojarlo, y al retomar el CPU, el valor guardado en la variable y puede no reflejar el verdadero valor de x (por ejemplo si otros procesos modificaron x).

Habría que colocar el if adentro de la sección crítica protegida por el mutex, para que la comparación con 5 y la modificación posterior de x sea todo un único bloque atómico 
(garantizado por el mutex).
*/