#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_HANDY_HASHTBL_H
#define HANDY_HANDY_HASHTBL_H

typedef struct hashtbl_struct * handy_hashtbl;

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

struct hashtbl_struct
{
    bool (*contain)         ( handy_hashtbl * l, void * key, size_t size );
    bool (*add_front)       ( handy_hashtbl * l, void * item, void * key, size_t size );
    bool (*add_back)        ( handy_hashtbl * l, void * item, void * key, size_t size );
    bool (*add_at)          ( handy_hashtbl * l, void * item, void * key, int at, size_t size );
    bool (*push)            ( handy_hashtbl * l, void * item, void * key, size_t size );
    bool (*empty)           ( handy_hashtbl * l );

    void * (*get_front)     ( handy_hashtbl * l, size_t size );
    void * (*get_back)      ( handy_hashtbl * l, size_t size );
    void * (*get_at)        ( handy_hashtbl * l, int at, size_t size );
    void * (*remove_front)  ( handy_hashtbl * l, size_t size );
    void * (*remove_back)   ( handy_hashtbl * l, size_t size );
    void * (*reverse)       ( handy_hashtbl * l );
    void * (*remove_at)     ( handy_hashtbl * l, void * key, size_t size );
    void * (*pop)           ( handy_hashtbl * l, size_t size );
    void   (*free)          ( handy_hashtbl * l );
    void * (*top)           ( handy_hashtbl * l, size_t size );
    void * (*hash_function) ( handy_hashtbl * h1, handy_hashtbl * h2 );

    handy_Obj first;
    handy_Obj last;

    int size;
};

extern handy_hashtbl handy_create_hashtbl();

#endif //HANDY_HANDY_HASHTBL_H
