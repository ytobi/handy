#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_HANDY_STACK_H
#define HANDY_HANDY_STACK_H

typedef struct stack_struct * handy_stack;

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

struct stack_struct
{
    bool (*contain)         ( handy_stack * l, void * item );
    bool (*push)            ( handy_stack * l, void * item );
    bool (*empty)           ( handy_stack * l );

    void * (*reverse)       ( handy_stack * l );
    void * (*pop)           ( handy_stack * l );
    void   (*free)          ( handy_stack * l );
    void * (*top)           ( handy_stack * l );
    void * (*end)           ( handy_stack * l );

    handy_Obj first;
    handy_Obj last;

    int size;
};

extern handy_stack handy_create_stack();


#endif //HANDY_HANDY_STACK_H
