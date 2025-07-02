/*

Me ganó, este no me crean nada porque no lo pude hacer, Despues les pregunto a los profes

Qué me están pidiendo? calcular cantidad de page faults

Cómo es el reparto de memoria? no lo entendí

    Tenemos una matriz A[100][100] de enteros.

    Cada página del sistema cubre 200 bytes.

    La posición física de A[0][0] (el inicio de la matriz) está en la dirección 200, así que la matriz empieza justo al comienzo de la segunda página 
    (la primera página, direcciones 0–199, contiene el código del programa). // esto es del amigo y tiene razón ahí entendí que era jajajaj

ok, tenemos que determinar cuanto nos entra por página, sabemos que es de 200 unidades y que un elemento de la matriz ocupa 1 unidad.

tenemos una Matriz que existe en 100x100 osea un total de 10.000 elementos 

a) Accedemos por columna
    for (int j = 0; j < 100; j++)
        for (int i = 0; i < 100; i++)
            A[i][j] = 0;
        
    Con solo 2 frames, a partir de la tercera fila se produce un page fault en cada acceso, porque LRU mantiene siempre las dos páginas más recientes 
    pero llegan páginas nuevas constantemente.

    me entran 2 columnas por página por lo que j se va a mover hasta 50 técnimante 

    50




*/