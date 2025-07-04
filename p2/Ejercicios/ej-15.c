/*
    Podemos utilizar una cola de prioridades sin desalojo.

    Prioridad 1 (alta):

    Todos los procesos que responden a los botones corren con esta prioridad. Se asume que estos procesos tienen ráfagas muy cortas ya que solamente tienen
    que ajustar alguna variable del algoritmo utilizado por el proceso que genera las imágenes y luego pasan a waiting para esperar la siguiente
    interacción.

    Se utiliza una política FIFO ya que los ajustes en la imagen se tienen que realizar en el mismo orden en el que el operador apreta los botones. 
    Asumimos que cada interacción con los botones genera un evento que será manejado por el proceso correspondiente, es decir, si se aprietan muchos
    botones en secuencia, todas estos ajustes quedan pendientes para ser aplicados en el mismo orden en el que sucedieron, cuando el proceso responsable
    obtiene el CPU.

    Prioridad 2 (baja):

    El proceso que genera las imágenes corre con esta prioridad. Se asume que si bien puede llegar a tener una ráfaga de media duración, sólo se generan 
    algunas imágenes por segundo. Al terminar de generar una imagen el proceso se va a dormir mientras espera la siguiente lectura del aparato, dando lugar
    a los procesos de los botones, que tienen mayor prioridad, para procesar todos los ajustes que sucedieron durante la generación de la última imagen.

    No necesitamos utilizar una política con desalojo pues si se presiona un botón durante la generación de una imagen no tendría sentido modificar ese
    parámetro inmediatamente pues obtendríamos, por ejemplo, una imagen partida en donde una porción tiene un brillo y otra porción otro brillo distinto.
*/