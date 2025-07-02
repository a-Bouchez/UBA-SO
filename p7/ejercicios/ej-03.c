/*
    Si el usuario tiene control sobre la entrada estándar, el siguiente código tiene problemas de seguridad.
*/

void saludo(void) {
    char nombre[80];
    printf("Ingrese su nombre: ");
    gets(nombre);
    printf("Hola %s!\n", nombre);
}

/*
    Se considera como un problema de seguridad que un usuario atacante pueda realizar operaciones que no le eran permitidas, ya sea tanto acceder a 
    datos privados, ejecutar código propio en otro programa o inhabilitar un servicio. Determinar:

        a) ¿Dónde se introduce el problema de seguridad?

            El problema está en el uso de la función gets(), que no verifica el tamaño del buffer. El buffer nombre tiene solo 80 bytes, pero gets() 
            leerá hasta encontrar un salto de línea, sin límite, lo que permite un buffer overflow.

            Esto permite al atacante escribir datos por fuera del arreglo nombre, sobrescribiendo zonas adyacentes en el stack, como registros, 
            variables locales, la dirección de retorno, etc.

        b) ¿Qué datos del programa (registros, variables, direcciones de memoria) pueden ser controladas por el usuario?

            El contenido del buffer nombre.

            La dirección de retorno de la función, si escribe lo suficiente para llegar a ella.

            Posiblemente, otros registros o variables locales si están en el stack contiguo.

            El flujo de ejecución del programa, si logra sobrescribir el IP (Instruction Pointer).


        c) ¿Es posible sobreescribir la dirección de retorno a la que vuelve la llamada de alguna de las funciones printf o gets?

            No se puede, creo que se encuentran en otra región de la MEMO.

        d) ¿Se soluciona el problema de seguridad si se elimina el segundo printf?
            
            No, el problema es del gets() que nos deja pisar la dirección de retorno de la función.

            Tendríamos que usar scanf(‘‘ %79s’’, nombre); para aseguararnos que no pase el tamaño del buffer o fgets()
    */