/*
    ╔═══════════════════════════════════════════════════════════════════╗
    ║        Ejemplo de alternancia entre ráfagas de CPU y de E/S       ║
    ╚═══════════════════════════════════════════════════════════════════╝

    La siguiente secuencia describe cómo un proceso alterna el uso del procesador
    y operaciones de entrada/salida a lo largo del tiempo.

    ┌────────────┬───────────────────────────────────────────────────────┐
    │ Tiempo     │ Evento                                                │
    ├────────────┼───────────────────────────────────────────────────────┤
    │  0         │ load store                                            │
    │  1         │ add store                                             │
    │  2         │ read de archivo                                       │
    └────────────┴───────────────────────────────────────────────────────┘
    ► Ráfaga de CPU: tiempo 0 a 2 (duración: 3)

    ┌────────────┬───────────────────────────────────────────────────────┐
    │  3..10     │ espera E/S                                            │
    └────────────┴───────────────────────────────────────────────────────┘
    ► Ráfaga de E/S: tiempo 3 a 10 (duración: 8)

    ┌────────────┬───────────────────────────────────────────────────────┐
    │ 11         │ store increment                                       │
    │ 12         │ inc                                                   │
    │ 13         │ write en archivo                                      │
    └────────────┴───────────────────────────────────────────────────────┘
    ► Ráfaga de CPU: tiempo 11 a 13 (duración: 3)

    ┌────────────┬───────────────────────────────────────────────────────┐
    │ 14..20     │ espera E/S                                            │
    └────────────┴───────────────────────────────────────────────────────┘
    ► Ráfaga de E/S: tiempo 14 a 20 (duración: 7)

    ┌────────────┬───────────────────────────────────────────────────────┐
    │ 21         │ load store                                            │
    │ 22         │ add store                                             │
    └────────────┴───────────────────────────────────────────────────────┘
    ► Ráfaga de CPU: tiempo 21 a 22 (duración: 2)

    ─────────────────────────────────────────────────────────────────────
    a) ¿Qué es una ráfaga de CPU?

        Una ráfaga de CPU es un período continuo durante el cual un proceso 
        está ejecutando instrucciones sobre el procesador, como cálculos, 
        manipulaciones de datos, etc.

    b) ¿Qué es una ráfaga de E/S?

        Es el período donde el proceso espera o utiliza dispositivos de 
        entrada/salida (E/S), como discos, teclado o red. Durante este 
        tiempo, el proceso no necesita la CPU.

    c) Duración de cada ráfaga:

        - CPU   → 3, 3, 2 unidades de tiempo
        - E/S   → 8, 7 unidades de tiempo
*/
