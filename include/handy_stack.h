#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_HANDY_STACK_H
#define HANDY_HANDY_STACK_H

typedef struct stack_struct * handy_stack;

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

struct stack_struct
{
    bool (*contain)         ( handy_stack * s, void * item );
    bool (*push)            ( handy_stack * s, void * item );
    bool (*empty)           ( handy_stack * s );

    void   (*reverse)       ( handy_stack * s );
    void * (*pop)           ( handy_stack * s );
    void   (*free)          ( handy_stack * s );
    void * (*top)           ( handy_stack * s );
    void * (*bottom)        ( handy_stack * s );

    _handy_stack_obj _first;
    _handy_stack_obj _last;

    int size;
};

extern handy_stack handy_create_stack();


#endif //HANDY_HANDY_STACK_H
