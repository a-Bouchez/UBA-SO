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
    💾 Datos del enunciado
    ─────────────────────────────────────────────────────────────────────────────

        - Capacidad del disco:     128 GB
        - Tamaño de bloque:        8 KB
        - Sistema de archivos:     similar a FAT
        - Ubicación de la tabla:   desde la posición 0
        - Tamaño de entrada en la tabla: 24 B (por bloque)

    ─────────────────────────────────────────────────────────────────────────────
    a) ¿Qué tamaño ocupa la tabla?
    ─────────────────────────────────────────────────────────────────────────────

        Cantidad de bloques del disco:
            128 GB / 8 KB = 
            (128 × 2³⁰) / (8 × 2¹⁰) = 16 × 2²⁰ bloques

        Tamaño de la tabla (1 entrada de 24 B por bloque):
            (16 × 2²⁰) × 24 B = 384 × 2²⁰ B

        ¿Cuántos bloques ocupa la tabla?
            (384 × 2²⁰) / (8 × 2¹⁰) = 48 × 2¹⁰ B → 48 bloques

    ─────────────────────────────────────────────────────────────────────────────
    b) ¿Cuántos archivos de 10 MB se pueden almacenar?
    ─────────────────────────────────────────────────────────────────────────────

        Bloques disponibles para datos:
            Total de bloques      = 16 × 2²⁰
            Menos los de la tabla = 48
            → 16 × 2²⁰ − 48 = 16336 × 2¹⁰ bloques

        Tamaño en bloques de un archivo de 10 MB:
            10 MB / 8 KB = 
            (10 × 2²⁰) / (8 × 2¹⁰) = 1.25 × 2¹⁰ = 1280 bloques

        Máxima cantidad de archivos:
            (16336 × 2¹⁰) / 1280 = 12.7625 × 2¹⁰ ≈ 13068 archivos

    ─────────────────────────────────────────────────────────────────────────────
    c) Se sabe que un archivo comienza en el bloque 20. Dada la siguiente FAT:
    ─────────────────────────────────────────────────────────────────────────────

        Bloque       →    0  1  2 3 4 5 6 ... 20 21 22 ...
        Siguiente    →   EOF 2 23 4 5 0 7 ... 21 22  3 ...

        Recorrido: 20 → 21 → 22 → 3 → 4 → 5 → 0 → EOF archivo de 7 bloques

        Tamaño del archivo:
            7 × 8 KB = 56 KB
*/
