/*
a) Movete al directorio /home/taller0 y mirá los permisos de archivo_misterioso.txt.
    Para ver los permisos de un archivo hago
        "ls -l" 

    salida:
        -rw-rw-r-- 1 taller0 taller0 2330 Aug 15  2023 archivo_misterioso.txt

    i. ¿Quiénes tienen permiso de lectura? ¿Y de escritura? ¿Y de ejecución?
        el primer - es de que es un archivo, despues se agrupan de a 3:

            * rw- (Dueño) → Puede leer (r) y escribir (w), pero no ejecutar (-).

            * rw- (Grupo) → Puede leer (r) y escribir (w), pero no ejecutar (-).

            * r-- (Otros) → Solo pueden leer (r), pero no escribir (w) ni ejecutar (-).

        los siguentes son el dueño y el grupo, este caso taller0

        entonces todos tinene permisos de lectura, taller0 dueño y grupo tiene permisos de escritura y nadie de ejecucion
        
*/      