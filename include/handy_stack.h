#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_HANDY_STACK_H
#define HANDY_HANDY_STACK_H

typedef struct _handy_stack_struct * handy_stack;

#ifndef HANDY_STACK_OBJ_H
#define HANDY_STACK_OBJ_H

typedef struct __handy_stack_obj * _handy_stack_obj;

struct __handy_stack_obj
{
    void  * _data;

    _handy_stack_obj _next;
    _handy_stack_obj _prev;
};

#endif

struct _handy_stack_struct
{
    bool (*contain)         ( handy_stack self, void * item );
    bool (*push)            ( handy_stack self, void * item );
    bool (*empty)           ( handy_stack self );

    void   (*reverse)       ( handy_stack self );
    void * (*pop)           ( handy_stack self );
    void   (*free)          ( handy_stack self );
    void * (*top)           ( handy_stack self );
    void * (*bottom)        ( handy_stack self );
    int    (*length)        ( handy_stack self );

    _handy_stack_obj _first;
    _handy_stack_obj _last;

    void ** _handy_poped;

    int _size;
};

extern handy_stack handy_create_stack();


#endif //HANDY_HANDY_STACK_H
