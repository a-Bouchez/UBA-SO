/*
    ─────────────────────────────────────────────────────────────────────────────
    📌 Comparación de accesos a disco: ext2 vs FAT
    ─────────────────────────────────────────────────────────────────────────────

    Supuestos:
        - Sistema de archivos ext2:
            · 12 punteros directos
            · 1 puntero a bloque de punteros indirectos simples
            · 1 puntero a bloque de punteros indirectos dobles
            · 1 puntero a bloque de punteros indirectos triples

        - Tamaño del bloque:        4 KB
        - Cantidad de LBAs por bloque: 512 (→ cada bloque de punteros contiene 512 entradas)

        - En ambos casos:
            · Se asume que la tabla FAT y los inodos están ya cargados en memoria
            · Si un mismo bloque se accede más de una vez, se cuenta una sola lectura
            · En FAT se conoce el número de bloque inicial

    ─────────────────────────────────────────────────────────────────────────────
    i) Leer bloques: 1, 2, 3, 5, 7, 11, 13, 17, 23
    ─────────────────────────────────────────────────────────────────────────────

        En ext2:
            - Los bloques del 1 al 12 son accesibles por punteros directos → 1 lectura por bloque
            - A partir del bloque 13 se accede vía el puntero indirecto simple

            Supongamos que los bloques 13, 17 y 23 caen dentro del primer indirecto simple:
                · 1 lectura del bloque de punteros indirectos
                · 3 lecturas de bloques de datos apuntados

            Total:
                6 lecturas directas + 1 indirecta simple + 3 lecturas → 10 lecturas

    ─────────────────────────────────────────────────────────────────────────────
    ii) Leer bloques: 1, 2, 3, 4, 5, 6, 10001
    ─────────────────────────────────────────────────────────────────────────────

        - Bloques 1 a 6 → punteros directos → 6 lecturas
        - Bloque 10001:
            · Acceso mediante indirecto doble:
                - 1 lectura del bloque de punteros dobles
                - 1 lectura de bloque de punteros simples
                - 1 lectura del bloque de datos

        Total: 6 + 3 = 9 lecturas

        ⚠️ Dato útil: 
            · Si cant_LBA = 512 ⇒ indirecto doble cubre hasta 512² = 262,144 bloques

    ─────────────────────────────────────────────────────────────────────────────
    iii) Leer bloques: 13, 10000, 1000000
    ─────────────────────────────────────────────────────────────────────────────

        - Bloque 13:
            · Acceso por indirecto simple + bloque de datos = 2 lecturas

        - Bloque 10000:
            · Indirecto doble → indirecto simple → datos = 3 lecturas

        - Bloque 1,000,000:
            · Indirecto triple → doble → simple → datos = 4 lecturas

        Total: 2 + 3 + 4 = 9 lecturas

    ─────────────────────────────────────────────────────────────────────────────
    iv) Leer bloques: 14, 15, ..., 50
    ─────────────────────────────────────────────────────────────────────────────

        - Todos estos bloques están dentro del rango accesible por el indirecto simple
        - Se realiza:
            · 1 lectura del bloque de punteros indirectos (la tabla)
            · 1 lectura por cada bloque de datos individual (del 14 al 50 inclusive)

        Total:
            · 1 (tabla) + (50 − 14 + 1) = 1 + 37 = 38 lecturas

    ─────────────────────────────────────────────────────────────────────────────
    📘 Comparación con FAT
    ─────────────────────────────────────────────────────────────────────────────

        En FAT:
            - La tabla FAT se encuentra cargada en memoria
            - Basta con conocer el bloque inicial del archivo
            - Se accede directamente a cada bloque de datos

        ▶ Por lo tanto, el número de accesos a disco en FAT es igual al número
          de bloques que se desean leer (uno por cada bloque de datos).

*/
