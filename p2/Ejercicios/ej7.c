/*
| Process | CPU Burst | Priority | Arrival |
|---------|-----------|----------|---------|
| P1      | 3         | 0        | 0       |
| P2      | 6         | 0        | 2       |
| P3      | 4         | 0        | 4       |
| P4      | 5         | 0        | 6       |
| P5      | 2         | 0        | 8       |

|-----|----|------|----|-------|-------|
| P1  | P2 | P3   | P5 | P2    | P4    |
|-----|----|------|----|-------|-------|
0     3    4      8   10      15      20

a) Calcular el waiting time y el turnaround promedios.

    TAT[i] = CT[i] - AT[i] (cuánto tiempo total pasó desde que llegó hasta que terminó).
    --> TT = (3 + 13 + 4 + 14 +2)/5 = 7,2

    WT[i] = TAT[i] - BT[i] (cuánto tiempo estuvo esperando sin ejecutar).
    WT = ((3-3) + (13-6) + (4-4) + (14-5) + (2-2))/5 --> (0 + 7 + + 0 + 9 + 2)/5 = 3,2

b) Indicar de qué tipo de scheduler se trata, justificando claramente esa conclusión.

    Podemos ver que claramente no tiene quantums ya que los procesos duran teimpos distintos asi qeu descartamos RR.

    No es FCFS porque no se respeta el orden de llegada.

    Puede ser un SJF con interrupciones porque se respeta que siempre se ejecuta el proceso mas corto antes que el mas largo y se interrumpe a alguno mas
    largo del que acaba de llegar si se estaba ejecutando, Como le pasa a P2. Por que no se interrumpe a P3 si es mas largo que P5? porque cuando llega 
    P5 ya se ejecuto la mitad de P3 quedando los 2 del mismo tiempo. Parece estar usando una cola donde ordena a los procesos primero por tiempo de 
    ejecucion y luego por tiempo de llegada. Por eso termina el 2 antes que el 4.

    No es prioridades porque o son todos de la misma o no se definen pero se interrumpe la ejecucion de P2 y no se comporta como un FCFS mientras le llegan todos de la misma prioridad.

    Dejo como quedarian:

    // FCFS (First come, first served)

    |-----|--------|------|-------|----|
    | P1  | P2     | P3   | P4    | P5 |
    |-----|--------|------|-------|----|
    0     3        9     13      18   20

    // SJF (Shortest job first / non-preemptive)

    |-----|--------|----|------|-------|
    | P1  | P2     | P5 | P3   | P4    |
    |-----|--------|----|------|-------|
    0     3        9   11     15      20

    // Priority (non-preemptive)

    |-----|--------|------|-------|----|
    | P1  | P2     | P3   | P4    | P5 |
    |-----|--------|------|-------|----|
    0     3        9     13      18   20

    // Round-Robin (quantum = 3)

    |-----|-----|-----|-----|-----|----|----|----|
    | P1  | P2  | P3  | P4  | P2  | P5 | P3 | P4 |
    |-----|-----|-----|-----|-----|----|----|----|
    0     3     6     9    12    15   17   18   20

    // SRTF (Shortest remaining time first / preemptive SJF)

    |-----|----|------|----|-------|-------|
    | P1  | P2 | P3   | P5 | P2    | P4    |
    |-----|----|------|----|-------|-------|
    0     3    4      8   10      15      20

*/