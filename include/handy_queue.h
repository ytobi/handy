#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_HANDY_QUEUE_H
#define HANDY_HANDY_QUEUE_H

typedef struct queue_struct * handy_queue;

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

struct queue_struct
{
    bool (*contain)         ( handy_queue * q, void * item );
    bool (*enqueue)         ( handy_queue * q, void * item );
    bool (*empty)           ( handy_queue * q );

    void * (*reverse)       ( handy_queue * q );
    void * (*dequeue)       ( handy_queue * q );
    void   (*free)          ( handy_queue * q );
    void * (*front)         ( handy_queue * q );
    void * (*back)          ( handy_queue * q );

    handy_Obj first;
    handy_Obj last;

    int size;
};

extern handy_queue handy_create_queue();

#endif //HANDY_HANDY_QUEUE_H
