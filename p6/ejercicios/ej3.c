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

    📝 Notar: en sistemas de archivos y bajo nivel se utilizan potencias de 2,
             no múltiplos decimales como en contextos comerciales.

    ─────────────────────────────────────────────────────────────────────────────
    💾 Datos del enunciado
    ─────────────────────────────────────────────────────────────────────────────

        - Sistema de archivos similar a ext2
        - Tamaño de bloque: 4 KB
        - Cada LBA ocupa: 8 bytes
        - Inodo con:
            · 5 punteros directos
            · 2 punteros a bloques de punteros indirectos simples
            · 1 puntero a bloque de punteros dobles indirectos

    ─────────────────────────────────────────────────────────────────────────────
    a) ¿Cuál es el tamaño máximo de archivo que se puede almacenar?
    ─────────────────────────────────────────────────────────────────────────────

        ✦ Directos:
            → 5 bloques directamente apuntados

        ✦ Indirectos simples:
            → Cada bloque indirecto tiene 4 KB / 8 B = 512 entradas (bloques)
            → 2 bloques → 2 × 512 = 1,024 bloques

        ✦ Doble indirecta:
            → 1 bloque con 512 punteros a bloques indirectos simples
            → Cada indirecta simple tiene 512 bloques
            → Total: 512 × 512 = 262,144 bloques

        ▶ Total de bloques: 5 + 1,024 + 262,144 = 263,173 bloques
        ▶ Tamaño máximo:
            263,173 bloques × 4 KB = 1,052,692 KB ≈ 1,028 MB ≈ 1 GB

    ─────────────────────────────────────────────────────────────────────────────
    b) ¿Qué porcentaje del disco está siendo desperdiciado?
       (Solo se considera el espacio dentro de los bloques de datos)
    ─────────────────────────────────────────────────────────────────────────────

        Dado:
            - 50% de archivos de 2 KB
            - 25% de archivos de 4 KB
            - 25% de archivos de 8 KB
            - Tamaño del bloque: 4 KB

        ➤ Archivos de 2 KB → usan la mitad del bloque → 50% de desperdicio
            → Ocupan el 50% del disco → 50% × 50% = 25% desperdiciado

        ➤ Archivos de 4 KB → ocupan completamente un bloque → 0% desperdicio

        ➤ Archivos de 8 KB → usan 2 bloques completos → 0% desperdicio

        ▶ Total desperdiciado: 25% del espacio total del disco

    ─────────────────────────────────────────────────────────────────────────────
    c) ¿Cuántos bloques deben accederse para leer completamente un archivo de 5 MB?
    ─────────────────────────────────────────────────────────────────────────────

        ✦ 5 MB = 5 × 1,024 KB = 5,120 KB
        ✦ Bloque = 4 KB → Se necesitan 5,120 / 4 = 1,280 bloques de datos

        Accesos necesarios:

        → 5 bloques directos
        → 2 bloques para las tablas de indirectos simples
        → 1,024 bloques accesibles desde las indirectas simples

        Total hasta ahora: 5 (directos) + 1,024 (datos) = 1,029 bloques

        Restan: 1,280 − 1,029 = 251 bloques

        → Acceso a:
            · 1 bloque de doble indirecta
            · 1 bloque de tabla indirecta simple
            · 251 bloques de datos (desde esa tabla)

        ➤ Total de accesos:
            5   (directos)
          + 2   (indirectas simples)
          + 1   (doble indirecta)
          + 1   (tabla indirecta)
          + 251 (datos indirectos)
          + 1,024 (datos indirectos simples)
          = 1,284 bloques

        ▶ Resultado final: Se deben acceder 1,282 bloques en total
*/
