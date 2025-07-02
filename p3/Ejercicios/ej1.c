/*

CODIGO 1:

    // Global
    X = 0

    // Proceso A
    X = X + 1;
    printf("%d", X);

    // Proceso B
    X = X + 1;

No tiene una unica salida, si por ejemplo arranca ejecutandose el proceso A e incremente el valor de x en 1. Luego el shceduler nos hace saltar al proceso B donde lo vuelve a incrementar. Y por 
ultimo se printea el valor 2. Distinto a si se ejecuta primero el proceso A entero y se printea 1

CODIGO 2:

    // Global
    X = 0
    Y = 0

    // Proceso A
    for (; X < 4; X++) {
        Y = 0;
        printf("%d", X);
        Y = 1;
    }

    // Proceso B
    while (X < 4) {
        if (Y == 1) printf("a");
    }

Se puede ver que el proceso B depende completamente del A ya que las 2 variables utilizadas tanto en loop como en el if solo se incrementan en A. Esto nos permite llegar a la conclusion de que 
una vez que el proceso A termina su ejecucion, tambien lo hace el prcoeso B.

En este caso tenemos muchos posibles resultados. 

    1 - A se ejecuta completamente --> vemos los prints 0123 y luego cuadno se quiera ejecutar B la condicion del while va a ser falsa y termina su ejecucion.

    2 - B se ejecuta primero y luego se ejecuta A completamente --> B gasta todo su cuantum en el while haciendo nada y despues termina igual que el de arriba.

    3 - se ejecuta A y llega hasta la parte de incrementar variables en el for, ahi tenemos 2 caminos: o logro poner Y=1 y printio su indice actual o puso Y = 0 y no printea.
        Si el scheduler nos manda a B en ese momento podemos ver como printea "a" durante todo su quantum entre alguno de los indices o no hace nada porque y=0.
        Tambien se puede dar el caso de que se llegue a chequear el if de B, y == 1, pero el scheduler vuelve a A. ahi veriamos un print de una "a" cuando le vuelva a tocat a B.
    
*/