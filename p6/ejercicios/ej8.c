/*
    ─────────────────────────────────────────────────────────────────────────────
    📌 Recordemos: Tamaños en informática (basados en potencias de 2)
    ─────────────────────────────────────────────────────────────────────────────

        - 1 Byte (B)      = 8 bits           → unidad básica de almacenamiento
        - 1 Kilobyte (KB) = 2^10 bytes       = 1,024 bytes
        - 1 Megabyte (MB) = 2^20 bytes       = 1,048,576 bytes
        - 1 Gigabyte (GB) = 2^30 bytes       = 1,073,741,824 bytes

    Relaciones útiles:
        - 1 KB = 1,024 B
        - 1 MB = 1,024 KB
        - 1 GB = 1,024 MB = 1,048,576 KB = 1,073,741,824 B

    📝 Notar: en el ámbito de sistemas y archivos, se trabaja siempre con estas 
             potencias de 2, no con el sistema decimal usado en marketing.

    ─────────────────────────────────────────────────────────────────────────────
    Datos
    ─────────────────────────────────────────────────────────────────────────────

        - Disco de 16Gb
        - Sectores de 1KB
        - FS basado en FAT pero sin dirs ni archivos
        - Dado un path, se calcula el hash del nombre y éste indica cuál es el archivo buscado
        - tenemos 2 tablas:
            ° Tabla Fat que guarda las entradas correspondientes al próximo bloque, indicando el final de un archivo cuando estos valores coinciden
            ° tabla de hash que contiene, para cada hash posible, el identificador del bloque inicial y el tamaño en bytes del archivo correspondiente
              a dicho hash.
        - Tamaño de bloques: 2,4 u 8 sectores
        - Tamaño de identificadores de bloque: 8, 16, 24 o 32 bits.
        - Tamaño del hash: 8, 16, 24 o 32 bits.

    ─────────────────────────────────────────────────────────────────────────────
    a) Suponiendo que se configura con 2 sectores por bloque, identificadores de
       bloque de 24 bits, y hash de 16 bits. ¿Cuál es el tamaño que ocupa la FAT? 
       ¿Cuál es el tamaño de la tabla de archivos? ¿Cuál es el espacio que queda 
       en disco para archivos?
    ─────────────────────────────────────────────────────────────────────────────

    • Tamaño de FAT
        – 1 bloque es de 2 sectores → tam_bloque = 2×1KB = 2KB
        – cant_bloques = 16GB / 2KB = 16×2^30 / 2×2^10 = 8×2^20
        – identificadores = 24 bits = 24/8 bytes = 3B
        – Tamaño FAT = 8×2^20 × 3B = 24×2^20 bytes

    • Tamaño de tabla de archivos
        – Como el hash es de 16 bits podemos representar 2^16 nombres distintos 
          y cada uno de ellos va a ser una entrada.
        – Cada entrada contiene:
            · identificador del bloque inicial → 3B
            · tamaño en bytes del archivo → 3B para que sea menor a 16GB (en vez de 4B)
        – Total = 2^16 × 6B = 393216 bytes ≈ 384 KB

    • Espacio restante para datos
        – Total = 16×2^30 − 24×2^20 − 384×2^10 = [pendiente de cálculo final]

    ─────────────────────────────────────────────────────────────────────────────
    b) Sabiendo que se desea maximizar la cantidad de archivos que el sistema
       soporta y que, además, en promedio los archivos tendrán un tamaño de 1 KB,
       ¿cuál sería la configuración óptima del sistema de archivos? Justificar.
    ─────────────────────────────────────────────────────────────────────────────

    • Objetivo
        – Maximizar la cantidad de archivos y minimizar el espacio sin uso en bloques.

    • Hash
        – Elegimos un hash de 24 bits para tener 2^24 entradas posibles de la tabla.
          Quise poner 32 pero se me iba a 4GB la tabla y me parece que es medio mucho.

    • Tamaño de bloques
        – El tamaño de los bloques va a ser el más cercano a 1 KB que podamos tener.
          En nuestro caso sería de 2 sectores (2 KB).

    • Identificadores
        – Tienen que poder representar a todos los bloques:
            · cant_bloques = 16GB / 2KB = 8×2^20
            · Vemos que necesitamos más de 2^20 para representar estos números → 24 bits

    • Conclusión
        – Con esto maximizamos la cantidad de archivos posibles que desperdicien el menor 
          espacio por bloque posible y que puedan ser representables por nuestras tablas 
          sin necesidad de ocupar más espacio del necesario.

    ─────────────────────────────────────────────────────────────────────────────
    c) Configuración óptima si el tamaño promedio de archivos es de 16 MB
    ─────────────────────────────────────────────────────────────────────────────

    • Entradas de la tabla de hash
        – Mantenemos hash de 24 bits (2^24 ≈ 16 M entradas) → tabla ≈ 117 MiB.
          Sigue cubriendo holgadamente la cantidad de archivos esperada.

    • Tamaño de bloque
        – Bloque de 8 KB (8 sectores × 1 KB):
            · 16 MB / 8 KB = (16 × 2^20) / (8 × 2^10) = 2 × 2^10 = 2048 bloques  
              → ¡no hay fragmentación interna para archivos de 16 MB!  
        – Con 8 KB por bloque ganamos en eficiencia lectora/escritora:
            · Menos punteros por archivo  
            · Menos accesos al FAT (cada bloque mayor cubre más datos)

    • Cantidad de bloques totales
        – Disco de 16 GB / 8 KB = (16 × 2^30) / (8 × 2^10) = 2 × 2^20 = 2 097 152 bloques  
        – Identificador de bloque de 24 bits → 3 bytes por entrada en FAT

    • Identificador de bloque
        – Mantener 24 bits es suficiente para direccionar 2 097 152 bloques  
        – Con 3 bytes por entrada en FAT, la FAT ocupará:
            2 097 152 × 3 bytes ≈ 6 291 456 bytes ≈ 6 MiB

    ▶ Resumen de la configuración “16 MB promedio”:
        1 - Hash de 24 bits  
        2 - Bloque de 8 KB  
        3 - Identificador de bloque de 24 bits  

    Esta combinación minimiza la fragmentación interna para archivos de 16 MB, 
    mantiene la FAT y la tabla de hash en un tamaño razonable, y permite direccionar 
    todos los bloques del disco sin desperdiciar espacio en estructuras auxiliares.
*/
