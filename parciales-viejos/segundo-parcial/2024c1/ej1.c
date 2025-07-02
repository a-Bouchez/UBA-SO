/*
    filesystem con indos

    a) pseudocode para acceder al archivo A/B/c.txt teniendo el inodo del dir A: 

        Si tenemos el inodo del dir A lo que vamos a tener que hacer es mirar en sus bloques directos donde está la referencia al inodo del dir B y
        luego hacer esto mismo para llegar a c.txt

        vamos a necesitar 2 lecturas para llegar al archivo ya que enteindo que el A lo tenemos cargado

        una dir_entry tiene este tipo: 

        dir_entry {
            int inode
            int record_length
            int name_length
            int file_type
            char name[]
        }

        me fijo en A dentro de sus bloques --> van a haber entrues que no ocupan todo el bloque por lo que tengo que hacer un offset con su tamaño
        e ir incrementandolo con eso

        get_txt(A:inode, Path) {
            names[] = los nombres que salen en path
            inodo_act = A

            // iteramos por cada nombre
            for name in names: 
                encontrado = 0;

                // iteramos por cada bloque
                for block in get_blocks(inodo_act): 
                    offset = 0

                    // mientras sigamos teniendo espacio para seguir leyendo
                    while (offset < block_size): 
                        bloque = read_blocks(A,block);

                        dir_entry = bloque + offset

                        // si tienen el mismo nombre
                        if dir_entry.name == name: 

                            inodo_act = load_inode(dir_entry.inode)
                            econtrado = 1
                            break

                        offset += dir_entry.length

                    if encontrado: 

                        break

            return inodo_act                        
        }
        
    b) cuantas escrituras para renombrar el archivo /home/j/l.txt a /home/m.txt

        Parecen que 2 no? o es un engaña pichanga?

        primero accedemos al dir entry del txt y le cambiamos el largo y el nombre del archivo --> 1

        luego hacemos lo mismo para el dir --> 2

        modificamos 2 bloques --> 2 escrituras al disco

    c) ejecutamos como root, se podria ejecutar un loop infito al leer un archivo?

        si hacemos que el inodo se apunte a si mismo si, lo podemos hacer con uno dir entry que se apunte a si mismo desntrlo del inodo del archivo. 
        Si le ponemos el mismo nombre del archivo se va a quedar tildado


        
*/