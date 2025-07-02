/*
Nos piden que nos imaginemos una tabla y que usa cada algoritmo para sacar de una página mientras mira la tabla

a) ¿Qué atributo utiliza el algoritmo FIFO? ¿Y el algoritmo LRU? ¿Y Second Chance?

    - FIFO: Timestamp de cuando la página fue cargada en memoria.

    - LRU: Timestamp del último acceso a la página.

    - Second chance: Timestamp de cuando la página fue cargada en memoria + bit de accedido para volver a encolar la página y darle una segunda oportunidad

b) Pensar el algoritmo genérico para estos algoritmos de reemplazo de páginas.

    1. Se produce un page fault por acceder a una página que no tiene un frame asignado.

    2. Buscamos un frame disponible.

        i.   Si existe, lo asignamos a la página actualizando las estructuras correspondientes (page directory, page table).
        ii.  Cargamos en memoria principal el contenido de la página.
        iii. Retornamos el control al programa para que reintente el acceso.

    3. Si no hay frames disponibles, tenemos que desalojar alguno.
    
        i.   Utilizando el atributo correspondiente encontramos la página a desalojar.
        ii.  Si fue modificada, la bajamos a memoria secundaria (disco).
        iii. La desalojamos de las estructuras correspondientes marcándola como inválida.
        iV.  Asignamos el frame a la página actualizando las estructuras correspondientes.
        V.   Cargamos en memoria principal el contenido de la página.
        Vi.  Retornamos el control al programa para que reintente el acceso.

*/