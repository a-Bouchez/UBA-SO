/*
Qué página sacamos con los distintos algoritmos?

    +-------+------------+------------+---+
    | Page  |  Loaded    | Last Ref.  | R |
    +-------+------------+------------+---+
    |   0   |    126     |    280     | 1 |
    |   1   |    230     |    265     | 0 |
    |   2   |    140     |    270     | 0 |
    |   3   |    110     |    285     | 1 |
    +-------+------------+------------+---+

LRU:
    - Este algoritmo va a mirar cuando fieron cargadas y las va a sacar en ese orden 

        ° El stack de desalojo nos queda: <3,0,2,1>

    - La siguente página a desalojar va a ser la 3

LRS: 
    - Este algoritmo va a mirar la última vez que se hayan usado las páginas para hacer el stack

        ° <1,2,0,3>

    - La siguiente página a desalojar va a ser la 1

SC: 
    - Este algoritmo mira la columna de loaded para hacer el stack y el bit de R para saber si darles escudo

        °  <3*,0*,2,1>

    - La siguiente página a desalojar va a ser la 2
*/