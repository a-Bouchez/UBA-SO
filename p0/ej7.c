/*
i. Imprimí todas las líneas de archivo_misterioso.txt con la palabra escalera:
    Instrucciones para subir una escalera
    Cada uno de estos peldaños, formados como se ve por dos elementos, se sitúa un tanto más arriba y adelante que el anterior, principio que da sentido a la escalera, ya que cualquiera otra combinación producirá formas quizá más bellas o pintorescas, pero incapaces de trasladar de una planta baja a un primer piso.
    Las escaleras se suben de frente, pues hacia atrás o de costado resultan particularmente incómodas.
    Para subir una escalera se comienza por levantar esa parte del cuerpo situada a la derecha abajo, envuelta casi siempre en cuero o gamuza, y que salvo excepciones cabe exactamente en el escalón.
    Llegado en esta forma al segundo peldaño, basta repetir alternadamente los movimientos hasta encontrarse con el final de la escalera.


ii. Consultá el manual para grep y explicá para qué sirven estas opciones:

    - -n	Muestra el número de línea donde aparece la coincidencia
    - -c	Cuenta cuántas veces aparece el patrón en lugar de mostrar las líneas.
    - -i	Ignora mayúsculas y minúsculas en la búsqueda.
    - -v	Invierte la búsqueda: muestra las líneas que NO contienen el patrón.
    - -w	Busca palabras completas, evitando coincidencias parciales.

iii. ¿Qué resultado se obtiene de ejecutar grep -v login /etc/passwd?

    root:x:0:0:root:/root:/bin/bash
    sync:x:4:65534:sync:/bin:/bin/sync
    tss:x:106:111:TPM software stack,,,:/var/lib/tpm:/bin/false
    pollinate:x:111:1::/var/cache/pollinate:/bin/false
    vagrant:x:1000:1000:,,,:/home/vagrant:/bin/bash
    ubuntu:x:1001:1001:Ubuntu:/home/ubuntu:/bin/bash
    lxd:x:998:100::/var/snap/lxd/common/lxd:/bin/false
    taller0:x:1002:1002:usuario taller 0:/home/taller0:/bin/bash
    taller1:x:1003:1003:usuario taller 1:/home/taller1:/bin/bash
    taller2:x:1004:1004:usuario taller 2:/home/taller2:/bin/bash
    taller3:x:1005:1005:usuario taller 3:/home/taller3:/bin/bash
    taller4:x:1006:1006:usuario taller 4:/home/taller4:/bin/bash

    
*/