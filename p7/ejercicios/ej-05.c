/*
    Me está dando paja copiar todo y hacerlo más o menos decente
    
    a) El programa puede leer /etc/shadow si el binario tiene activado el bit SETUID y pertenece al usuario root.

       Este bit le indica al sistema operativo que, al ejecutar el binario, el proceso debe correr con los privilegios del **owner del archivo**
       (en este caso, root), independientemente del usuario que lo ejecuta.

       Para que esto funcione:
       - El binario debe tener permisos de ejecución para el usuario que lo invoca (ya sea porque es su dueño, pertenece al grupo, o por permisos "others").
       - El bit SETUID debe estar activado (`chmod u+s`).
       - El owner debe ser `root`, para que el programa se ejecute con privilegios de root.

    b) El problema está en el uso de `gets()` para leer la contraseña ingresada por el usuario.

       `gets()` lee desde la entrada estándar hasta que encuentra un newline o EOF, **sin verificar el tamaño del buffer destino**. En este caso,
       el buffer `pass[128]` puede ser desbordado si se ingresan más de 128 caracteres.

       Como `pass`, `realpass` y `salt` están en la pila, uno después del otro, el usuario puede sobrescribir:
       - La variable `realpass`, con lo que quiera.
       - El array `salt`.
       - Y si escribe aún más, puede incluso pisar la **dirección de retorno** de la función `check_pass()` y tomar control del flujo del programa.

       Esto constituye un clásico **buffer overflow** con posible **ejecución de código arbitrario**.

    c) Aunque solo los usuarios ya logueados pueden acceder al protector de pantalla, esta función **sí compromete la integridad del sistema completo**.

       Razón:
       - El binario corre como root (por SETUID).
       - Un usuario común podría explotar la vulnerabilidad para obtener una shell como root.
       - Esto le permitiría **modificar archivos del sistema**, acceder a otros usuarios, o instalar software malicioso.

       Por lo tanto, aunque el usuario ya haya iniciado sesión, **la vulnerabilidad permite escalar privilegios y compromete al sistema entero**.

       Tener privilegios para ejecutar el programa **no significa tener permiso para acceder a recursos root**. Por eso, esta falla es crítica.
*/
