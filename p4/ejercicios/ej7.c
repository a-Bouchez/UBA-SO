/*
Este está bueno, quieren que veamos si entendimos la diferencia entre LRU y SC. Si lo pensamos parecen iguales, uno lo pone al final del stack del 
próximo a desalojar y el otro le dá un escudo. pero funcionan distinto.

LRU lo manda directo al final pero SC lo deja es su posición y cuando sea turno de ser desalojado, si tiene escudo, lo manda al final y luego desaloja
a otro. 

Tengo 3 frames {-,-,-} y una seq de {0,1,2,3}.

La seq va a ser 0,1,2,1,3,0,2,1.

primero llenamos con 0 1 y 2

    {0,1,2}

Ahora veamos que pasa cuando tenemos un hit con los algoritmos:

    LRU:
        {0,2,1}

    SC: 
        {0,1*,2}

Metemos el 3:

    LRU:
        {2,1,3}

    SC: 
        {1*,2,3}

Metemos el 0: 

    LRU:
        {1,3,0}

    SC: 
        {1*,2,3} --> tenemos escudo asi que nos queda de esta manera {2,3,1}, desalojamos el 2 {3,1,0}.
    
Metemos el 2:

    LRU:
        {3,0,2}

    SC: 
        {1,0,2}

Metemos el 1: 

    LRU:
        {3,0,2} --> acá tenemos miss, no estaba carcgado.

    SC: 
        {1,0,2} --> acá tenemos hit!!!!! lo tenemos cargado.

*/