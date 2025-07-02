/*
- Siempre contamos si hay starvation o no aunque no lo diga el enunciado, si quiero que no haya o si quiero que haya porque no me molesta

- Para tareas real time siempre queremos que se ejecuten rapido para que parezca interactivo. Las ejecutamos apenas las tenemos, son rafagas cortas del CPU y muhca E/S

vamos a usar una multi lvl queue con 1 + k colas de prioidad, 

la de prioridad 0 se va a encargar las tareas real-time y vamos a usar un algotimo EDF y a cada tarea le ponemos una deadline lo antes posible ( pero no nos dan deadline ni sabemos cual ponerla).
Para que salgan rapido y sabiendo que las realtime no entran todo el tiempo, vamos a usar FCFS. (usa poquito CPU y despues se distrae con cosas en disco y demas)

despues tenemos k colas de tareas interactivas, Como queremos que todas respondan lo mas rapido posible y haya fluidez usamos un RR a cada uno asegurandonos que c/u tenga un tiempo justo del cpu. 
Queremos favorecer a las tareas mas intensivas de E/S y castigar a los que usan mucho CPU.

    Para cada una de las k colas vamos a ponerle un quantum de tamaño igual q multiplicado por su numero de cola de manera tal que primero metemos todas en la cola 1 y bajamos de de prioridad a las que no puedan 
    respetar los quantum dados. Si terminan su ejecucion antes de su quantum los subimos de cola 

    Si terminan muy cerca del quantum se quedan donde estan.

    Es basicamente la def de MLFQ

    Nos quedan el 1 con q, el 2 con 2q ... el k con kq.

    donde q es lo suficientemente grande para que el context switch no sea mas caro que la ejecucion y los sufieicntemt pequeño para que no se vuelvan FCFS

    Para evitar starvation vamos a implementar aging (se quede estnacado en la cola k) por cada ciclo que espera podemos subir su prioridad en 1 hasta la fila 1.

    Si subimos una de 1 a 0 y tenemos implementado FIFO nos va a tomar de rehen el CPU hasta que termine su ejecucion. 

Que pasa si llega una RT mientras estoy ejecutando algo de otra cola. que hago?

    Implementamos interrupciones, si llega algo de una cola superior se interrumpe la ejecucion actual y se va a atender esa. -> preemption entre colas

    si te desalojo cuando termine de ejecutar el nuevo proceso, retomo el anterior pero con el quantum reiniciado. 

Como hago para dar la cota para el peor caso de response time de las tareas RT?

    Si no se cuanto tardan en correr las RT no puedo darlo asi que tiempoRT < T

    tengo k tareas de RT --> la cota a ser KxT ya que tengo que esperar a que se terminen de ejcutar todas las tareas RT que llegaron antes que yo. 

LAs tareas RT tienen starvation?

    si es FCSF no vamos a tener al igual que RR (ya que todos duran como mucho un quantum).
    Si es EDF peude que si pero no nos importa ya que se tendrian qeu cumplir los deadlines dados. cuando es SoftRT si se vence un deadline no pasa nada. si pasa todo el tiempo es uns sitema
    que esta fallando en otro lado

Saber identificar tareas como se comportan en donde son intensivos si hay aging si hay starvation si hay preemption si hay muchas colas con prioridades porque de cada cosa. 
*/