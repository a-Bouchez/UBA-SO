/*
Separemos los puntos clave:

    - Módulo de video: Para este tipo de procesos se quiere evitar situaciones de scheduling poco “justas”. Este sería, dentro de los procesos normales, 
                       el más importante (sacando la alarma).

    - Módulo de Alarma: Se lanza un proceso que gestiona su activación. Se tiene que acceder de inmediato y es crítico poder garantizar que cualquier 
                        alarma se active dentro de un deadline estricto que no puede perderse.

    - Procesos nocturnos: Las cámaras se configuran para transmitir sólo en caso de detección de movimiento, así que la carga de procesos de procesamiento
                          activos de video es muy baja y en forma de ráfagas de corta duración.

Algoritmos de scheduling:

    Acá nos tiraron todos los tips básicamente. Para el módulo de video nos piden uso justo del CPU y sabemos que esto se hace con un algoritmo de RR 
    asignando un quantum de cierto tamaño para que ni sea muy grande y se comporte como un FCFS (fifo) ni sea muy corto y gastemos más tiempo en los 
    cambios de contexto.

    En el segundo módulo nos hablan de algo que necesita atenderse por sobre el resto de las cosas y que tiene un deadline. Si le sumamos lo que sabemos 
    del módulo anterior, se nos da un indicio de que puede estar bueno hacer un Multi Level Queue donde la prioridad 0 es solo para alarmas y el módulo de
    video se maneja en la cola de prioridad 1.

    Para la cola de la alarma (prioridad 0) como nos manejamos con deadlines vamos a usar un algoritmo EDF (Earliest-Deadline-First) para asegurarnos de 
    atender la mayor cantidad de alarmas en sus respectivos tiempos.

    Para la cola de prioridad 1 donde se maneja el módulo de video vamos a usar un algoritmo RR que nos garantiza uso justo del CPU ya que si se usa todo
    el quantum que le dimos al proceso, el Scheduler le saca el control del CPU y lo pone al final de cola. De esta manera tenemos uso justo del CPU para
    todos los procesos de video.

    Como siempre queremos atender las alarmas por sobre todas las cosas, no vamos a agregar Aging ya que no queremos atender otro proceso por sobre una 
    alarma. Esto nos va a generar casos de starvation en el módulo de video si no paramos de levantar alarmas. Igualmente, entiendo que el proceso de 
    levantar una alarma no debe ser muy largo como para que no podamos seguir analizando video. 

    Para la noche ocurre otra cosa. Ahora vamos a tener cortas ráfagas de video en caso de movimiento y en cambio mucho uso del CPU para comprimir el video
    de la mañana. Por lo que ahora la idea va a ser la siguiente: mantenemos la cola de prioridad 0 de las alarmas como están. Acá no se bien cómo quieren
    que nos manejemos porque podemos hacer una cola nocturna (funny) o modificar la cola de la mañana. 

    Voy a asumir que hacemos otra cola. El problema que nos trae esto es cómo mandamos acá los procesos. Podemos hacerlo con una cola de prioridad 2 donde 
    se ejecutan todas las tareas nocturnas. Esta cola se maneja con SRTF (Shortest-Remaining-Time-First). Es clave que nos digan "cortas ráfagas" por lo 
    que podemos estar procesando video y en caso de haber una de esas ráfagas, interrumpimos el proceso actual (compresión de video, que usualmente es muy 
    larga) para atender al video. 

    Me parece que otra manera de hacerlo es poner el video en la cola de prioridad 1. Sabemos que en la MLQ las colas de mayor prioridad tienen prioridad 
    absoluta por sobre las otras pero no me interrumpen la ejecución actual de un proceso (creo, ¡VER!). Si lo hicieran, en la cola de prioridad 2 podemos
    usar FCFS y mandar la parte de la noche a esta. (Volviendo al ej me parece que es legal decir que usamos una MLQ con interrupciones de ejecución de
    procesos).
*/
