/*
    Hay vunerabilidades que permiten el escalado de privilegios

    Pautas:
        - Explique brevemente qué hace el código, qué función cumple cada variable, qué condiciones deben existir para que se ejecute completamente, y 
          cuales serían los vectores de ataque. Justifique e indique cualquier detalle relevante. 

        - Indique los nombres de las vulnerabilidades involucradas.

        - Indique con qué argumentos y entradas de usuario deberá ser ejecutado el programa para vulnerarlo. En caso de requerir contar con un payload
          complejo, indicar la composición del mismo.

        - En caso de requerir conocer algún dato o valor del programa para construir el payload o para realizar el ataque, indique de dónde proviene 
          el mismo, y cómo lo obtendría.

        - Indique y justifique las posibles formas de impacto del ataque en base a los tres principios básicos de la seguridad de la información.

        - Proponga una forma de mitigar la(s) vulnerabilidad(es) modificando el código.

        - Indique y justifique si existen formas de mitigar la(s) vulnerabilidad(es) a nivel del sistema operativo.
*/

/**
* Dado un usuario y una clave, indica si la misma es válida
*/
typedef bool;

extern int EXIT_FAILURE;

extern bool clave_es_valida(char* usuario, char* clave);

// Pide el largo de la clave, luego le agrega un char mas y el eol  y verifica si es la calve o no
bool validar_clave_para_usuario(char *usuario){
    // fmt = " %......."
    char fmt[8];
    fmt[0] = "%";

    printf("Ingrese un largo para la clave: ");

    // fmt = " %NNNN\0"
    scanf(" %4s", fmt+1);
    int l = strlen(fmt+1);

    // max_size <- atoi(NNNN)
    unsigned char max_size = atoi(fmt+1);
    char clave[max_size+1];

    // fmt = " %NNNNs\0"
    fmt[l+1] = "s";
    fmt[l+2] ="\0";

    scanf(fmt, clave);

    return clave_es_valida(usuario, clave);
}

// valida si la la clave es válida o no
int main(int argc, char **argv){
    setuid(0);
    bool es_valida = validar_clave_para_usuario(argv[1]);
    if(es_valida) {
        system("/bin/bash");
    } else {
        exit(EXIT_FAILURE);
    }
}

/*
    1.
        Main: 
            con el setuid(0) eleva sus privilegios a root, luego se fija el resultado de la otra funcion con el primer argumento recibido al ejecutar
            el bin y en caso de ser TRUE abre una terminal. cc error

        validar_clave_para_usuario:
            crea un buffer de tamaño 8 y pone % en su primera posición
            luego le pide al usuario que meta el largo de la clave y lee 4 caracteres del stdin y los guarda en fmt
            guarda en la var l la longitud de fmt -1 
            guarda el tamaño de fmt+1 en una var llamada max_size
            crea una lista de char llamada clave de tam max_size + 1
            pone el char s en la  última posición de fmt
            meuve el EOL de fmt una posición
            lee un string del tamaño que especifica fmt en el buffer clave
            se fija si la clave corresponde al usuario

        lo que vamos a querer acá es un buffer overflow para activar el bit de validez de la clave si n necesidad de tenerla

    2. 
        la Vunerabilidad vien de gurdar un int en un tipo unsigned char lo que nos permite escribir más caracteres de los que soporta el buffer 
        generando un BUffer overflow. Esto nos puede provocar muchas cosas como pisar el bit de validez y acceder sin necesidad de tener la clave,
        pisar variables locales y la dirección de retorno haciendo que se saltee partes del código(se peude adivinar la dir del stack y escribir un
        binario que inicialice una shell). 

        entonces tenemos:
            Integer overflow → Se está asignando a un char un valor más grande.

            Buffer overflow → Al declarar un buffer de tamaño más chico que la contraseña leída, se podría pisar valores por fuera del buffer.

            Ejecución arbitraria del código → Se va a poder pisar el return address ya que fmt, l, y max_size son de tamaño acotado.

    3. 
        Cuando podemos introducir el largo clave mandamos un valor muy grande mayor a 256. después mandamos una clave que me exceda el buffer +
        el tamaño de las otras variables para poder pisar el return y cambiarlo por la dirección de la linea:
            system("/bin/bash"); 
        De main, de manera que nos salteamos toda la parte de la autentificación y solo abrimos una terminal con priv de root

    4. 
        necesitamos saber la dir de la línea de código en la que se encuentra system(”/bin/bash”) y el valor Max_size del buffer

        según Uli: 
            El primer dato se puede obtener haciendo casteos y posibles inputs en C, y el segundo obteniendo la dirección base en la que se carga 
            el código y cuál es la dirección correspondiente en el compilado.
        
    5.
        Todos, abrimos terminal a lvl de root por lo que podemos modificar el sistema a gusto

    6.
        Cambiar el tipo de max_size por int.
        Devolver un valid=strcmp(...) entre la clave ingresada y la del usuario 

    7.
        el SO tiene: 
            - ASLR que lo que hace es modificar las direcciones hardcodeadas de retorno del stack. 
            - Stack canaries que se pone un valor en la pila luego de crear el stack frame y el compilador antes de retornar se fija que el valor
              que está escrito sea el correcto
        estas técnicas ayudan a que primero el lugar de la dir de retorno no sea siempre el mismo y segundo protegerla de posibles overflows
*/