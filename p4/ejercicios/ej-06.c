/*
a) ¿Por qué los algoritmos de reemplazo LRU, FIFO y Second Chance no serán efectivos para manejar esta dinámica para una cantidad de frames menor al 
   largo de la secuencia?

        Porque lo más probable es que se produzca un pagefault por cada página ya que vamos a tener desalojo en cascada de todas ellas. 
        Están pensados para intentar tener las páginas más recientes que usaste Pero en este caso tenemos una secuencia desde 0 hasta 511 seguido por una 
        página random. se van a comportar todas como si fueran FIFO y van a ser todos miss. 
    
b) Si este programa tuviera disponibles 500 frames, describir un enfoque de reemplazo de páginas que funcione mejor que los algoritmos LRU, FIFO o 
   Second Chance.

        Este es medio raro no? si ya sabemos que tenemos una secuencia desde el 0 al 511 y despues 2 randoms que están entre el 0 y el 500 podemos 
        decir que una vez que se llenen los 500 frames hacemos FILO (first in last out) o mejor dicho LIFO (last in first out) de manera que nos la vamos 
        a pasar cambiando desde la página 500 y la 511 pero vamos a pegarle a toda la secuencia desde el 0 al 489 más los 2 randoms.

Creo que este ejercicio no es muy importante pero VER!!! después le pregunto a los profes (Benja, Valen y Fede) --> Lo compraron.
*/