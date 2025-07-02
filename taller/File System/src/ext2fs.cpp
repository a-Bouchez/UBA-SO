#include "ext2fs.h"
#include "hdd.h"
#include "pentry.h"
#include "mbr.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdlib>

Ext2FS::Ext2FS(HDD & disk, unsigned char pnumber) : _hdd(disk), _partition_number(pnumber)
{
	assert(pnumber <= 3);

	// Load Superblock
	unsigned char * buffer = new unsigned char[2*SECTOR_SIZE];

	// Get partition info
	const PartitionEntry & pentry = _hdd[_partition_number];

	// Skip first two sectors & read 3rd and 4th sectors
	// Warning: We assume common sector size of 512bytes but it may not be true
	_hdd.read(pentry.start_lba()+2, buffer);
	_hdd.read(pentry.start_lba()+3, buffer+SECTOR_SIZE);

	// Warning: this only works in Little Endian arhitectures
	_superblock = (struct Ext2FSSuperblock *) buffer;

	// Load Block Group Table

	// Compute block size by shifting the value 1024
	unsigned int block_size = 1024 << _superblock->log_block_size;
	unsigned int sectors_per_block = block_size / SECTOR_SIZE;

	// Compute amount of block groups in FS
	_block_groups = _superblock->blocks_count / _superblock->blocks_per_group;

	if((_superblock->blocks_count % _superblock->blocks_per_group) != 0)
	{
		_block_groups++;
	}
	std::cerr << "block_groups: " << _block_groups << std::endl;

	// Allocate enough memory to keep the table
	_bgd_table = new Ext2FSBlockGroupDescriptor[_block_groups];

	// Since the size of the table is not forced to be a factor of SECTOR_SIZE
	// we need to compute the amount of sectors we should read and then copy
	// one by one the descriptors into the table in the apropriate order.
	unsigned int size_of_bgd_table = sizeof(Ext2FSBlockGroupDescriptor) * _block_groups;
	unsigned int bgd_table_sectors = size_of_bgd_table / SECTOR_SIZE;
	if((size_of_bgd_table % SECTOR_SIZE) != 0)
	{
		bgd_table_sectors++;
	}
	std::cerr << "bgd_table_sectors: " << bgd_table_sectors << std::endl;

	buffer = new unsigned char[bgd_table_sectors * SECTOR_SIZE];
	for(unsigned int i = 0; i < bgd_table_sectors; i++)
	{
		std::cerr << "pentry.start_lba()+4+i: " << (unsigned int) (pentry.start_lba()+4+i) << " buffer+(SECTOR_SIZE*i): " << (unsigned char *) (buffer+(SECTOR_SIZE*i)) << std::endl;
		_hdd.read(pentry.start_lba()+4+i, buffer+(SECTOR_SIZE*i));
	}

	// Copy descriptors into table
	for(unsigned int i = 0; i < _block_groups; i++)
	{
		_bgd_table[i] = *((Ext2FSBlockGroupDescriptor *) (buffer+(i*sizeof(Ext2FSBlockGroupDescriptor))));
	}
	delete[] buffer;
}

unsigned int Ext2FS::blockgroup_for_inode(unsigned int inode)
{
	assert(inode > 0);
	return (inode - 1) / _superblock->inodes_per_group;
}

unsigned int Ext2FS::blockgroup_inode_index(unsigned int inode)
{
	assert(inode > 0);
	return (inode - 1) % _superblock->inodes_per_group;
}

// Free allocated memory
Ext2FS::~Ext2FS()
{
	delete[] _superblock;
	delete[] _bgd_table;
}

struct Ext2FSSuperblock * Ext2FS::superblock()
{
	return _superblock;
}

unsigned int Ext2FS::block_groups()
{
	return _block_groups;
}

struct Ext2FSBlockGroupDescriptor * Ext2FS::block_group(unsigned int index)
{
	assert(index < _block_groups);
	return & _bgd_table[index];
}

std::ostream & operator<<(std::ostream & output, const struct Ext2FSInode & inode)
{
	output << "mode: " << inode.mode << std::endl;
	output << "uid: " << inode.uid << std::endl;
	output << "size: " << inode.size << std::endl;
	output << "atime: " << inode.atime << std::endl;
	output << "ctime: " << inode.ctime << std::endl;
	output << "mtime: " << inode.mtime << std::endl;
	output << "dtime: " << inode.dtime << std::endl;
	output << "gid: " << inode.gid << std::endl;
	output << "links_count: " << inode.links_count << std::endl;
	output << "blocks: " << inode.blocks << std::endl;
	output << "flags: " << inode.flags << std::endl;
	//output << "os_dependant_1: " << inode.os_dependant_1 << std::endl;

	//output << std::hex;
	for(unsigned int i = 0; i < 15; i++)
		output << "block[" << i << "]: " << inode.block[i] << std::endl;
	//output << std:dec;

	output << "generation: " << inode.generation << std::endl;
	output << "file_acl: " << inode.file_acl << std::endl;
	output << "directory_acl: " << inode.directory_acl << std::endl;
	output << "faddr: " << inode.faddr << std::endl;
	//output << "os_dependant_2: " << inode.os_dependant_2 << std::endl[3];

	return output;
}

std::ostream & operator<<(std::ostream & output, const struct Ext2FSSuperblock & superblock)
{
	output << "inodes_count: " << superblock.inodes_count << std::endl;
	output << "blocks_count: " << superblock.blocks_count << std::endl;
	output << "reserved_blocks_count: " << superblock.reserved_blocks_count << std::endl;
	output << "free_blocks_count: " << superblock.free_blocks_count << std::endl;
	output << "free_inodes_count: " << superblock.free_inodes_count << std::endl;
	output << "first_data_block: " << superblock.first_data_block << std::endl;
	output << "log_block_size: " << superblock.log_block_size << std::endl;
	output << "log_fragment_size: " << superblock.log_fragment_size << std::endl;
	output << "blocks_per_group: " << superblock.blocks_per_group << std::endl;
	output << "fragments_per_group: " << superblock.fragments_per_group << std::endl;
	output << "inodes_per_group: " << superblock.inodes_per_group << std::endl;
	output << "mount_time: " << superblock.mount_time << std::endl;
	output << "write_time: " << superblock.write_time << std::endl;
	output << "mount_count: " << superblock.mount_count << std::endl;
	output << "max_mount_count: " << superblock.max_mount_count << std::endl;
	output << "magic_bytes: " << superblock.magic_bytes << std::endl;
	output << "state: " << superblock.state << std::endl;
	output << "errors: " << superblock.errors << std::endl;
	output << "minor_revision_level: " << superblock.minor_revision_level << std::endl;
	output << "lastcheck: " << superblock.lastcheck << std::endl;
	output << "checkinterval: " << superblock.checkinterval << std::endl;
	output << "creator_os: " << superblock.creator_os << std::endl;
	output << "revision_level: " << superblock.revision_level << std::endl;
	output << "default_reserved_userid: " << superblock.default_reserved_userid << std::endl;
	output << "default_reserved_groupid: " << superblock.default_reserved_groupid << std::endl;
	// -- EXT2_DYNAMIC_REV Specific --
	output << "first_inode: " << superblock.first_inode << std::endl;
	output << "inode_size: " << superblock.inode_size << std::endl;
	output << "block_group_number: " << superblock.block_group_number << std::endl;
	output << "feature_compatibility: " << superblock.feature_compatibility << std::endl;
	output << "feature_incompatibility: " << superblock.feature_incompatibility << std::endl;
	output << "readonly_feature_compatibility: " << superblock.readonly_feature_compatibility << std::endl;
	output << "uuid: ";
	for(int i = 0; i < 16; i++)
		output << superblock.uuid[i];
	output << std::endl;
	output << "volume_name: ";
	for(int i = 0; i < 16; i++)
		output << superblock.volume_name[i];
	output << std::endl;
	output << "last_mounted: ";
	for(int i = 0; i < 64; i++)
		output << superblock.last_mounted[i];
	output << std::endl;
	output << "algo_bitmap: " << superblock.algo_bitmap << std::endl;
	// Performance hints
	output << "prealloc_blocks: " << (unsigned int) superblock.prealloc_blocks << std::endl;
	output << "prealloc_dir_blocks: " << (unsigned int) superblock.prealloc_dir_blocks << std::endl;
	//char alignment[2];
	// Journaling support
	output << "journal_uuid: ";
	for(int i = 0; i < 16; i++)
		output << superblock.journal_uuid[i];
	output << std::endl;
	output << "journal_inode: " << superblock.journal_inode << std::endl;
	output << "journal_device: " << superblock.journal_device << std::endl;
	output << "last_orphan: " << superblock.last_orphan << std::endl;
	// Directory indexing support
	output << "hash_seed: ";
	for(int i = 0; i < 4; i++)
		output << superblock.hash_seed[i];
	output << std::endl;
	output << "default_hash_version: " << (unsigned int) superblock.default_hash_version << std::endl;
	//char padding[3];
	// Other options
	output << "default_mount_options: " << superblock.default_mount_options << std::endl;
	output << "first_meta_bg: " << superblock.first_meta_bg << std::endl;
	//char unused[760];

	return output;
}

std::ostream & operator<<(std::ostream & output, const struct Ext2FSBlockGroupDescriptor & bg_descriptor)
{
	output << "block_bitmap: " << bg_descriptor.block_bitmap << std::endl;
	output << "inode_bitmap: " << bg_descriptor.inode_bitmap << std::endl;
	output << "inode_table: " << bg_descriptor.inode_table << std::endl;
	output << "free_blocks_count: " << bg_descriptor.free_blocks_count << std::endl;
	output << "free_inodes_count: " << bg_descriptor.free_inodes_count << std::endl;
	output << "used_dirs_count: " << bg_descriptor.used_dirs_count << std::endl;

	return output;
}

std::ostream & operator<<(std::ostream & output, const struct Ext2FSDirEntry & dent)
{
	output << "inode: " << dent.inode << std::endl;
	output << "record_length: " << dent.record_length << std::endl;
	output << "name_length: " << (unsigned short) dent.name_length << std::endl;
	output << "file_type: " << (unsigned short) dent.file_type << std::endl;

	// NULL terminate dent name
	char * dentname = new char[dent.name_length + 1];
	strncpy(dentname, dent.name, dent.name_length);
	dentname[dent.name_length] = '\0';

	output << "name: " << dentname << std::endl;

	delete[] dentname;

	return output;
}

struct Ext2FSInode * Ext2FS::inode_for_path(const char * path)
{
	char * mypath = new char[strlen(path)+1];
	mypath[strlen(path)] = '\0';
	strncpy(mypath, path, strlen(path));

	char * pathtok = strtok(mypath, PATH_DELIM);
	struct Ext2FSInode * inode = NULL;

	while(pathtok != NULL)
	{
		struct Ext2FSInode * prev_inode = inode;
		// std::cerr << "pathtok: " << pathtok << std::endl;
		inode = get_file_inode_from_dir_inode(prev_inode, pathtok);
		pathtok = strtok(NULL, PATH_DELIM);

		delete prev_inode;
	}

	delete[] mypath;
	return inode;
}

unsigned int Ext2FS::blockaddr2sector(unsigned int block)
{
	// Get partition info
	const PartitionEntry & pentry = _hdd[_partition_number];

	// Compute block size by shifting the value 1024
	unsigned int block_size = 1024 << _superblock->log_block_size;
	unsigned int sectors_per_block = block_size / SECTOR_SIZE;

	return pentry.start_lba() + block * sectors_per_block;
}

/**
 * Warning: This method allocates memory that must be freed by the caller
 */
struct Ext2FSInode * Ext2FS::load_inode(unsigned int inode_number)
{
	int block_size = 1024 << _superblock->log_block_size;

	uint inode_size = _superblock->inode_size;

	uint numero_grupo = blockgroup_for_inode(inode_number);
	Ext2FSBlockGroupDescriptor* grupo = block_group(numero_grupo);
	uint indice_en_blockgroup_inodo = blockgroup_inode_index(inode_number);

	uint inodo_table = grupo->inode_table;

	uint inodes_per_block = block_size / inode_size;

	uint block_index = indice_en_blockgroup_inodo / inodes_per_block;
	uint inode_index_in_block = indice_en_blockgroup_inodo % inodes_per_block;

	uint block_address = inodo_table + block_index;

	unsigned char * bloque_del_inodo = (unsigned char *) malloc(block_size);
	read_block(block_address, bloque_del_inodo);

	Ext2FSInode * inodo =(Ext2FSInode *) malloc(inode_size);

	Ext2FSInode * tmp = (Ext2FSInode*)bloque_del_inodo;
	memcpy(inodo,&tmp[inode_index_in_block], inode_size);

	free(bloque_del_inodo);
	return inodo;
}


/*
	las direcciones LBA ocupan 4 bytes.
	Nos dan inodo y numero del bloque dentro del inodo

	esta es la estructura del inodo:

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
		unsigned int block[15];		 ESTO ES LO INTERESANTE!!!! aca hay del 0 al 11 bloques directos, 12 ind simples, 13 es ind doble y 14 bloque ind trip
		unsigned int generation;
		unsigned int file_acl;
		unsigned int directory_acl;
		unsigned int faddr;
		unsigned int os_dependant_2[3];
	};

	Esta funci´on debe devolver la direcci´on LBA (Logical Block Address) correspondiente a un bloque de dato

	por enunciado sabemos que si es menor a 12 tenemos ahi el bloque y lo mandamos 

	si es mayor a 12 separamos en 12 y 13 y en caso 14
*/
unsigned int Ext2FS::get_block_address(struct Ext2FSInode * inode, unsigned int block_number)
{

	int block_size = 1024 << _superblock->log_block_size;
	uint cant_LBA = block_size / 4;

	// caso: bloque directo

	if (block_number < 12)
	{
		return inode->block[block_number];
	}

	// caso: bloque indirecto simple

	/*
		por alguna razon que desconozco el block number funciona así:
			normal si es menor a 12 lo cual tiene todo el sentido del mundo 
			Si pasa los 12 se pone todo loco 
				- si esta entre 12 y 15 es simple, por que? porque al ser simple puede apuntar a cuantos LBA entran en un bloque y como las dirs de LBA ocupan 4 bytes tenemos que hacer block_size/4
				- que pasa si es mayor a 15? es doble ind y se vuelve a poner todo muy loco
	*/ 
	block_number -= 12;
	if (block_number < cant_LBA)
	{
		// vamos a tener que leer el bloque, este es un bloque que apunta a LBA
		unsigned char* simple_table = (unsigned char*) malloc(block_size); // le pido espacio a dios y como solo le dije la cantidad de espacio le digo entre ()
		read_block(inode->block[12], simple_table);
		unsigned int tmp = ((unsigned int*)simple_table)[block_number]; // recordemos que le sacamos 12 para poder usarlo de indice acá, usamos var esta para poder hacer el free
		free(simple_table); // todo lo que se le pide a dios se le dueveulve
		return tmp;
	}

	/*
		Esto hay que pensarlo asi:

		| directos (12) | indirecto simple (cant_lba) | Doble indirecto (cant_lba²) | Triple indirecto |
           	↑               ↑                           ↑
 		  original       restar 12                     restar CANR_LBA

		La cosa es usamos el normal hasta el 12
		Restamos 12 y si eso es menor a cantidad de punteros a LBA es indirecto
		Restamos Cannt_lba y llegamos a los indices del dobre directo y es de ese tipo si lo que queda es menor a cant_lba². Por qué?
		porque tenemos un bloque donde entran 4 LBAS que apuntan a 4 LBAS por lo que la cnatidad de bloques es cant_lba²

	*/
	block_number -= cant_LBA;
	// caso: bloque indirecto doble
	if (block_number < cant_LBA*cant_LBA)
	{
		
		u_int32_t double_index = block_number / cant_LBA;
		u_int32_t simple_index = block_number % cant_LBA;

		unsigned char* double_table = (unsigned char*) malloc(block_size);
		unsigned char* simple_table = (unsigned char*) malloc(block_size);

		read_block(inode->block[13], double_table);
		read_block(((uint*)double_table)[double_index], simple_table);

		uint tmp = ((uint*)simple_table)[simple_index];
		free(double_table);
		free(simple_table);
		return tmp;
	}
	
	// caso bloque triple
	return -1; // no implementamos
}

void Ext2FS::read_block(unsigned int block_address, unsigned char * buffer)
{
	unsigned int block_size = 1024 << _superblock->log_block_size;
	unsigned int sectors_per_block = block_size / SECTOR_SIZE;
	for(unsigned int i = 0; i < sectors_per_block; i++) {
		_hdd.read(blockaddr2sector(block_address)+i, buffer+i*SECTOR_SIZE);
	}
}

/*
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
	unsigned int block[15];			leemos cada uno de estos
	unsigned int generation;
	unsigned int file_acl;
	unsigned int directory_acl;
	unsigned int faddr;
	unsigned int os_dependant_2[3];
};

en cada uno de los bloques tenemos esto, pensalo como una tablita que te dice lo que necesitas pero para acceder si o si hay que leer el bloque
struct __attribute__((__packed__)) Ext2FSDirEntry {
	unsigned int inode;				a cual apunta
	unsigned short record_length;	tamaño de la entrada
	unsigned char name_length;		tamaño del nombre
	unsigned char file_type;		ni idea
	char name[];					nombre del archivo
};
*/

struct Ext2FSInode * Ext2FS::get_file_inode_from_dir_inode(struct Ext2FSInode * from, const char * filename)
{
	if(from == NULL)
		from = load_inode(EXT2_RDIR_INODE_NUMBER);
	//std::cerr << *from << std::endl;
	assert(INODE_ISDIR(from));

	//TODO: Ejercicio 3

	// arrancamos definiendo vars que nos pueden llegar a servir 
	uint block_size = 1024 << _superblock->log_block_size;
	uint block_number= 0;
	uint inode_res = 0;

	uint blocks_in_use = from->blocks;

	// buffer al que vamos a leer y un puntero a un directorio para que despues de leer podemso usarlo como esa estructura
	unsigned char * buffer1 = (unsigned char *) malloc(block_size*2);
	unsigned char * buffer2 = buffer1+block_size;

	struct Ext2FSDirEntry * dir_entry;

	uint tam_bytes = 0;
	// la idea es recorrer los bloques en uso, leerlos y luego leer las Ext2FSDirEntry en cada uno de estos bloques y ver donde esta el archivo	

	// chequeamos que hayan bloques en uso --> que el dir no este vacio
	
	//recorremos todos los bloques, si lo encontramos antes hacemos un break

	while (block_number < blocks_in_use)
	{
		// paso 1: leemos el bloque actual para ver si tiene o no el archivo
			// aca nos tendriamos que saltear los primeros 2 que son . y .. (actual y padre) pero primero veamos si funciona
		
		// para poder acceder a cada bloque vamos a necesitar un indice --> hay que hacerlo afuera del loopblo

		uint lba = get_block_address(from,block_number);			// obtenemos la lba del bloque
		read_block(lba, buffer1);									// leemos lo que hay eb el bloque
		Ext2FSDirEntry *dir_entry = (Ext2FSDirEntry *) buffer1; 	// agarramos el primer dir


		uint lba2 = get_block_address(from,block_number +1);		// obtenemos la lba del bloque
		read_block(lba2, buffer2);									// leemos lo que hay en el segundo bloque

		// ahora, dentro de cada bloque no hay solo una Ext2FSDirEntry, asi que dentro del buffer vamos a tener mychas de estas
		// paso 2: iterar por las Ext2FSDirEntry y ver sus archivos 
		
		// mi puntero a la dir de memoria actual es menor al puntero inicial del buffer mas el tamaño del bloque, recordar que no arranca en el 0
		
		while ((unsigned char *) dir_entry < buffer1 + block_size) {
			
			
			// llegue al final del inodo
			if (tam_bytes >= from->size)
			{
				break;
			}

			//  Comparar nombre con lo pedido, primero si son mimsa long y despues si es el mismo
			if (dir_entry->name_length == strlen(filename) && strncmp(dir_entry->name, filename, dir_entry->name_length) == 0) {
				inode_res = dir_entry->inode; // actualizamos respuesta
				break; // al pedo seguir mirnado el resto de bloques
			}
			
			// cc pasamos al siguiente registro:
			tam_bytes += dir_entry->record_length;
			dir_entry = (Ext2FSDirEntry *)(((char *) dir_entry) + dir_entry->record_length);
    	}

		// si ya encontramos el inodo nos las tomamos, loopeo al pedo no
		if (inode_res != 0)
		{
			break;
		}
		
		block_number ++;
	}
	
	// liberamos el buffer -> todo lo que se le pide a dios se le devuelve
	free(buffer1);

	// no encontramos el inodo
	if (inode_res == 0)
	{
		return NULL;
	}
	
	// encontramos el inodo que apunta al archivo
	return load_inode(inode_res);
}

fd_t Ext2FS::get_free_fd()
{
	for(fd_t fd = 0; fd < EXT2_MAX_OPEN_FILES; fd++)
	{
		// Warning: This is inefficient
		if(!(_fd_status[fd/sizeof(unsigned int)] & (1 << (fd % sizeof(unsigned int)))))
			return fd;
	}
	return -1;
}

void Ext2FS::mark_fd_as_used(fd_t fd)
{

	_fd_status[fd/sizeof(unsigned int)] = (_fd_status[fd/sizeof(unsigned int)] | (1 << (fd % sizeof(unsigned int))));
}

void Ext2FS::mark_fd_as_free(fd_t fd)
{

	_fd_status[fd/sizeof(unsigned int)] = (_fd_status[fd/sizeof(unsigned int)] ^ (1 << (fd % sizeof(unsigned int))));
}

fd_t Ext2FS::open(const char * path, const char * mode)
{
	fd_t new_fd = get_free_fd();
	if(new_fd < 0)
		return -1;
	mark_fd_as_used(new_fd);

	// We ignore mode
	struct Ext2FSInode * inode = inode_for_path(path);

	if(inode == NULL)
		return -1;

	_open_files[new_fd] = *inode;
	delete inode;
	_seek_memory[new_fd] = 0;

	return new_fd;
}

int Ext2FS::read(fd_t filedesc, unsigned char * buffer, int size)
{
	int realsize = ((_seek_memory[filedesc] + size) >= _open_files[filedesc].size)?_open_files[filedesc].size-_seek_memory[filedesc]:size;
	if(realsize > 0)
	{
		int seek = _seek_memory[filedesc];
		unsigned int read = 0;

		// Compute block size by shifting the value 1024
		unsigned int block_size = 1024 << _superblock->log_block_size;
		unsigned int sectors_per_block = block_size / SECTOR_SIZE;

		unsigned int start_block = (seek / block_size);
		unsigned int end_block = ((seek + realsize - 1) / block_size);


		for(unsigned int block = start_block; block <= end_block; block++)
		{
			unsigned int block_address = get_block_address(&_open_files[filedesc], block);

			unsigned char block_buf[block_size];
			read_block(block_address, block_buf);

			do
			{
				buffer[read++] = block_buf[seek++ % block_size];
			} while(((seek % block_size) != 0) && (read < realsize));
		}
	}
	return realsize;
}

int Ext2FS::write(fd_t filedesc, const unsigned char * buffer, int size)
{
	return -1;
}

int Ext2FS::seek(fd_t filedesc, int offset)
{
	//std::cerr << "offset: " << offset << " size: " << _open_files[filedesc].size << std::endl;
	int position = offset;
	if(offset < 0)
		position = _open_files[filedesc].size + offset;
	if(position >= _open_files[filedesc].size)
		position = _open_files[filedesc].size - 1;
	_seek_memory[filedesc] = position;
	return position;
}

int Ext2FS::tell(fd_t filedesc)
{
	return _seek_memory[filedesc];
}

void Ext2FS::close(fd_t filedesc)
{
	mark_fd_as_free(filedesc);
}
