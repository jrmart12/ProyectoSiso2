#include <fuse.h>
#include <stdio.h>
#include "fs.h"

struct fuse_operations sfs_oper;

int main(int argc, char *argv[]) {
	int fuse_stat;

    sfs_oper.mkdir=fs_mkdir;

    device_new_disk(argv[1]);
    fuse_stat=fuse_main(argc, argv, &sfs_oper,NULL);
    device_close();
    return fuse_stat;
}