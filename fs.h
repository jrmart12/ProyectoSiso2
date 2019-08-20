#ifndef FS_H
#define FS_H

#include "device.h"
#include <math.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif
    int get_free_block();
    void set_busy_block(int block);
    void set_free_block(int block);
    void load_dir();
    struct Dir_Entry *entry(const char * path);

    void fs_init(struct fuse_conn_info *conn) ;
    int fs_mkdir(const char *path, mode_t mode) ;
#ifdef __cplusplus
}
#endif
#endif