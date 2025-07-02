/*
a) El comando cat muestra el contenido de un archivo:

        $ cat esto_es_un_script.sh
    
    Si el archivo es muy largo para verse en la terminal, sólo muestra la última parte.

b) Otra alternativa es usar el comando more:

        $ more esto_es_un_script.sh

    Esto muesta la primera parte del archivo primero. Con la barra espaciadora podés ir pasando
    de a página hasta el final del archivo. Al llegar al final del archivo se vuelve a la línea de
    comandos. También se puede volver con q.

c) Para poder avanzar y subir en el archivo se puede usar el comando less:
        
        $ less esto_es_un_script.sh

    Acá también se empieza a mostrar la primer página y luego permite subir o bajar con las
    flechitas o AvPag y RePag. En este caso, al llegar al final del archivo no se vuelve a la línea de
    comandos, para esto se debe usar q.

d) Por defecto, el comando head imprime las 10 primeras líneas de un archivo:
    
        $ head esto_es_un_script.sh

    También podés especificar el número de líneas a imprimir:

        $ head -3 esto_es_un_script.sh

e) Por defecto, el comando tail imprime las 10 últimas líneas de un archivo:

        $ tail esto_es_un_script.sh

    También podés especificar el número de líneas a imprimir:
    
        $ tail -2 esto_es_un_script.sh
*/