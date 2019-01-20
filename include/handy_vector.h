#include <stdlib.h>
#include <stdbool.h>

#ifndef HANDY_HANDY_VECTOR_H
#define HANDY_HANDY_VECTOR_H


typedef struct _handy_vector_struct * handy_vector;

struct _handy_vector_struct
{
    bool    (*set_at)   ( handy_vector self, void * item, int at );
    void *  (*get_at)   ( handy_vector self, int at );
    int     (*contain)  ( handy_vector self, void * item );
    bool    (*rem_at)   ( handy_vector self, int at );
    int     (*capacity) ( handy_vector self );
    void    (*free)     ( handy_vector self );

    void ** _bucket;
    int _capacity;
    int _size;
};


handy_vector handy_create_vector();

#endif //HANDY_HANDY_VECTOR_H
