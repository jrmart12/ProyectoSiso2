#include "fs.h"
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <stdlib.h>
#include "device.h"
Dir_Entry *dir;
unsigned char Map[TamanoBloque];

void load_dir(){
    int x=0;
    for(x=0;x<DIRSIZE;x++){
        device_read_block(reinterpret_cast<unsigned char*>(&dir[x * 4096]), x + 1);
    }
}

int get_free_block(){
    int bloques_ocupados;
    int primer_bit;
    int x;
    int y;
    for(x=0;x<512;x++){
        if(Map[x]==0){
            bloques_ocupados=x;
        }
    }
    for(y=0;y<8;y++){
        if((Map[bloques_ocupados]>>y&1)==1){
            primer_bit=y;break;
        }
    }
    int resultado=8*bloques_ocupados+primer_bit;
    return(resultado);
}
void set_busy_block(int bloque){
    int b=floor(bloque/8);
    int numero_bloque=bloque%8;
    Map[b]&=~(1<<numero_bloque);
}
void set_free_block(int bloque){
    int b=floor(bloque/8);
    int numero_bloque=bloque%8;
    Map[b]|=1<<numero_bloque;
}

struct Dir_Entry *entry(const char * path){
    int x;
    int y;
    for(x=0;x<DIRSIZE;x++){
        for(y=0;x<ENTBLOQUE;y++){
            if(strcmp(path,dir[x*4096+x*16].name)==0){
                return &dir[x*4096+x*16];
            }
        }
    }
}

void fs_init(struct fuse_conn_info *conn) {
    device_read_block(Map,0);
    load_dir();
}

int fs_mkdir(const char *path, mode_t mode) {
return 0;
}
