// header definition of handy_list( linked list ) data structure

#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_LIST_H
#define HANDY_LIST_H

typedef struct list_struct  * handy_list;

#ifndef HANDY_OBJ_H
#define HANDY_OBJ_H

typedef struct _handy_obj * handy_obj;
struct _handy_obj
{
    void  * _data;
    void  * _key;

    handy_obj _next;
    handy_obj _prev;
};

char * handy_str_return;
#endif

struct list_struct
{
    int  (*contain)         ( handy_list * l, void * item );
    bool (*add_front)       ( handy_list * l, void * item );
    bool (*add_back)        ( handy_list * l, void * item );
    bool (*add_at)          ( handy_list * l, void * item, int at );
    bool (*empty)           ( handy_list * l );

    char * (*to_string)     ( handy_list * l );
    void * (*get_front)     ( handy_list * l );
    void * (*get_back)      ( handy_list * l );
    void * (*get_at)        ( handy_list * l, int at );
    void * (*remove_front)  ( handy_list * l );
    void * (*remove_back)   ( handy_list * l );
    void * (*reverse)       ( handy_list * l );
    void * (*remove_at)     ( handy_list * l, int at );
    void   (*free)          ( handy_list * l );

    handy_obj _first;
    handy_obj _last;

    int size;
};

extern handy_list handy_create_list();

#endif //HANDY_LIST_H
