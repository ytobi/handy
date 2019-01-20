// header definition of handy_list( linked list ) data structure

#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_LIST_H
#define HANDY_LIST_H

typedef struct _handy_list_struct  * handy_list;

#ifndef HANDY_LIST_OBJ_H
#define HANDY_LIST_OBJ_H

typedef struct __handy_list_obj * _handy_list_obj;

struct __handy_list_obj
{
    void  * _data;

    _handy_list_obj _next;
    _handy_list_obj _prev;
};

#endif // HANDY_LIST_OBJ_H

struct _handy_list_struct
{
    int  (*contain)         ( handy_list self, void * item );
    bool (*add_front)       ( handy_list self, void * item );
    bool (*add_back)        ( handy_list self, void * item );
    bool (*add_at)          ( handy_list self, void * item, int at );
    bool (*empty)           ( handy_list self );

    void * (*get_front)     ( handy_list self );
    void * (*get_back)      ( handy_list self );
    void * (*get_at)        ( handy_list self, int at );
    bool   (*rem_front)     ( handy_list self );
    bool   (*rem_back)      ( handy_list self );
    void   (*reverse)       ( handy_list self );
    bool   (*rem_at)        ( handy_list self, int at );
    void   (*free)          ( handy_list self );
    int    (*length)        ( handy_list self );

    _handy_list_obj _first;
    _handy_list_obj _last;

    int _size;
};

extern handy_list handy_create_list();

#endif //HANDY_LIST_H
