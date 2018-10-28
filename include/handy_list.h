// header definition of handy_list( linked list ) data structure

#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_LIST_H
#define HANDY_LIST_H

typedef struct _list_struct  * handy_list;

#ifndef HANDY_LIST_OBJ_H
#define HANDY_LIST_OBJ_H

typedef struct __handy_list_obj * _handy_list_obj;
struct __handy_list_obj
{
    void  * _data;

    _handy_list_obj _next;
    _handy_list_obj _prev;
};

#endif

struct _list_struct
{
    int  (*contain)         ( handy_list * l, void * item );
    bool (*add_front)       ( handy_list * l, void * item );
    bool (*add_back)        ( handy_list * l, void * item );
    bool (*add_at)          ( handy_list * l, void * item, int at );
    bool (*empty)           ( handy_list * l );

    void * (*get_front)     ( handy_list * l );
    void * (*get_back)      ( handy_list * l );
    void * (*get_at)        ( handy_list * l, int at );
    bool   (*rem_front)     ( handy_list * l );
    bool   (*rem_back)      ( handy_list * l );
    void * (*reverse)       ( handy_list * l );
    bool   (*rem_at)        ( handy_list * l, int at );
    void   (*free)          ( handy_list * l );

    _handy_list_obj _first;
    _handy_list_obj _last;

    int size;
};

extern handy_list handy_create_list();

#endif //HANDY_LIST_H
