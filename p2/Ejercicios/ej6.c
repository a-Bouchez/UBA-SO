/*
    Mi amigo me tiro la posta: 
        BT[i]: Burst Time del proceso Pi (cuánto CPU necesita).

        AT[i]: Arrival Time del proceso Pi (cuándo llega).

        CT[i]: Completion Time (cuándo termina realmente).

        TAT[i] = CT[i] - AT[i] (cuánto tiempo total pasó desde que llegó hasta que terminó).

        WT[i] = TAT[i] - BT[i] (cuánto tiempo estuvo esperando sin ejecutar).


    | Process | CPU Burst | Priority | Arrival |
    |---------|-----------|----------|---------|
    | P1      | 10        | 3        | 0       |
    | P2      | 1         | 1        | 0       |
    | P3      | 2         | 3        | 0       |
    | P4      | 1         | 4        | 0       |
    | P5      | 5         | 2        | 0       |

    // FCFS (First come, first served)

    |------------|----|----|----|-------|
    | P1         | P2 | P3 | P4 | P5    |
    |------------|----|----|----|-------|
    0           10   11   13   14      19

    (se calcula sumando cuando arranca cada proceso y diviendo por la cantidad de procesos)
    Waiting time = (0 + 10 + 11 + 13 + 14)/5 = 9.6

    (en que momento termino cada proceso divido cant de procesos)
    Turnaround time = (10 + 11 + 13 + 14 + 19)/5 = 13.4 

    // SJF (Shortest job first / non-preemptive)

    |----|----|----|-------|------------|
    | P2 | P4 | P3 | P5    | P1         |
    |----|----|----|-------|------------|
    0    1    2    4       9           19

    WT = (0 + 1 + 2 + 4 + 9)/5 = 3.2 
    TT = (1 + 2 + 4 + 9 + 19)/5 =  7

    // Priority (non-preemptive)

    |----|-------|------------|----|----|
    | P2 | P5    | P1         | P3 | P4 |
    |----|-------|------------|----|----|
    0    1       6           16   18   19

    WT = (0 + 1 + 6 + 16 + 18)/5 = 8.2
    TT = (1 + 6 + 16 + 18 + 19)/5 = 12

    // Round-Robin (quantum = 1)

    |----|----|----|----|----|----|----|----|----|----|----|----|----|----|-------|
    | P1 | P2 | P3 | P4 | P5 | P1 | P3 | P5 | P1 | P5 | P1 | P5 | P1 | P5 | P1    |
    |----|----|----|----|----|----|----|----|----|----|----|----|----|----|-------|
    0    1    2    3    4    5    6    7    8    9   10   11   12   13   14      19

    TT = (19 + 2 + 7 + 4 + |4)/5 = 9.2
    WT = lo podes ver como cuantos quantums que no son el suyo tuvo que esperar una vez que llego su primer quantum para completarse

    Proceso |  BT |  CT  | TAT = CT–AT | WT = TAT–BT
    --------|-----|------|-------------|-----------
       P2   |  1  |   2  |     2       |    1
       P4   |  1  |   4  |     4       |    3
       P3   |  2  |   7  |     7       |    5
       P5   |  5  |  14  |    14       |    9
       P1   |  6  |  15  |    15       |    9

*/