#include "device.h"
#include "dir.h"
static FILE *file;

void device_new_disk(const char *path)
{
    file =fopen(path,"w+");

    unsigned char bloques_vacios[TamanoBloque];
    int x;
    int y;
    for(y=0;y<NBLOQUES;y++){
        for(x=0;x<TamanoBloque;x++){
            bloques_vacios[y]=0;
        }
        device_write_block(bloques_vacios,y);
    }
	unsigned char Map[TamanoBloque];

	for(int x = 0; x < TamanoBloque; x++){
		Map[x] = 0xFF;
	}
    device_write_block(Map, 0);

    unsigned char dir[4096];
    Dir_Entry dirs;
    for(int x=0;x<ENTBLOQUE;x++){
        memcpy(&dir[x*32],&dirs,sizeof(Dir_Entry));
    }
    for(int x=0;x<DIRSIZE;x++){
        device_write_block(dir,x+1);
    }
}

void device_open(const char *path){
    file=fopen(path,"r+");
    if(file==NULL){
        device_new_disk(path);
    }
}

void device_close()
{
    fflush(file);
    fclose(file);
}

int device_read_block(unsigned char buffer[], int block) 
{
    fseek(file, block*TamanoBloque, SEEK_SET);
	
    return ( fread(buffer, 1, TamanoBloque, file) == TamanoBloque );
}

int device_write_block(unsigned char buffer[], int block) 
{
    fseek(file, block*TamanoBloque, SEEK_SET);
	
    return ( fwrite(buffer, 1, TamanoBloque, file) == TamanoBloque );
}

void device_flush()
{
    fflush(file);
}
