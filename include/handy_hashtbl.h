#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "handy_list.h"

#ifndef HANDY_HANDY_HASHTBL_H
#define HANDY_HANDY_HASHTBL_H

typedef struct _hashtbl_struct * handy_hashtbl;

#ifndef HANDY_HASHTBL_OBJ_H
#define HANDY_HASHTBL_OBJ_H

typedef struct __handy_hashtbl_obj * _handy_hashtbl_obj;

struct __handy_hashtbl_obj
{
    void * _value;
    void * _key;
};
#endif

struct _hashtbl_struct
{
    bool (*contain)         ( handy_hashtbl * l, char * key );
    bool (*add)             ( handy_hashtbl * l, char * key, void * item );

    void * (*get)           ( handy_hashtbl * l, char * key );
    void   (*remove)        ( handy_hashtbl * l, char * key );
    void   (*free)          ( handy_hashtbl * l );

    int _size;

    handy_list * _bucket;
};

extern handy_hashtbl handy_create_hashtbl();

#endif //HANDY_HANDY_HASHTBL_H
