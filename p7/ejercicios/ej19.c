/*
    void seleccionar_funcion(unsigned int opcion) {
    	func (*funciones)[1000] = [ &f1, &f2, ..., &f1000 ];
    	int costos[1000] = [10, 100, 10000, 100000, ..., 10000000];
    	if (opcion>=1000) { return; };
    	usuario *usuario_actual = get_user();
    	creditos = usuario_actual->creditos;
    	return ejecutar_si_quedan_creditos(&creditos, costos[opcion-1], funciones[opcion-1]);
    }
		
    void ejecutar_si_quedan_creditos(int *creditos, int costo, func *f) {
    	unsigned int saldo = (*creditos) - costo;
    	if (saldo == 0) {
    		return; // No tiene crédito.
    	}
    	// Sí tiene.
    	(*f)(); // Se ejecuta f().
    	*creditos = saldo; // Se actualiza el saldo.
    }

    SI el usuario toma la opción 1000 le va a saltar un retunr aunque no tendría que pasar eso, ahí el usr simplemnte carga que opción quiere no el 
    indice del arr costos

    después tenemos la mítica de poner un unsigned int a la resta de 2 enteros. Si costos es más grande que saldo me va a causar un underflow 
    dandome números muy grandes que se saltean el if (saldo == 0) (que tampoco tiene sentido porque no toma nunca que puede quedar negativo)
    y cualquiera puede ejecutar la función f y cargarse un saldo que no debe.

    Si bien parece un bug, es una falla de seguirdad porque gente que no tendría que tener acceso a la función f lo tiene.
*/