/*
    ─────────────────────────────────────────────────────────────────────────────
    📌 Recordatorio: Acceso a archivos en FAT y ext2 + Enlaces
    ─────────────────────────────────────────────────────────────────────────────

    📁 FAT:
        - El directorio raíz (ROOT) contiene las rutas absolutas a todos los archivos
        - Los directorios son listas de entradas de tamaño fijo
        - Para acceder a un archivo dentro de un subdirectorio:
            · Se debe leer el directorio raíz para encontrar la entrada del subdirectorio
            · Luego se debe leer el subdirectorio para encontrar la entrada del archivo

    📁 ext2:
        - Cada directorio tiene un inodo propio
        - Los inodos de directorios contienen punteros a bloques que almacenan las entradas del dir
        - Las dos primeras entradas de un directorio son:
            · "."  → referencia al mismo directorio
            · ".." → referencia al directorio padre
        - El inodo número 2 es **siempre** el del directorio raíz ("/")

    🔗 Enlaces:

        🔸 Hard links (enlaces duros):
            - El nombre del archivo no está almacenado en el inodo
            - Distintos nombres (entradas en directorios) pueden apuntar al mismo inodo
            - El inodo tiene un contador de referencias (link count)
            - Solo se elimina cuando ese contador llega a 0

        🔸 Enlaces simbólicos (soft links):
            - Se crea un archivo cuyo inodo **contiene** la ruta a otro archivo (como texto)
            - Para acceder al archivo real:
                → Se lee el archivo simbólico
                → Se interpreta su contenido como una nueva ruta
                → Se sigue esa nueva ruta como si fuera una nueva llamada

            Ejemplo de acceso:
                /renombrado.txt  → [inodo con puntero] → "/home/aprobar.txt"
                                     ↓
                                  acceso a:  /home/aprobar.txt
                                  ↓
                               acceso real a los datos

    ─────────────────────────────────────────────────────────────────────────────
    a) En un sistema FAT, ¿cuántos bloques se deben leer para acceder a /home/aprobar.txt?
    ─────────────────────────────────────────────────────────────────────────────

        1️⃣ Leer el directorio raíz para encontrar la entrada "home"  
        2️⃣ Leer el subdirectorio "home" para encontrar "aprobar.txt"

        ▶ Total de bloques accedidos: **2**

        ⚠️ Si se solicitara acceder a los datos del archivo, y el archivo fuera más
           grande que un bloque, habría que leer **bloques adicionales**.

    ─────────────────────────────────────────────────────────────────────────────
    b) En un sistema ext2, se quiere leer /pepe.txt, que es un enlace simbólico
       al archivo /home/aprobar.txt. El enlace NO está en memoria.
    ─────────────────────────────────────────────────────────────────────────────

        📌 Supuesto: /pepe.txt es un archivo que contiene como contenido
                     la ruta "/home/aprobar.txt".

        Para resolverlo se deben seguir estos pasos:

        1️- Leer el inodo número 2 (root) → está en memoria (por consigna)

        2️- Buscar la entrada "pepe.txt" en el bloque de datos del directorio raíz  
            → 1 lectura para el bloque de datos del dir root

        3️- Leer el inodo al que apunta "pepe.txt" → inodo del enlace simbólico  
            → 1 lectura del inodo (no está en memoria)

        4️- Leer el contenido del archivo simbólico (dentro de su bloque de datos)  
            → 1 lectura para obtener la cadena "/home/aprobar.txt"

        Ahora resolvemos la ruta real `/home/aprobar.txt`:

        5️ - Leer el bloque del directorio raíz para buscar "home"  
            → leido 

        6️ - Leer el inodo de "home"  
            → 1 lectura

        7️ - Leer el bloque del directorio "home" para buscar "aprobar.txt"  
            → 1 lectura

        8️ - Leer el inodo de "aprobar.txt"  
            → 1 lectura

        🔚 A partir de allí se pueden leer los bloques de datos del archivo

        ▶ Total de bloques leídos (hasta llegar al inodo de aprobar.txt): **6**

        Detalle:
            - 1 (dir raíz para pepe.txt)
            - 1 (inodo de pepe.txt)
            - 1 (contenido del enlace simbólico)
            - 1 (inodo de "home")
            - 1 (bloque de dir "home")
            - 1 (inodo de "aprobar.txt")

        ❗ El acceso a los bloques de datos no se cuenta en este caso,
           pero podrían sumarse según el tamaño del archivo.

Le pedí al chat que me ordenara un poco el texto y me puso 32 emojis, no los voy a sacar.
*/
