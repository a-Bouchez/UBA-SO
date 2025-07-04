/*
Qué es copy on write?

    Cuando forkeamos que hacemos con las páginas en memoria? bueno la idea va a ser usar las mismas hasta que alguno escriba y ahí se duplican 
    y tienen sus copias independientes. 

Cómo se puede implementar? (confiemos)

    Necesitamos que las estructuras de configuración de páginas soporten un bit adicional para indicar qué páginas son copy-on-write. Cuando el MMU 
    detecta que se quiere escribir a una página configurada como copy-on-write, dispara un page fault.

    El SO procede a realizar las siguientes acciones:

        - Asigna un nuevo frame para la página que ya no es copy-on-write.

        - Copia el contenido del frame original a este nuevo frame.

        - Retorna el control al programa para que reintente la escritura.

    Además, el SO debe mantener alguna estructura de datos para contabilizar la cantidad de procesos que hacen referencia al mismo frame con copy-on-write.
    De esta forma cuando queda un único proceso referenciando al frame, en vez de copiarlo simplemente le quitamos el bit de copy-on-write y así evitamos
    perder el tracking de este frame para ser desalojado en un futuro.
*/