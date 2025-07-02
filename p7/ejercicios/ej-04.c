
/*
    El siguiente es un sistema de login que valida los datos contra una base de datos.

        struct credential {
            char name[32];
            char pass[32];
        }
        bool login(void) {
            char realpass[32];
            struct credential user;

            // Pregunta el usuario
            printf("User: ");
            fgets(user.name, sizeof(user), stdin);

            // Obtiene la contraseña real desde la base de datos y lo guarda en realpass
            db_get_pass_for_user(user.name, realpass, sizeof(realpass));

            // Pregunta la contraseña
            printf("Pass: ");
            fgets(user.pass, sizeof(user), stdin);

            return strncmp(user.pass, realpass, sizeof(realpass)-1) == 0;
            // True si user.pass == realpass
        }

    Suponiendo que la función db_get_pass_for_user() es totalmente correcta y no escribe fuera de realpass():

        a) Hacer un diagrama de cómo quedan ubicados los datos en la pila, indicando claramente en qué sentido crece la pila y las direcciones 
        de memoria. Explicar, sobre este diagrama, de qué datos (posiciones de memoria, buffers, etc.) tiene control el usuario a través de la 
        función fgets().

        Cuando se llama a una función en C, el compilador genera un stack frame (marco de pila), que es una porción del stack reservada para esa 
        función. En general, el layout del stack (en arquitecturas x86) es algo como esto:

            Direcciones más altas
            │
            │   [ Dirección de retorno ]       ← vuelve aquí al terminar la función
            │   [ EBP anterior         ]       ← base del stack frame anterior
            │ ─────────────────────────────────────────────
            │   [ realpass[0..31] ]            ← buffer local para la contraseña real
            │   [ user.pass[0..31] ]           ← campo pass del struct credential
            │   [ user.name[0..31] ]           ← campo name del struct credential
            │ ─────────────────────────────────────────────
            │   (ESP apunta acá al entrar a la función)
            │
            Direcciones más bajas

        Detalle del orden (de direcciones bajas a altas dentro del stack frame):

            - Primero se ubican las variables locales del struct `user`, es decir, `user.name` y `user.pass`.
            - Luego viene `realpass`, también reservado localmente.
            - Por encima están los valores automáticos del stack: EBP anterior y dirección de retorno.

        ⚠️ Como `fgets(user.name, sizeof(user), stdin)` está usando mal el tamaño (sizeof(user) da 64),
        permite escribir más de 32 bytes y el usuario puede sobreescribir `user.pass` e incluso `realpass`.

            Direcciones más altas
            ┌────────────────────────────────────────────┐
            │ Dirección de retorno                       │
            │ EBP anterior                               │
            ├────────────────────────────────────────────┤
            │ realpass[24..31]                           │ ← fin del área alcanzable por el input
            │ ...                                        │
            │ realpass[0..7]                             │
            │ user.pass[24..31]                          │
            │ ...                                        │
            │ user.pass[0..7]                            │
            │ user.name[24..31]                          │
            │ ...                                        │
            │ user.name[0..7]                            │ ← comienzo del área controlada por el usuario
            └────────────────────────────────────────────┘
            Direcciones más bajas
            
        b) Indicar un valor de la entrada, que pueda colocar el usuario, para loguearse como admin sin conocer la contraseña de este.

            pass == 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF que es el más grande que podemos meter para poner todo en 1
*/