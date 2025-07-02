/*
Cambie su solución del ejercicio anterior con una solución basada solamente en las herramientas atómicas vista en las clases, que se implementan a nivel de hardware, y responda las siguientes
preguntas:

Este me tiene un poco perdido, no meacuerdo lo del HW. Esto es lo que encontré en las diapos.

Algunas primitivas
    getAndInc(): Devuelve el entero atómico sumado 1.

    getAndAdd(unsigned int value): Devuelve el entero atómico sumado la cantidad especificada.

    set(unsigned int value): Asigna al objeto un valor pasado por parámetro.

Código: 
    atomic<int> contador = 0;

    proceso() {
    
        preparado();
        
        // sumamos uno 
        contador.getAndInc()

        // Barrera tipo “spin”: espero hasta que todos lleguen
        while (contador.load() < n) {
            // busy-waiting
        }

        critica();
    }

// habia entendido mal este y el anterior pensé que cada proceso tenía que ejecutar la zona crítica a la vez pero eso no es lo que se nos pedía. Solo tenemos que terminar de procesar

a) ¿Cuál de sus dos soluciones genera un código más legible?
    Este tipo de código parece mas legible ya que ves claramente como se quedan en el while hasta que se suma el ultimo incrementar.

b) ¿Cuál de ellas es más eficiente? ¿Por qué?
    El anterior es más eficiente porque no hacemos busy-waiting como en esta. Es mucho desperdicion del CPU, nos la podemos jugar a poner un sleep pero quien sabe ya pueden salir del ciclo
    y el proceso está dormido.

c) ¿Qué soporte requiere cada una de ellas del SO y del HW?
    Para la nueva solución solo necesitamos soporte del CPU para realizar operaciones atómicas, no necesitamos ningún soporte especial del SO.
    Para la solución anterior, además del soporte del CPU para operaciones atómicas, necesitamos también soporte del SO para manejar la cola de procesos esperando el semáforo.

*/