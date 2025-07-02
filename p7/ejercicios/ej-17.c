/*
    El siguiente fragmento de código en C presenta al menos una vulnerabilidad grave. Se deberá hacervun análisis del mismo, se recomienda: 

        1. Analice el mismo explicando qué hace el código, qué función cumple cada variable, y cuál sería el vector de ataque y el nombre de la
           vulnerabilidad. Justifique e indique cualquier detalle relevante.

        2. Explique las potenciales formas de impacto de los distintos ataques posibles, ejemplificando inputs y outputs.

        3. Dentro de los ataques posibles, elija el que considere más grave e indique con qué valores deberá ser ejecutado el programa para vulnerarlo
           (ver debajo ejemplo de una línea de ejecución). Encaso de requerir un payload complejo, indicar la composición de cada parte del mismo.
           Indique cuáles serían las consecuencias del ataque elegido.

        4. En caso de requerir conocer algún dato o valor del programa para realizar el ataque, indique si es posible obtenerlo de algún modo.

        5. Explique si existen formas de mitigar la vulnerabilidad.
*/
extern int EXIT_FAILURE;

char MAX_SIZE = 127;
unsigned char buffer[128];
char *format = "%s %d %s\n";

char* algo_asi_si(char *cadena) {
	scanf(" %127s", buffer);
	printf(format, buffer, MAX_SIZE, cadena);
	return cadena;
}
char* algo_asi_no(char *cadena){
	if(strlen(cadena) > MAX_SIZE) exit(EXIT_FAILURE);
	sprintf(buffer, format, "echo" , atoi(cadena), "asi si?\n");
	system(buffer);
	return cadena;
}
int main(int argc, char **argv){
	setuid(0);
	printf(algo_asi_no(algo_asi_si(argv[1])));
}

/*
    1. Las funciones que tenemos son:
    
        - Main:
            ° Se sube los privilegios a los de root y luego hace printf de el resultado de pasarle a la fun no de pasarle el resultado de la fun si
              con el primer argumento recibido luego de compilar el código.
            ° La idea del código es chequear que la cadena no sea mayor al tamaño del buffer, ejecutar la cadena y luego printearla
        
        - algo_asi_no: 
            ° Se fija si el tamaño de la cadena que recibe como entrada es mayor al max_size defindo como var global, si lo es salta error
            ° Si no lo es hace un sprintf al buffer global con el formato global y queda:
                - Un string que dice echo --> problemones cuando vemos esto y un system abajo sin un path absoluto
                - Un int que es pasar a enteros la cadena
                - Un último string que es el mensaje
            ° Hace un system del buffer --> muchos problemas
            ° Devuelve la cadena
        
        - algo_asi_si: 
            ° Escanea el stdin para obtener una entrada de 127bytes para poner en un buffer de 128.
            ° Hace un printf por la terminal con estos parámetros:
                - El buffer como el primer string.
                - El tamaño max del buffer con el segundo.
                - La cadena que se pasa como parámetro.
            ° Devuelve la cadena.

        Estamos con los mismos privilegios que root, el que me parece peor de todos los ataques posibles es el de Path enviroment variable, podemos 
        crear un binario malicioso en /tmp con código bin/sh y que nos abra una terminal con privilegios max. Esto se debe a qeu no estamos dando 
        un PATH absoluto a la hora de llamar funciones como echo. 

        Otra cosa que se hace es no sanitizar la entrada por lo que puede ser código malicioso, solo se mira que no sea mas grande qeu el buffer. 
        Con un "Hola camarón con cola;bin/sh" tenes una terminal con privilegios de root.

    2. Ejemplifiqué en el anterior pero el impacto es absoluto. Al tener privilegios de root violamos los 3 principios básicos de la seguridad de la 
       información. 

       volviendo a los ejemplos del input uno ya lo dí pero termino el Path enviroment variable: 
            mkdir /tmp/fakebin

            cat < /tmp/fakebin/echo <<'EOF'
                #!/bin/sh
                /bin/sh
                EOF

            chmod +x /tmp/fakebin/echo

            export PATH="/tmp/fakebin:$PATH"
        
        El output de ambos es abrir una terminal con privilegios de root para que me puedan romper toda la máquina

    3. Para mí los 2 son igual de graves pero voy a tomar como peor el de modivicar la var de entorno ya que para el otro tenemos una medida del SO
       Que nos mitiga el inyectar código.

        Luego de hacer lo de arrbia mandamos cualquier string y cuando se ejecute el echo se nos abre la terminal. 

    4. Para ninguno

    5. A qué se refiere? nosotros? el SO? 

        Nostros obviamente podemos, es usar PATH absolutas y sanitizar strings cuando los recibimos. 

        Después por parte del SO tenemos DEP que hace qeu no podamos inyectar código.
*/