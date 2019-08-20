#ifndef DIR_H
#define DIR_H

struct Dir_Entry
{
    char name[10];
    int index_block;
    char isDir;
};

#endif