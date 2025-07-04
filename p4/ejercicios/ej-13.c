/*
a) Explicar cómo funciona el mecanismo de paginación que permite ejecutar un programa más grande que la memoria física disponible.

    Al crear el proceso, se configura el page table para todas las páginas necesarias del programa, es decir los 4 MB. No obstante, solo se carga en 
    memoria una cierta cantidad de páginas que no superan los 2 MB. El resto de las páginas quedan con el bit de valid en 0.

    Cuando el programa inicia su ejecución, las primeras páginas ya las tiene disponibles. A medida que avanza su ejecución, llega a alguna página que no 
    fue cargada. Ahí, mediante el mecanismo de page faults, el SO hace un "lazy loading" de la página que se quiere usar. Esto se repite hasta que el 
    programa termine, swapeando páginas de memoria a disco según el flujo del programa.

    En la práctica vimos: 

    La memoria virtual permite la ejecución de procesos que están sólo parcialmente en memoria. Así, los programas pueden ser más grandes
    que la cantidad de memoria física disponible. Además, como cada programa toma menos memoria física, más programas pueden correr al
    mismo tiempo.

b) Si el tamaño de frame es de 4 KB y suponiendo que el programa tarde o temprano ejecuta todo su código. ¿Cuántos fallos de página se producirán como 
   mínimo?

    La memoria solo admite 512 páginas de 4 KB. Suponemos que algunas de estas páginas son utilizadas por el SO y otros programas.

    El programa requiere 1024 páginas para todo su código.

    Si al crear el proceso, le cargamos inicialmente 128 páginas en memoria (por dar un ejemplo), y el programa ejecuta todo su código al menos 1 vez, 
    entonces como mínimo va a tener que cargar sus 1024 páginas en memoria (al menos 1 vez). Si inicialmente ya le habíamos cargado 128 páginas, entonces
    se van a producir (como mínimo) 1024 - 128 = 896 page faults.

c) ¿Bajo qué contexto tiene sentido que varios procesos compartan páginas? Indique por lo menos 2 situaciones y justiﬁque.

    Cuando se realiza algún cómputo distribuido entre varios procesos donde todos necesitan acceder al mismo dataset solo para lectura.

    Las bibliotecas tipo libc pueden ser compartidas entre todos los procesos.

*/