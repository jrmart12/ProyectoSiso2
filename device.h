#ifndef DEVICE_H
#define DEVICE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "dir.h"
#define TamanoBloque 4096
#define NBLOQUES TamanoBloque*8
#define DIRSIZE (NBLOQUES*16)/TamanoBloque
#define ENTBLOQUE 4096/16
#ifdef __cplusplus
extern "C" {
#endif
void device_new_disk(const char *path);
void device_open(const char *path);
void device_close();
int device_read_block(unsigned char buffer[], int block);
int device_write_block(unsigned char buffer[], int block);
void device_format();
void device_flush();
#ifdef __cplusplus
}
#endif

#endif