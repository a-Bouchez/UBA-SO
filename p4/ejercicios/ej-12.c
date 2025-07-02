/*
Sistema A: procesamiento secuencial de archivos
    - Acceso estrictamente lineal: cada bloque se lee, procesa y escribe una sola vez.
    - Recomendamos la política “bajar la página más recientemente usada” (MRU, opción a).
      • Al expulsar justo la última página traída, garantizamos que las páginas que
        probablemente sí necesitemos (las más “antiguas” en la secuencia) sigan
        en memoria.

Sistema B: medidor de clima con respuesta inmediata
    - Páginas estáticas para el código del proceso principal (no deben desalojarse nunca).
    - Second Chance para los módulos de medición (opción c):
      • Conserva en memoria las rutinas que se usan con frecuencia.
      • Permite desalojar de forma “amable” un módulo no referenciado antes de
        expulsarlo definitivamente, cubriendo escenarios de cambio rápido.
*/
