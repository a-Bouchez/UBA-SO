void f(char *input) {
    int a;
    char buffer[16];
    int b;
    // Sintaxis: memcpy(destino, origen, tamano en bytes)
    (void) memcpy(buffer, input, 20);
}

/*
    Considerándola en una arquitectura donde un char ocupa un byte y un int ocupa cuatro, responda las siguientes preguntas, justificando

    1. Hay algún problema de seguridad si la función se compila sin ningún tipo de optimizaciones del compilador?

        No, no hay problema. Si bien memcopy me deja copiar 20 bytes al buffer, cuando se genere el buffer overflow, se van a pisar los datos
        de la var a con los 4 bytes que me quedaban. Como a no se usa para nada en el código --> nothing ever happens. 

    2. Y si se activa la optimización de eliminación de código muerto del compilador?

        Lo cambia todo, ahora mi overflow puede pisar 4 bytes y modificar la retunr address, lo cual me genera un problema de seguridad
    
    3. Si alguna de las dos opciones anteriores permitiera atacar el código, ¿cómo debería organizar la memoria el atacante -en base a los parámetros
       que controla— como para lograr que se ejecute código de su preferencia?

        Tiene que mandar por la entrada el código del binario compilado e intentar hacer un jump a este código desde la return address. Como la puede 
        pisar con la entrada es simplemente prueba y error
*/