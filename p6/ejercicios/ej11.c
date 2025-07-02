/*
    Implementar una función find_file_less_size(char * dir, int min_bytes, char * arch_nombre), que tome el path de un directorio, una cantidad de 
    bytes, y un nombre, y devuelva una lista con todos los archivos que tengan un tamaijo menor a min_bytes, cuyo nombre sea arch_nombre, a partir
    de dir (inclusive). La búsqueda deberá también considerar los subdirectorios del directorio dado (excepto ’.’ y ’..’).
*/

// me dan un path. Me tengo que meter al inodo de root y fijarme la lista de directorios, luego lo mismo hasta llegar al path

// voy a usar la estructura del inodo provista por la cátedra porque sino ni idea de como hacerlo


	struct __attribute__((__packed__)) Ext2FSInode {
		unsigned short mode;
		unsigned short uid;
		unsigned int size;
		unsigned int atime;
		unsigned int ctime;
		unsigned int mtime;
		unsigned int dtime;
		unsigned short gid;
		unsigned short links_count;
		unsigned int blocks;
		unsigned int flags;
		unsigned int os_dependant_1;
		unsigned int block[15];		
		unsigned int generation;
		unsigned int file_acl;
		unsigned int directory_acl;
		unsigned int faddr;
		unsigned int os_dependant_2[3];
	} ;

    typedef inode_t;
    extern int BLOCKS_ROOT;

void find_file_less_size(char * dir, int min_bytes, char * arch_nombre) {
    inode_t * root = load_inode(2); // supuestamente ya lo tenemos leido siempre asi que esto es al pedo
    int block;
    while (block < BLOCKS_ROOT)
    {
        
    }
    

}