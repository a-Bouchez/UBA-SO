/*
¿Bajo qué circunstancias se produce un page fault?

    -  Cuando intentamos acceder a una página que no está en memoria causa un page-fault. Es decir Un page fault se produce cuando la MMU 
       (memory management unit) no puede satisfacer un acceso a memoria (lectura o escritura) por parte de un proceso. Muchos page faults no implican
       un error real, sino que es un mecanismo del SO para aprovechar mejor la memoria. Cuando sucede un page fault, se envía una interrupción que es 
       manejada por el SO.

Cuáles son las acciones que realiza el sistema operativo para resolver la situación?

    - se debe primero leer la página desde almacenamiento secundario y luego accederla en memoria. (IDEA)

Mecanismo (resumido)

    1 - Encontrar la página deseada en almacenamiento secundario. 

    2 - Encontrar un frame libre:

        ° Si hay un frame libre, usarlo

        ° Si no hay un frame libre, usar un algoritmo de reemplazo de páginas para seleccionar un frame víctima.

        ° Escribir el contenido del frame víctima a almacenamiento secundario (si hace falta) (en general, a espacio de swap); actualizar la tabla de
          páginas (y demás tablas).

    3 - Leer la página deseada en el recién liberado frame; actualizar la tabla de páginas (y demás tablas).

    4 - Continuar el proceso desde donde ocurrió el page-fault.
*/