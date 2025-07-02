/*
    0 ganas de graficar pero usamos EDF que es un scheduling de tiempo real que se asegura (teoricamente) que podamos terminar todas las deadlines que
    tenemos. Entiendo que la gracia de estos es que interrumpen cuando les pintan.

    Le pedi a mi amigo que me haga el grafico 

    Pero la idea es como la de SFJ con interrupciones de ejecucion

    Ejercicio: EDF (Earliest Deadline First - con desalojo)

    Tareas:
    
    | Proceso | Llegada | Ejecución | Deadline |
    |---------|---------|-----------|----------|
    |   P1    |    0    |     3     |    16    |
    |   P2    |    2    |     1     |     7    |
    |   P3    |    0    |     6     |     8    |
    |   P4    |    8    |     2     |    11    |
    |   P5    |   13    |     3     |    18    |

    Política: EDF con desalojo → siempre se ejecuta el proceso listo con el deadline más próximo.

    Diagrama de Gantt:

    |---------|--|-------------|----|--|-----|
    |   P3    |P2|     P3      | P1 |P4| P1  | P5
    |---------|--|-------------|----|--|-----|
     0        2  3            8    10 12   13  16

    Detalle:
    - P3 inicia en t=0, pero al llegar P2 (t=2, con deadline más cercano), se interrumpe y P2 se ejecuta.
    - Al terminar P2, P3 retoma y sigue hasta el arribo de P4 (t=8).
    - Luego de ejecutar P4, se continúa con P1 (que aún no finalizó), y luego P5.

    Finish times:
    - P1 = 16
    - P2 = 3
    - P3 = 10
    - P4 = 12
    - P5 = 19

    Turnaround Time = Finish - Arrival
    - P1: 16 - 0  = 16
    - P2:  3 - 2  = 1
    - P3: 10 - 0  = 10
    - P4: 12 - 8  = 4
    - P5: 19 - 13 = 6

    Waiting Time = Turnaround - Burst
    - P1: 16 - 3 = 13
    - P2:  1 - 1 = 0
    - P3: 10 - 6 = 4
    - P4:  4 - 2 = 2
    - P5:  6 - 3 = 3

    Promedios:
    - Turnaround promedio = (16 + 1 + 10 + 4 + 6) / 5 = 7.4
    - Waiting promedio    = (13 + 0 + 4 + 2 + 3) / 5 = 4.4

*/