/*
    N carritos de C personas.
    3 secciones:
        - inicio --> espera que la gente se suba antes de arrancar. sale y llega otro N veces
        - viaje
        - retiro --> llegan en el orden que salieron, esperan a que se bajen todos y despues vuelve al inicio

    RES:

    mutex = sem(1)          // para exclusión mutua en el contador de personas.
    espera_subida = sem(0)  // para bloquear a los carritos hasta que se suban C personas.
    espera_bajada = sem(0)  // para bloquear a las personas hasta que termine el viaje.
    personas_subidas = 0    // contador de personas subidas.

    persona() {
        subir()
        mutex.wait()
        personas_subidas += 1
        if (personas_subidas == C)
            espera_subida.signal()      // avisa al carrito que ya subieron todas
        mutex.signal()

        espera_bajada.wait()            // esperan a que se pueda bajar
        bajar()
    }

    carrito() {
        while (true) {
            espera_subida.wait()   // espera a que suban C personas

            viajar()

            for i in 1..C:
                espera_bajada.signal()  // libera a las C personas para que bajen

            mutex.wait()
            personas_subidas = 0    // resetea para el siguiente viaje
            mutex.signal()
        }
    }

    No hay deadlock porque en el peeor de los casos se van a quedar n-1 carritos en el retiro hasta que el N suba a todos sus pasajeros y los otros 
    empiezan a descargar

*/