/*
    Confío en lo de Yago:

    La tabla FAT está contenida en cierta cantidad de bloques iniciales del disco que deben ser accedidos cada vez que se consulte alguna entrada de la
    tabla pues por enunciado no se guarda la tabla FAT en memoria principal.

    Para obtener la dirección del bloque N del archivo (el último bloque), necesitamos recorrer N - 1 entradas de la tabla FAT pues el archivo tiene N 
    bloques por enunciado. Por lo tanto realizamos N - 1 accesos a disco.
*/