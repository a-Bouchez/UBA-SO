/*
    Ejercicio 3:
    ¿A qué tipo de scheduler corresponde el siguiente diagrama de transición de estados?

        new → ready → running → { terminated, blocked } → ready

    Observaciones:
      • No existe transición de running → ready por expiración de quantum.
      • Un proceso en running solo abandona la CPU si:
          1) Termina su ejecución (running → terminated), o
          2) Se bloquea para E/S (running → blocked).

    Conclusión:
      Este comportamiento caracteriza a un **scheduler no-preemptivo** (sin desalojo):
      - No hay quantum que fuerce el cambio de running a ready.
      - El proceso mantiene la CPU hasta completar su ráfaga de CPU o entrar en E/S.
      - Un proceso CPU-bound (consume mucho tiempo de CPU) puede bloquear a otros procesos, especialmente los I/O-bound que esperan poco.
*/
