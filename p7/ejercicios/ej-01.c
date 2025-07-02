/*
    En muchos sistemas las contraseñas de los usuarios no se almacenan, sino que se almacena solo el resultado de una función de hash. Suponiendo que
    la función de hash utilizada entrega valores de 64 bits y que los resultados se encuentran bien distribuidos, responder:

    a) ¿Cómo puede verificar el sistema si un usuario ingresó su contraseña correctamente, si no la tiene almacenada en el sistema?

        El sistema guarda solo el hash de la contraseña, no la contraseña en sí. Cuando el usuario ingresa su contraseña:

            1 - El sistema le aplica la misma función de hash que usó para almacenar el hash original.

            2 - Compara el resultado con el hash almacenado.

            3 - Si coinciden, la contraseña ingresada es correcta.

        Idea clave: hash(input_usuario) == hash_almacenado

    b) Si bien existen varias contraseñas que entregan el mismo valor de hash (colisión), ¿qué probabilidad hay de acertar el valor de hash almacenado?

        Para calcular la probabilidad primero tenemos que saber la cantidad de valores de hash que tenemos:

            En este caso como el el Hash es de 64 bits tenemos 2⁶⁴ valores posibles.

        De manera que la probabilidad de pegarle al hash es de 

            P = 1 / Cant_intentos --> 1/2⁶⁴ ~= 5.4×10⁻²⁰

    c) ¿En cuántos años se puede tener un 50 % de probabilidad de haber acertado al valor de hash almacenado, dado que pueden probarse mil millones de
        contraseñas por segundo?

            Paja, ya hice proba.

    d) Conocer el valor de hash de una contraseña no implica conocer una contraseña que genere ese valor. Suponer que se pueden probar contraseñas a 
       la misma velocidad que en el ítem anterior, pero nos informan que la contraseña es de, a lo sumo, 6 caracteres, y que estos solo son letras
       minúsculas o dígitos. ¿Cuánto tiempo hay que esperar para averiguar la clave?

        Mas cuentas, 36 digitos y podemos hacer cualquiera de c/u de los 6 caracteres de la contra sum de eso hasta 6 de 36^i y divimos por vel.
*/