/*
    Para obtener un buen tiempo de respuesta del sistema necesitamos garantizar la ejecución frecuente de los procesos interactivos.

    Por el enunciado, los trabajos de procesamiento de datos no son intensivos en CPU ya que solamente hacen pequeñas cuentas una vez que leyeron los 
    archivos inmensos. 
    Podemos asumir que leer estos archivos inmensos no se realiza en el CPU, en cambio es una tarea del manejador de memoria una vez que el proceso inicia
    la transacción, bloqueándose hasta que la lectura termina y los datos ya están cargados en memoria. Por lo tanto como sus ráfagas van a ser cortas
    podríamos asumir que son parecidas a las de los procesos interactivos.

    Cómo a priori no podemos garantizar que efectivamente todos los procesos siempre van a tener ráfagas cortas, sería más conveniente elegir una política
    Round-Robin por sobre FCFS ya que de esta forma protegemos al sistema en el caso de qué algún proceso tenga alguna ráfaga demasiado larga.
*/