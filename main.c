#include <fuse.h>
#include <stdio.h>
#include "fs.h"

struct fuse_operations sfs_oper;

int main(int argc, char *argv[]) {
    printf("mounting file system...\n");
    device_new_disk("jose");
    device_close();
    return 0;
}
//make
// dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
//dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc
//./mount.sh