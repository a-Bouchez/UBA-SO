/*
    Recordemos que ext2 no guarda el nombre del archivo en el inodo sino en el directorio padre

    Linux permite pasar un descriptor de archivo de un proceso a otro (es decir, el valor de retorno de la syscall open()). Suponga que un proceso abre
    el directorio /home que está sobre una partición de ext2 y le envía el descriptor del archivo home a otro proceso con los permisos necesarios para
    poder leerlo.
    
    Suponiendo que tiene la función auxiliar Ext2FSInode load_inode(int inode_number) que dado un número de inodo devuelve la estructura del inodo, 
    escriba el pseudocódigo que le permita obtener el nombre del directorio (home) a partir del descriptor de archivo recibido

    siento que me faltan datos
*/