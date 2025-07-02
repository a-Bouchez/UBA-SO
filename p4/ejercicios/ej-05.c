/*
Primero veamos cuáles son los métodos de reemplazo de páginas:

    - FIFO
        ° Asocia a cada página el tiempo en el que fue cargada en memoria.
          Cuando se tiene que reemplazar una página, se elige la más antigua.

    - LRU
        ° Asocia a cada página el tiempo de la última vez que se usó.
          Cuando se tiene que reemplazar una página, se elige la que hace más tiempo que no se usa.

        ° En este, cuando se referencia una página que ya estaba cargada,
          se la manda al final del stack imaginario (páginas a desalojar).

    - Second Chance
        ° Rota a través de las páginas hasta encontrar la que no ha sido referenciada
          desde la última vez que chequeamos.

          Cuando una página es seleccionada para desalojar, se mira el bit de referenciada:
              - Si es 0, se desaloja.
              - Si es 1, se le da una segunda oportunidad: se limpia el bit y se actualiza
                el tiempo de llegada con el tiempo actual.

        ° Si no entendés qué carajo hace esto, pensalo como que tenés un stack y cuando
          se referencia una página le das un escudo.

          Cuando tenés que sacar una página, sacás la primera que metiste. Si tiene escudo,
          la mandás al final y después metés la nueva. (La nueva va al final).

Ejercicio:

    - Nos entran estas páginas:
        ° 1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6

    - Supongamos que tenemos los siguientes frames:
        ° 1, 2, 3, 4, 5, 6 o 7

    Si tenemos 1 frame, hay un page fault por cada entrada (excepto si justo la anterior es la que se vuelve a referenciar).
    Si tenemos 7 frames, solo vamos a tener 1 page fault por la primera vez que se referencia cada página.

    Después de arrancar el caso de 2 me di cuenta que son medio una patada, así que voy a hacer el de 5 frames.

    LRU:

        El stack imaginario nos va a decir cuáles son las que tenemos que bochar y cuáles están cargadas.

        Con 2 frames:

            page fault con 1 → <1>
            page fault con 2 → <1,2>
            page fault con 3 → <2,3>
            page fault con 4 → <3,4>
            page fault con 2 → <4,2>
            page fault con 1 → <2,1>
            page fault con 4 → <3,4>
            ...
            Me parece que ya se entiende, ¿no?

        Con 5 frames:

            page fault con 1 → <1,,,,>
            page fault con 2 → <1,2,,,>
            page fault con 3 → <1,2,3,,>
            page fault con 4 → <1,2,3,4,>
            tenemos 2      → <1,3,4,2,>
            tenemos 1      → <3,4,2,1,>
            page fault con 5 → <3,4,2,1,5>
            page fault con 6 → <4,2,1,5,6>
            tenemos 2      → <4,1,5,6,2>
            tenemos 1      → <4,5,6,2,1>
            tenemos 2      → <4,5,6,1,2>
            page fault con 3 → <5,6,1,2,3>
            page fault con 7 → <6,1,2,3,7>
            tenemos 6      → <1,2,3,7,6>
            tenemos 3      → <1,2,7,6,3>
            tenemos 2      → <1,7,6,3,2>
            tenemos 1      → <7,6,3,2,1>
            tenemos 2      → <7,6,3,1,2>
            tenemos 3      → <7,6,1,2,3>
            tenemos 6      → <7,1,2,3,6>

            Total de page faults: 9

            Perdonen si me comí algo, lo importante es la idea.

    FIFO:

        Acceso   Page fault   Frame         Cola FIFO
          1         sí         1              1
          2         sí         2              1 2
          3         sí         3              1 2 3
          4         sí         4              1 2 3 4
          2         no         2              1 2 3 4
          5         sí         5              1 2 3 4 5
          6         sí         1              2 3 4 5 6
          2         no         2              2 3 4 5 6
          1         sí         2              3 4 5 6 1
          2         sí         3              4 5 6 1 2
          3         sí         4              5 6 1 2 3
          7         sí         5              6 1 2 3 7
          6         no         1              6 1 2 3 7
          3         no         4              6 1 2 3 7
          2         no         3              6 1 2 3 7
          1         no         2              6 1 2 3 7
          2         no         3              6 1 2 3 7
          3         no         4              6 1 2 3 7
          6         no         1              6 1 2 3 7

        Total de page faults: 10
    SC: 
        Acceso 	Page fault 	Frame 	Cola FIFO
          1 	      si 	      1 	   1
          2 	      si 	      2 	   1 2
          3 	      si 	      3 	   1 2 3
          4 	      si 	      4 	   1 2 3 4
          2 	      no 	      2 	   1 2* 3 4
          5 	      si 	      5 	   1 2* 3 4 5
          6 	      si 	      1 	   2* 3 4 5 6
          2 	      no 	      2 	   2* 3 4 5 6
          1 	      si 	      3 	   3 4 5 6 2 (second chance)
                                     4 5 6 2 1
          2 	      no 	      2 	   4 5 6 2* 1
          3 	      si 	      4 	   5 6 2* 1 3
          7 	      si 	      5 	   6 2* 1 3 7
          6 	      no 	      1 	   6* 2* 1 3 7
          3 	      no 	      4 	   6* 2* 1 3* 7
          2 	      no 	      2 	   6* 2* 1 3* 7
          1 	      no 	      3 	   6* 2* 1* 3* 7
          2 	      no 	      2 	   6* 2* 1* 3* 7
          3 	      no 	      4 	   6* 2* 1* 3* 7
          6 	      no 	      1 	   6* 2* 1* 3* 7

        Total de page faults: 9
*/