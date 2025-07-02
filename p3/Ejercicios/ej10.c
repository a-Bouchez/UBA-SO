/*
a) 
    Si llegaste hasta acá sin haber visto un do en tu vida felicitaciones porque es un logro. Es basicamente un while con condición al final

    nos dan 2 códigos con un while true, nos dicen como arrancan los semáforos y la var global. 

    Para ver su hay deadlock me gusta como nos lo dieron haciendo digrafos y buscando ciclos asi que voy a hacer lo mejor posible por mostrarlo acá:

        Diagrama de dependencias:

            +---+      +---+      +---+ 
            | B | ───> | R | ───> | S | 
            +---+      +---+      +---+

            +---+      +---+      +---+
            | F | ───> | S | ───> | R |
            +---+      +---+      +---+

    No se ve la verdad porque no se como pedirselo a mi amigo pero la idea es que F hace S y depsues R y B hace R y despues S pero entre el nodo R y el S
    nos queda un cíclo --> deadlock si se ejecuta:

        bar: 
            semWait(R)
        --- Desalojado ---

        foo:
            semWait(S)
        --- Desalojado ---

    y ahí nos quedamos tildados porque ambos semáforos están en 0.

b) 
    puede haber starvation? bajo un scheduler justo la respuesta es no, en algún momento se tiene que ejecutar el otro proceso pero si quieren que 
    veamos un caso muuuuuy borde entonces si:

    foo:
        semWait(S)
        semWait(R)
    --- Desalojado ---

    bar:
        semWait(R) --> como está en 0 hace un sleep
    --- Desalojado ---

    resto de foo 

    si pasa eso en loop entonces si. 
*/