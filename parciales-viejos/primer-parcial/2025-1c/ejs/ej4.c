/*
    int X[N];
    int step = M;    // con M predefinida

    for ( int i = 0; i < N; i += step){
        if (esPar(i)) {
            X[i] = X[i] + 1;
        }
    } else {
        X[N-i] = X[i] +1 ;
    }

    cada pag de mem puede contener P enteros, la mem física tiene F marcos y cada lectura o escritura en X[i] es un acceso a memoria

    a) N = 16, M =3, P=4 lsitar la secuencia de números accedidios y justificar cómo se derivan esos números de página a partir de los valores de i.
       coinsiderar el código y los valores de M e i se encuentran en una página fija y X[0] al inicio de la página 1.

        Si me entran P enteros en una página entonces el número de Página donde se encuentra X[i] va a ser i/P y miramos por cuanto multiplicamos el P. 
        En este caso también sumamos 1 porque arrancamos desde esa página.

        De manera que nos queda 

            - i = 0:
                ° es par
                ° O/4 es 0 y le sumamos 1 --> Pag1 
                ° escribimos en el mismo

            - i = 3:
                ° impar --> buscamos el 13 y el 3
                ° 13/4 es 3 y le sumamos 1 --> Pag4
                ° 3/4 es 0 --> Pag1

            - i = 6:
                ° es par
                ° 6/4 es 1 --> Pag2 
            
            - i = 9:
                ° buscamos 7 y el 9
                ° 9/4 es 2 --> Pag3
                ° 7/4 es 1 --> Pag2

            - i = 12:
                ° par
                ° 12/4 es 3 --> Pag4
            
            - i = 15:
                ° buscamos 1 y 15
                ° 1/4 es 0 --> Page1
                ° 15/4 es 3 --> Page4

            termina

            Primero leemos el X[i] y despues lo cargamos en el correspondiente.

            La secuencia de página accedida es <1, 1, 1, 4, 2, 2, 3, 2, 4, 4, 4, 1>.

    b)  F = 3, marcos (soy un boludo y arranqué para el otro lado a llenar mis frames pero bue)

            - Fifo:
                <1,-,-> pf
                <1,-,-> hit
                <1,-,-> hit
                <4,1,-> pf
                <2,4,1> pf
                <2,4,1> hit
                <3,2,4> pf
                <3,2,4> hit
                <3,2,4> hit
                <3,2,4> hit
                <3,2,4> hit
                <1,3,2> pf

                --> total de pagefaults = 5

            - SC:
                <1,-,->   pf
                <1*,-,->  hit
                <1*,-,->  hit
                <4,1*,->  pf
                <2,4,1*>  pf
                <2*,4,1*> hit
                <1,2*,4> --> <3,1,2*> pf
                <3,1,2*> hit
                <2,3,1> --> <4,2,3> pf
                <4*,2,3> hit
                <4*,2,3> hit
                <1,4*,2> pf

                --> total de PF = 6

    c) paja

*/