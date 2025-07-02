/*
Para los procesos presentados en la siguiente tabla, realizar un gráfico de Gantt para cada uno de los algoritmos de scheduling indicados:

| Process | CPU Burst | Priority | Arrival |
|---------|-----------|----------|---------|
| P1      | 1         | 0        | 5       |
| P2      | 10        | 0        | 6       |
| P3      | 1         | 0        | 7       |
| P4      | 10        | 0        | 8       |

// FCFS (First come, first served)
// SJF (Shortest job first / non-preemptive)
// Round-Robin (quantum = 10)

|-------|----|------------|----|------------|
|///////| P1 | P2         | P3 | P4         |
|-------|----|------------|----|------------|
0       5    6           16   17           27

//CT[i] - AT[i]
TAT = (1 + 10 + 10 + 19)/4 = 10

//TAT[i] - BT[i]
WT = (0 + 0 + 9 + 9)/4 = 4,5

Es en todos igual.
*/