/*
    Qué es un driver?
        
        - lo que me rompe la gráfica y toda la máquina 
        - son componentes de software muy específicos que conocen las particularidades del HW con el que trabajan. 
        - Corren con máximo privilegio: pueden hacer colgarse a todo el sistema.
        - De ellos depende el rendimiento de E/S, que es fundamental para el rendimiento combinado del sistema.

    a) Es una pieza de software.

        Verdadero, es un pieza del software que se encarga de comunicarse con alguna parte en es específico del HW, es su controlador encargado de 
        comunicarse con el kernel para el correcto funcionamiento de la parte.
        Genera una capa de abstracción respecto a todas las particularidades del hardware y le provee al usuario una API más amigable.

    b) Es una pieza de hardware.

        NO, se comunica con el HW pero no lo es.

    c) Es parte del SO.

        Tampoco, se carga como módulos en tienpo de ejecución  para extender la funcionalidad sin necesidad de reiniciar el sistema.

        te dejo la respueta de yago por si la mía no cierra: 
        Depende del SO. Algunos son compilados ya con los drivers del hardware que van a utilizar y posteriormente no se pueden cambiar salvo que se 
        recompile el SO. Esta configuración es más apropiada para sistemas embebidos de uso específico. En cambio, un SO de uso general tiene que 
        mantener una separación de responsabilidades ya que el usuario tiene que poder utilizar una cantidad muy diversa de hardware que requiere drivers 
        muy variados. Sería impráctico si el usuario tiene que recompilar o reinstalar el SO para usar un nuevo dispositivo. Para esta situación conviene 
        mantener los drivers aparte del SO, y en todo caso tener una API estándar para que distintos drivers puedan comunicarse con el SO.

    d) Dado que el usuario puede cambiarlo, es una aplicación de usuario.

        Corren a nivel máximp de privilegio es decir, a lvl del kernel. Si bien no forma parte de este no es algo que el usuario pueda tocar libremente
        ya que el SO nos tiene que asegurar Seguridad y protección. 
        
    e) Es un gestor de interrupciones.

        No es un gestor de interrupciones como tal pero es verdad que el HW se puede comunicar con el dirver (módulo) medienta interrupciones. 
        Igualmente este es solo uno de los métodos (también exite el Polling, miro todo el tiempo a ver si el pendejo se está portando bien, y DMA
        o direct memory access)

    f) Tiene conocimiento del dispositivo que controla pero no del SO en el que corre.

        Este es medio dudoso. Como tal yo diría que ses verdadero, indudablemente saben todo del dispositivo al que controlan pero no necesitan mucho 
        detalle del SO en el que operan. Pero si fuera del todo cierto lso drivers de Nvidia tendían que funcionar de una en linux pero no lo hacen
        así qeu algunas implementaciones específicas del SO tienen.

    g) Tiene conocimiento del SO en el que corre y del tipo de dispositivo que controla, pero no de
       las particularidades del modelo específico

       Falso, saben todo del modelo al que mamnejan. Sino podrías instalar cualquier driver de nvidia en cualquier gráfica, probablemente
       cuando intente acceder a algunos cores más nuevos qeu las anteriores no tienen se va a romper todo.
*/