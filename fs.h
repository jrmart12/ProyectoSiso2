#ifndef FS_H
#define FS_H

#include "device.h"
#include <fuse.h>
#include <string.h>
#include "dir.h"

int get_free_block();
void set_busy_block(int block);
void set_free_block(int block);
void load_dir();
struct Dir_Entry *entry(const char * path);

void fs_init(struct fuse_conn_info *conn) ;
int fs_mkdir(const char *path, mode_t mode) ;

#endif