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

typedef struct handy_obj * handy_Obj;
struct handy_obj
{
    void  * data;
    void  * key;

    size_t size;

    handy_Obj next;
    handy_Obj prev;
};
#endif

struct list_struct
{
    bool (*contain)         ( handy_list * l, void * item );
    bool (*add_front)       ( handy_list * l, void * item );
    bool (*add_back)        ( handy_list * l, void * item );
    bool (*add_at)          ( handy_list * l, void * item, int at );
    bool (*push)            ( handy_list * l, void * item );
    bool (*empty)           ( handy_list * l );

    void * (*get_front)     ( handy_list * l );
    void * (*get_back)      ( handy_list * l );
    void * (*get_at)        ( handy_list * l, int at );
    void * (*remove_front)  ( handy_list * l );
    void * (*remove_back)   ( handy_list * l );
    void * (*reverse)       ( handy_list * l );
    void * (*remove_at)     ( handy_list * l, int at );
    void * (*pop)           ( handy_list * l );
    void   (*free)          ( handy_list * l );
    void * (*top)           ( handy_list * l );

    handy_Obj first;
    handy_Obj last;

    int size;
};

extern handy_list handy_create_list();

#endif //HANDY_LIST_H