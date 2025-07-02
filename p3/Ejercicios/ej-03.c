/*
¿Qué hace mutex.wait()?

    wait() (también llamado P() o down()) intenta bajar el valor del semáforo.

    Si el valor del semáforo es mayor que 0, lo decrementa y el proceso continúa.

    Si el valor del semáforo es 0, el proceso se bloquea y espera hasta que otro proceso haga signal().

Si se usa una pila LIFO para atender los pedidos de wait() de los distintos procesos se puede dar un caso de starvation  si no dejan de entrar pedidos de wait cada vez que hay un signal().
Es decir, una vez stackeamos una pila de procesos en wait esperando a entrar a sus respectivas zonas criticas, si no nos dejan de entrar mas procesos cada vez que le podemos dar el cpu a alguno
solo vamos a desalojar a los ultimos que hayan entrado, dejando en starvation a los primeros en solicitar el uso del CPU.

Respuesta de YAGO:

Si se utiliza una pila (LIFO) para almacenar los pedidos de un semáforo, puede haber inanición si constantemente entran pedidos para el semáforo (procesos que llaman a wait sobre el semáforo). 
Los procesos que hicieron wait y quedaron en el fondo de la pila nunca logran desbloquearse porque siempre hay otros procesos que hacen wait en un momento posterior, quedan en el tope de la pila,
y cuando se libera el semáforo el scheduler les entrega el CPU a ellos pues están en el tope de la pila.
*/