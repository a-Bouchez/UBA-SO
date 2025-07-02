/*
    En cierto sistema cuyo filesystem soporta links simbólicos corre un juego, no muy bien programado, que les permite a los ganadores figurar en
    el “salón de la fama”, que no es más que un directorio donde figura un archivo por cada ganador, conteniendo una frase a elección del ganador. 
    El juego corre con máximo privilegio.
*/

void registrar_ganador(char *nombre_ganador, char *frase) {
    char directorio_ganadores[] = "/tmp";
    char archivo_ganador[256];
    
    snprintf(archivo_ganador, sizeof(archivo_ganador), "%s/ %s",directorio_ganadores, nombre_ganador);

    if(!existe_archivo(archivo_ganador)) {
        char command[512];
        snprintf(command, sizeof command, "echo ’ %s’ > %s",frase, archivo_ganador);
        system(command);    // siempre que vemos esto nos pillamos de felicidad
    }
}

/*
    Describir al menos dos ataques distintos, uno involucrando una inyección de shell, y otro haciendo uso de los links simbólicos explotando una 
    race condition en la verificación de existencia del archivo.En ambos casos el ataque se debe combinar con un el escalamiento de privilegios.
*/

/*
    Primer ataque --> usa Echo y luego system de comand. sabemos que el jeugo corre a privilegio max asi qeu podemos hacer que mi comando sea 
                      "Hola camarón con cola;/bin/sh" y nos abrimos una terminal con máximo privilegio

    Segundo ataque --> usa echo y no me mete el hard PATH por lo que podemos crear en /tmp una carpeta que se llame /fakebin y ahí dentro con cat
                       crear un archivo que se llame echo y su contenido sea /bin/sh. usamos chmod -x para darle privilegios de ejecución y luego
                       cambiamos el path al de tmp

    Ataque de Benja --> Finalmente, como dice el enunciado, es posible usar race conditions para lograr que, cuando el código chequea la existencia
                        del archivo y falla en encontrarlo, crear un link simbólico con el mismo nombre que linkee a /etc/passwd. Con esto, podríamos 
                        lograr reemplaar los usuarios del sistema con lo que nosotros querramos, en particular, podríamos reescribir los mismos oara
                        evitar posibbles problemas, pero eliminando la contraseña de root 

    el último ataque te rompe la compu y las 3 neuronas que te quedan

    según Uli: 
        Se puede sobreescribir cualquier archivo aprovechando la race condition de la siguiente forma:
            1. No escribir ningún archivo al momento de llamar a la función.
            2. Cuando se ingresa al if de que no existe ningún archivo, escribir un link simbólico al archivo del sistema o del usuario que se 
               quiere dañan.
            3. Efectivamente se escribe al link simbólico, sobreescribiendo al archivo y generando una vulnerabilidad del sistema.
            4.Este exploit se llama TOCTOU (Time-Of-Check To Time-Of-Use)
*/