/*
    impre el texto del usuario sii nombre y clave que da el usr es correcto

    usuario_habilitado -->  La misma utiliza strings terminados en caracter nulo (\0) y lee el archivo provisto de contraseñas (encriptadas) de todos 
    los usuarios del sistema, que puede ser sólo leído por root, devolviendo un booleano indicando si el usuario y la clave ingresados se encuentran
    en dicho archivo
*/
extern * NULL;

void imprimir_habilitado(const char *nombre_usuario, const char* clave,const char * imprimir, int tam_imprimir) {
    char *cmd = malloc(tam_imprimir+5 * sizeof(char));
    if (cmd == NULL) {
        exit(1);
    }
    if (usuario_habilitado("/etc/shadow", nombre_usuario, clave)) { // acá
        snprintf(cmd, tam_imprimir+4, "echo %s", imprimir);
        system(cmd);
    } else {
        printf("El usuario o clave indicados son incorrectos.");
        assert(-1);
    }
}

/*
    1. Indique si es necesario que el programa corra con algún nivel específico de permisos. Justifique en qué líneas y porqué.

        Como tiene permisos de lectura sobre el archivo shadow tiene que tener los mismos privilegios que root o correr a su nivel
        de manera tal que pueda acceder al texto y comprar las claves.

        Para esto se puede configurar el binario con el bit setuid prendido, owner root y permiso de ejecución para others, así cualquier usuario del 
        sistema puede ejecutar este programa. (Según YAGO una manera de hacer que todos puedan acceder, lo cual tiene sentido. Visto en un ej)

    2. Indique dos problemas de seguridad que podrían surgir (hint: tenga en cuenta el ítem anterior).

        Cuando vemos un system tenemos miedo, esta función básicamente agarra un string y lo ejecuta en una terminal --> problemas!!!

        El primer poblema lo vemos en que se manda directamente "imprimir" sin sanitizarlo, esto lo que le permite al atacante hacer es inyectar code
        por ejemplo si manda el string "hola; rm -rf /," se peude ejecutar un comando cuaquiera.

        El segundo que vemos es que se ejecuta el comando "echo" como no se dá todo el path del binario el atacante puede crear un binario temporal 
        con nombre echo y ejecutar código arbitrario

    3. Indique alguna manera (valuación de los parámetros) de poder explotar cada una de las vulnerabilidades mencionadas

        Ataque por format string:
            imprimir = "hola; bin/sh" --> cuando haga system de esto me abre una terminan con los permisos que tenemos (tenemos los mismos que root)

        Ataque por Path:
            primero tenemos que crear el archivo en algún lugar, para eso creamos la carpeta fakebin en tmp

                mkdir /tmp/fakebin

            ahora creamos el archivo que le vamos a poner echo y su código

                cat < /tmp/fakebin/echo <<'EOF'
                #!/bin/sh
                /bin/sh
                EOF

            Luego le damos permisos de ejecición

                chmod +x /tmp/fakebin/echo
            
            cambiamos la variable de entorno PATH

                export PATH="/tmp/fakebin:$PATH"
                
    4. Indique el impacto de las vulnerabilidades mencionadas, analizándolas según los tres requisitos fundamentales de la seguridad de la información.

        los 3 grandes son: 

            - Confidencialidad: Garantizar que la información esté disponible solo para personas autorizadas y protegerla de accesos no autorizados.

            - Integridad: Asegurar que los datos se mantengan precisos y sin alteraciones no autorizadas.

            - Disponibilidad: Mantener la información accesible y disponible para usuarios autorizados, evitando interrupciones no planificadas.

        En este caso es un escalado de privilegios, es decir, un usuario puede ejecutar con un mayor nivel de privilegios. El problema acá está en 
        que obtiene los privilegios de root --> se rompe todo, confidencialidad, integridad y disponibilidad. Una vez que el atacante obtiene los
        permisos de root la máquina es básicamente suya.

    5 - Para cada vulnerabilidad, proponga una solución, indicando cómo modificaría el código en caso de corresponder.

        La Primera es sanitizar el string, para eso le sacamos algunos carcteres especiales usando una blocklist que contenga a ;&|()

        La segunda es la del ataque por PATH o variable de entorno, en vez de llamar a echo tenemos que dar su path absoluto:
            /bin/echo
*/