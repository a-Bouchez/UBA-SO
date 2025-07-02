/*
    ─────────────────────────────────────────────────────────────────────────────
    📌 Recordatorio: Estructura de inodos tipo ext2
    ─────────────────────────────────────────────────────────────────────────────

    El sistema de archivos está basado en inodos (como ext2) y utiliza bloques de 4 KB.

    Cada inodo posee:
        - 12 punteros directos
        - 1 puntero a bloque de punteros indirectos simples
        - 1 puntero a bloque de punteros indirectos dobles
        - 1 puntero a bloque de punteros indirectos triples

    Para saber cuántos bloques puede direccionar cada tipo de puntero indirecto, 
    necesitamos conocer cuántas LBA (entradas de puntero) caben en un bloque de 4 KB.

        Suposición general:
            - Si una LBA ocupa 4 B → entran 1024 por bloque
            - Si una LBA ocupa 8 B → entran 512 por bloque

        En general:
            - Indirecto simple  = N        bloques
            - Indirecto doble   = N × N    bloques
            - Indirecto triple  = N × N × N bloques

    (Donde N = cantidad de LBAs por bloque)

    ─────────────────────────────────────────────────────────────────────────────
    a) Si se tiene un archivo de 40 KB, ¿cuántos bloques se deben leer?
    ─────────────────────────────────────────────────────────────────────────────

        ➤ Bloque = 4 KB → 40 KB / 4 KB = 10 bloques necesarios

        Como el inodo posee 12 punteros directos, los 10 bloques del archivo pueden 
        ser accedidos directamente sin necesidad de usar punteros indirectos.

        ▶ Total de bloques a leer: 10 bloques (todos directos)

    ─────────────────────────────────────────────────────────────────────────────
    b) ¿Y si el archivo tiene 80 KB?
    ─────────────────────────────────────────────────────────────────────────────

        ➤ Bloque = 4 KB → 80 KB / 4 KB = 20 bloques necesarios

        - Los primeros 12 bloques se acceden por punteros directos
        - Para los 8 bloques restantes:
            · Se necesita usar 1 puntero indirecto simple
            · Esto implica:
                - Leer 1 bloque de tabla (el bloque de punteros)
                - Leer 8 bloques de datos referenciados por dicha tabla

        ▶ Total de bloques a leer:
            12 (directos)
          + 1  (bloque de punteros)
          + 8  (datos desde indirecto simple)
          = 21 bloques

        ⚠️ Si tuvieras el tamaño de la LBA podrías calcular cuántos bloques puede direccionar
           cada tipo de puntero indirecto con precisión (útil para archivos más grandes).
*/
