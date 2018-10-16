#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "handy_list.h"

#ifndef HANDY_HANDY_HASHTBL_H
#define HANDY_HANDY_HASHTBL_H

typedef struct hashtbl_struct * handy_hashtbl;

#ifndef HASHTBL_OBJ_H
#define HASHTBL_OBJ_H
typedef struct _hashtbl_obj * hashtbl_obj;

struct _hashtbl_obj
{
    void * value;
    void * key;
};
#endif

struct hashtbl_struct
{
    bool (*contain)         ( handy_hashtbl * l, void * key );
    bool (*add)             ( handy_hashtbl * l, void * key, void * item );
    bool (*empty)           ( handy_hashtbl * l );

    void * (*get)           ( handy_hashtbl * l, void * key );
    void * (*remove)        ( handy_hashtbl * l, void * key );
    void   (*free)          ( handy_hashtbl * l );

    int size;

    handy_list * bucket;
};

extern handy_hashtbl handy_create_hashtbl();

#endif //HANDY_HANDY_HASHTBL_H
