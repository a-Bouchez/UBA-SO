/*
    Los sistemas de autenticación remota, donde el usuario se debe autenticar a través de un canal inseguro (que puede ser visto por terceros), 
    como por ejemplo POP3, a menudo no transmiten la contraseña en el proceso de autenticación para evitar que ésta sea interceptada.

    a) ¿Sería seguro autenticar al usuario enviando por el canal (desde el usuario hasta el sistema) el hash de la contraseña? 
       ¿A qué ataque es vulnerable este esquema?

        No sería seguro, básicamente cualquiera que intercepte el mensaje ya puede conectarse al sistema. Es vunerable a "replay-attacks".

    b) Un esquema Challenge-Response basado en una función de hash opera de la siguiente manera:

        ° El sistema envía una cadena seed elegida al azar.
        ° El usuario responde con el resultado de hash(seed + contraseña).
        ° El sistema hace la misma cuenta de su lado y verifica el resultado.

       Si un atacante captura toda esta conversación, ¿sería capaz de realizar un ataque de fuerza bruta sobre la contraseña sin realizar ninguna 
       interacción con el servidor (ataque offline)?

        No podría. Necesita al sistema para chequear que la respuesta sea correcta, recordemos qeu al iniciar el sistema genera una seed al azar y
        luego se la manda al usuario. Tendría que justo generarse la misma seed para poder hacer el ataque pero igualmente necesitaría el sistema
        para comparar.

        Como no me parece que mi respuesta es la mejor dejo la de YAGO: 

            Sería mucho mejor que la opción anterior. Ya no puede interceptar el hash y luego reusarlo en otro intento de autenticación porque al 
            cambiar el seed se generaría un hash distinto.

            No obstante, si el atacante obtiene el seed y también el hash generado por el usuario, puede intentar mediante un ataque de fuerza bruta 
            offline encontrar una contraseña que sumada al seed genere el mismo hash interceptado. Hay altas chances que la contraseña encontrada 
            sea la correcta, pero como las funciones de hash pueden tener colisiones, existe la posibilidad que la contraseña encontrada no sea 
            la correcta.

            La seguridad de este mecanismo viene más por la complejidad en encontrar la imagen del hash, con algoritmos de hashing modernos el tiempo
            requerido es tan grande que un ataque de fuerza bruta es simplemente inviable.

        La respuesta del chat:

            📌 ¿Es seguro? ¿Puede haber ataque offline?

            👉 Respuesta:
            El atacante no puede reutilizar la respuesta, porque el seed cambia cada vez.
            Pero sí puede hacer un ataque offline, porque tiene todo lo necesario:

                Captura seed y respuesta = hash(seed + pass).

                Luego, sin contactar al servidor, prueba con muchas contraseñas posibles:

                for candidata in diccionario:
                    if hash(seed + candidata) == respuesta:
                        print("¡Contraseña encontrada!")

            ✅ Ventaja: evita replay attack.
            ❌ Problema: es vulnerable a ataque de diccionario offline si la contraseña es débil.
*/