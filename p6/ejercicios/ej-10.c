/*
    Se tiene un disco formateado con FAT para el cual se quiere poder devolver el contenido de un archivo a partir de su ruta absoluta. Para ello se 
    debe implementar la función:

        datos = cargar_archivo(directorios[])
    
    donde directorios es la lista de los nombres de los directorios de la ruta (ordenados, incluyendo el nombre del archivo, y sin incluir al 
    directorio raíz). Es decir, si el archivo a abrir es \Documentos\Users\foto.png entonces directorios = [’Documentos’, ’Users’, ’foto.png’].
    Para ello se cuenta con las siguientes funciones auxiliares:
        
        FAT_entry(block_address): devuelve la entrada de la tabla FAT de la posición block_address.
        
        raw_data = read_blocks(block_address1,block_address2,...): lee del disco todos los bloques indicados por parámetro, en orden.

        parse_directory_entries(raw_data): devuelve una lista de struct_entrada_directorio, donde cada elemento representa los subdirectorios 
                                           del directorio pasado en raw_data.

        raw_data = root_table(): devuelve los datos de la tabla de directorios de root.

    Se pide:
    a) Enumerar tres campos que debe tener la estructura struct_entrada_directorio según este tipo de filesystem.
    b) Escribir el pseudo-código de la función cargar_archivo
*/
extern int EOF;
unsigned char buffer[128];
// nos piden 3 campos que tenga que tener el directorio
typedef struct struct_entrada_directorio
{
    char* name;                 // necesitamos el nombre del dir o del archivo
    int first_block;            // Necesitamos saber donde arranca en la fat el directorio para poder leerlo
    int dir_por_si_o_por_no;    // qsy avisamos si es o no un dir porque puede ser un arvhivo

    // Ademas hago un compilado de lo que me dió el chat + lo de yago + lo de Uli

    int file_size;
    int name_length;

} dir_entry_t;

/*
    datos = cargar_archivo(directorios[]) --> tengo que imp

    FAT_entry(block_address) que devuelve la entrada de la tabla FAT de la posici´on block_address.

    raw_data = read_blocks(block_address1,block_address2,...) que lee del disco todos los bloques indicados por par´ametro, en orden.

    parse_directory_entries(raw_data) que devuelve una lista de struct_entrada_directorio que representan las entradas de directorio del directorio 
    pasado en raw_data.

    raw_data = root_table() que devuelve los datos de la tabla de directorios de root.

    a) Enumere tres campos que debe tener, seg´un este tipo de filesystem, la estructura struct_entrada_directorio.

        dir_entry {
            int block       --> addr del bloque que necesito
            char name[]     --> nombre del archivo
            int length      --> tamño del archivo
            int file_type   --> tipo del archivo 
        }

    b) Escribir el pseudo-c´odigo de la funci´on cargar_archivo.

        // Que queremos hacer? vamos a buscar por bloque cuales son los dir_entry que tiene y nos fijamso el nombre para ver el archivo
        *int cargar_archivo(directorios[]) {
            
            data_act = root_table() --> primero cargamos root

            for name in directorios:

                enties[] = parse_dir_ent(data_act)

                encontrado = 0

                for entry in entries:
                    if (entry.name == name):
                        encontrado = 1

                        // tenemos que cambiar data actual para poner el neuvo dir
                        entry_fat = FAT_entry(entry.block)

                        // ahora tenemos que leer hasta eof
                        buffer[].append(entry_fat)
                        while(entry_fat != EOF): 
                            entry_fat = fat_entry(entry_fat)
                            buffer.append(entry_fat)
                        
                        // cuando salimos del while tenemos en el buffer todos los bloques a leer que hacen al archivo
                        data_act = read_block(buffer)

                        // como lo pusimos en data_act cuando volvemos a iterar con el for van a ser otras entries
                        break
                    
                if(encontrado): 
                    break 
            
            return data_act
        }
*/