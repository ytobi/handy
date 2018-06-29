// header definition of handy_list( linked list ) data structure

#include <stdbool.h>
#include <wchar.h>

#ifndef HANDY_LIST_H
#define HANDY_LIST_H

typedef struct list_struct * handy_list;
typedef struct list_obj * List_Obj;

struct list_obj
{
    void  * data;
    size_t size;

    List_Obj next;
    List_Obj prev;
};

struct list_struct
{
    bool (*contain)         ( handy_list * l, void * item, size_t size );
    bool (*add_front)       ( handy_list * l, void * item, size_t size );
    bool (*add_back)        ( handy_list * l, void * item, size_t size );
    bool (*add_at)          ( handy_list * l, void * item, int at, size_t size );
    bool (*push)            ( handy_list * l, void * item, size_t size );
    bool (*empty)           ( handy_list * l );

    void * (*get_front)     ( handy_list * l, size_t size );
    void * (*get_back)      ( handy_list * l, size_t size );
    void * (*get_at)        ( handy_list * l, int at, size_t size );
    void * (*remove_front)  ( handy_list * l, size_t size );
    void * (*remove_back)   ( handy_list * l, size_t size );
    void * (*reverse)       ( handy_list * l );
    void * (*remove_at)     ( handy_list * l, int at, size_t size );
    void * (*pop)           ( handy_list * l, size_t size );
    void   (*free)          ( handy_list * l );

    List_Obj first;
    List_Obj last;

    int size;
};

extern handy_list create_handy_list();
extern bool handy_contain         ( handy_list * l, void * item, size_t size );
extern bool handy_add_front       ( handy_list * l, void * item, size_t size );
extern bool handy_add_back        ( handy_list * l, void * item, size_t size );
extern bool handy_add_at          ( handy_list * l, void * item, int at, size_t size );
extern bool handy_push            ( handy_list * l, void * item, size_t size );
extern bool handy_empty           ( handy_list * l );

extern void * handy_get_front     ( handy_list * l, size_t size );
extern void * handy_get_back      ( handy_list * l, size_t size );
extern void * handy_get_at        ( handy_list * l, int at, size_t size );
extern void * handy_remove_front  ( handy_list * l, size_t size );
extern void * handy_remove_back   ( handy_list * l, size_t size );
extern void * handy_reverse       ( handy_list * l );
extern void * handy_remove_at     ( handy_list * l, int at, size_t size );
extern void * handy_pop           ( handy_list * l, size_t size );
extern void   handy_free          ( handy_list * l );



#endif //HANDY_LIST_H
