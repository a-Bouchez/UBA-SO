/*
| Process | CPU Burst | Priority | Arrival |
|---------|-----------|----------|---------|
| P1      | 8         | 0        | 0       |
| P2      | 8         | 0        | 5       |
| P3      | 6         | 0        | 14      |
| P4      | 5         | 0        | 15      |

// Round-Robin (quantum = 5)

|-------|-------|-----|-----|-------|-------|----|
| P1    | P2    | P1  | P2  | P3    | P4    | P3 |
|-------|-------|-----|-----|-------|-------|----|
0       5      10    13    16      21      26   27

TAT = (13 + 11 + 13 + 11)/4 = 12
WT = (5 + 3 + 7 + 6)/4 = 5,25

// SRTF (Shortest remaining time first / preemptive SJF)

|----------|----------|-------|--------|
| P1       | P2       | P4    | P3     |
|----------|----------|-------|--------|
0          8         16      21       27

TAT = (8 + 11 + 13 + 6)/4 = 9,5
WT = (0 + 3 + 7 + 1)/4 = 2,75

d)  A pesar de que uno de los dos casos tiene un tiempo de turnaround promedio mucho menor, explicar por qué en algunos contextos podría tener sentido utilizar la otra política. Para esto
    considere distintos tipos de procesos: real time, interactivos, batch, etc

        Si bien SRTF obtiene un turnaround promedio menor, si se tratan de procesos interactivos un algoritmo round-robin genera un scheduling más justo entre todos los procesos ready. 
        Esto es importante para que el usuario perciba que el sistema es más "responsive", que no tiene latencia entre una interacción (mouse, teclado, etc) y la respuesta del programa.
        (Si fuera SRTF veriamos como se nos queda tildada la compu).

        Por otro lado, si siempre hay procesos con ráfagas cortas en ready, como ser procesos interactivos o real-time, SRTF les va a dar el CPU constantemente quizás produciendo starvation a 
        los procesos con ráfagas largas, como los batch. REcordemos que RR nos da un uso justo del cpu a todos los procesos
*/