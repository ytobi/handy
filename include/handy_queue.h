#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_HANDY_QUEUE_H
#define HANDY_HANDY_QUEUE_H

typedef struct _queue_struct * handy_queue;

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
#endif

struct _queue_struct
{
    bool (*contain)         ( handy_queue * q, void * item );
    bool (*enqueue)         ( handy_queue * q, void * item );
    bool (*empty)           ( handy_queue * q );

    void   (*reverse)       ( handy_queue * q );
    void * (*dequeue)       ( handy_queue * q );
    void   (*free)          ( handy_queue * q );
    void * (*front)         ( handy_queue * q );
    void * (*back)          ( handy_queue * q );

    handy_obj _first;
    handy_obj _last;

    int size;
};

extern handy_queue handy_create_queue();

#endif //HANDY_HANDY_QUEUE_H
