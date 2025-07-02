/*
    ¿Inodos o FAT? ¿Cuál conviene para los siguientes casos?

    ─────────────────────────────────────────────────────────────────────────────
    1 - Es importante que puedan crearse enlaces simbólicos.
    ─────────────────────────────────────────────────────────────────────────────

        ✅ Inodos:
            - Los sistemas con inodos (como ext2/ext3) permiten crear enlaces
              simbólicos y enlaces duros.
            - Los enlaces simbólicos son archivos especiales cuyo inodo almacena
              la ruta al archivo destino como contenido de texto.

        ⚠️ FAT:
            - FAT no soporta enlaces simbólicos ni duros.
            - Cada archivo tiene una única entrada en el directorio y no se pueden
              crear referencias alternativas a él.

        ➤ Conclusión: **Inodos** son claramente preferibles.

    ─────────────────────────────────────────────────────────────────────────────
    2 - Es importante que la cantidad de sectores utilizados para estructuras
        auxiliares sea acotada, independientemente del tamaño del disco.
    ─────────────────────────────────────────────────────────────────────────────

        ✅ Inodos:
            - En sistemas con inodos, la estructura auxiliar (la tabla de inodos)
              ocupa una cantidad fija de bloques definida al formatear el disco.
            - Su tamaño **no crece con el tamaño total del disco**, sino con la
              cantidad máxima de archivos permitida.

        ⚠️ FAT:
            - FAT necesita una tabla de asignación de bloques que contiene una
              entrada por **cada bloque del disco**.
            - Por eso, **su tamaño crece linealmente con el tamaño total del disco**.
            - Además, suele haber múltiples copias de la FAT (por redundancia),
              lo que aumenta el uso de sectores.

        ➤ Conclusión: **Inodos** son preferibles si se quiere limitar el tamaño
           de estructuras auxiliares.

    ─────────────────────────────────────────────────────────────────────────────
    3 - Es importante que el tamaño máximo de archivo sólo esté limitado por
        el tamaño del disco.
    ─────────────────────────────────────────────────────────────────────────────

        ✅ FAT:
            - El tamaño de archivo solo está limitado por el tamaño del disco.
            - Cada bloque apunta al siguiente, sin una estructura jerárquica.

        ⚠️ Inodos:
            - Tienen una cantidad finita de punteros directos, simples,
              dobles y triples indirectos.
            - Esto limita la cantidad máxima de bloques (y por ende, el tamaño
              máximo de archivo), **aunque suele ser suficiente en la práctica**.

        ➤ Conclusión: **FAT** es más flexible si se busca un límite teórico más alto,
           aunque **en sistemas modernos esto ya no suele ser un problema real**.

    ─────────────────────────────────────────────────────────────────────────────
    4 - Es importante que la cantidad de memoria principal ocupada por estructuras
        del filesystem sea (a lo sumo) lineal en la cantidad de archivos abiertos.
    ─────────────────────────────────────────────────────────────────────────────

        ⚠️ FAT:
            - La FAT completa debe estar cargada en memoria para poder seguir
              las cadenas de bloques de archivos.
            - Esto implica uso de memoria proporcional al tamaño del disco, no
              a la cantidad de archivos abiertos.

        ✅ Inodos:
            - Solo se cargan en memoria los inodos de los archivos abiertos.
            - Esto permite que el uso de memoria crezca solo con la cantidad
              de archivos efectivamente usados.

        ➤ Conclusión: **Inodos** son claramente superiores en este aspecto.

*/
