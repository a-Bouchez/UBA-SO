/*
    Asuma que Bob crea un programa para que los usuarios de Linux puedan modificar sus contraseñas con el siguiente código:
*/
extern int stdin;

int main(void) {
	cambiarPassword();
	return 0;
}

void cambiarPassword() {
	int numeroDeUsuario = obtenerUsuarioActual();

	char password[250];
	char passwordConfirmacion[250];
	printf("Ingrese su password actual");
	fgets (password , 250, stdin ) ;          // --> problemon si gemos un gets nos babeamos y tengo que ver si no hay overflow por ser del mismo tam
                                              //     que el buffer, no se si fgets() me poner /0 o lee hasta EOF
	if (hash(password) == hashDePasswordActual(numeroDeUsuario)) {
	    printf( " Ingrese su nuevo password" );
	    fgets(password,250 , stdin );
	    printf("Confirme su nuevo password");
	    gets(passwordConfirmacion);         // este es el lindo

	    if(sonIguales(password , passwordConfirmacion)) {
	        actualizarPassword(numeroDeUsuario, password ) ;
	    }
	}
}

/*
    1. Explique qué problema de seguridad tiene el código mencionado, y cómo debería explotarlo un atacante.

        Primero a Bob no le va compilar el código porque puso main arriba de la función que llama así que el compilador todavía no le leyó.

        Después está usando gets() para la confirmación de la contraseña, recordemos que gets lee hasta EOF así que metemos lo que queremos 
        Podemos hacer un buffer overflow y pisar los datos de mi contraseña (lo cual no es muy importante) y el número del usuario pudiendo cambiar 
        la contraseña de otros usuarios.

    2. ¿Qué podría hacer con las contraseñas un atacante que logra explotar la vulnerabilidad?

        Cambiarlas tanto para bloquear el otro usuario como para acceder a su cuenta y robarle información importante. 

    3. ¿Cómo podría hacer Bob para que su programa pueda ser ejecutado por cualquier usuario y al mismo tiempo tenga permisos para modificar el
       archivo protegido /etc/passwd que sólo Bob puede leer y modificar?

        Compilar el programa con el bit de setuid prendido. 
    
    4. Si Alice pudiera leer el archivo de contraseñas, qué diferencias habría si las contraseñas se almacenan en texto plan, con una función de hash,
       o con una función de hash + salt. Explique qué podría hacer Alice en cada caso. 

        Si las tiene en texto plano directametne puede meterse a los usuarios que quiera. 

        Benja:

        Si las contraseñas estuviesen hasheadas, se podría hacer uso de hash-tables precomputadas, e intentar forzar las contraseñas de esta manera.

        Con el uso de salt, esto hace que el approach anterior se vuelva mucho más dificil para Alice. Si bien tiene acceso al valor del salt 
        (ya que suelen ser guardados con los hashes de las contraseñas), el salt hace que sea realísticamente imposible precomputar una tabla 
        con todos los posibles valores debido a cuestiones de espacio, colisiones, cant de aplicaciones de salt, y el hecho de que se suele usar
        un salt diferente para cada contraseñá. lo que previene a Alice de saber si múltiples usuarios tienen la misma contraseña si llegase a 
        crackear una.

*/