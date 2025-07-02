/*
Ejercicio 2 – Métodos de asignación de memoria

    Tenemos 16 MB de memoria divididos en las siguientes particiones (huecos libres):

    ┌────────────┬───────┬───────┬───────┬──────────┬──────────┬───────┐
    │ Partición  │  8 MB │  1 MB │  4 MB │  512 KB  │  512 KB  │  2 MB │
    └────────────┴───────┴───────┴───────┴──────────┴──────────┴───────┘

    Vamos a aplicar tres métodos de asignación:

        - First-Fit: Toma el primer hueco que entre.
        - Best-Fit: Toma el hueco más chico posible que entre.
        - Worst-Fit: Toma el hueco más grande disponible.

    Nos llegan procesos de estos tamaños:

        - 500 KB (p1), 6 MB (p2), 3 MB (p3), 20 KB (p4), 4 MB (p5). 


    ┌────────────┬───────┬───────┬───────┬──────────┬──────────┬───────┐
    │ Partición  │  8 MB │  1 MB │  4 MB │  512 KB  │  512 KB  │  2 MB │
    ├────────────┼───────┼───────┼───────┼──────────┼──────────┼───────┤
    │ First-Fit  │   P1  │   P4  │   P3  │          │          │       │
    ├────────────┼───────┼───────┼───────┼──────────┼──────────┼───────┤
    │ Best-Fit   │   P2  │       │   P3  │    P1    │    P4    │       │
    ├────────────┼───────┼───────┼───────┼──────────┼──────────┼───────┤
    │ Worst-Fit  │   P1  │       │   P3  │          │          │   P4  │
    └────────────┴───────┴───────┴───────┴──────────┴──────────┴───────┘

    Hay procesos que no podamos asignarles espacio?
    
        - No podemos meter P2 y P5 en First-fit 

        - No podemos meter P5 en Best-fit

        - No podemos meter P2 y P5 en Worst-fit

    a) Indicar cómo asignaría las particiones utilizando best fit. ¿Cuál es la cantidad de bytes de memoria desperdiciados?

        Para saber el espacio despdiciado lo que tenemos que hacer es sumar el espacio total de la celda menos el espacio ocupado de esta para toda celda.

        En BF:

            (8 MB - 6 MB) + (1 MB - 0) + (4 MB - 3 MB) + (512 KB - 500 KB) + (512 KB - 20 KB) + (2 MB - 0)
            = 2 MB + 1 MB + 1 MB + 12 KB + 492 KB + 2 MB
            = 6 MB + 504 KB
            = 6144 KB + 504 KB
            = 6648 KB
            ~= 6.5 MB.

    b) ¿Alguna de las estrategias de asignación vistas en clase (worst fit, first fit) produce como resultado la imposibilidad de ejecutar los 5 programas
       a la vez?

        Las 2 porque no pudimos alocar todos los procesos. 

    c) ¿Cuál algoritmo hace el uso más eficiente de la memoria?

        Podemos intuir que va a ser BF pero calculemos cuanto nos sobra con los otros algoritmos: 

        WF: 
            (8 MB - 500 KB) + (1 MB - 0) + (4 MB - 3 MB) + (512 KB - 0) + (512 KB - 0) + (2 MB - 20 KB)
            = 12792 KB
            ~= 12.5 MB.

        FF: 
            12792 KB ~= 12.5 MB.

        Efectivamente BF es el más eficiente.
*/