#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef HANDY_HANDY_STRING_H
#define HANDY_HANDY_STRING_H

typedef struct string_struct  * handy_string;

struct string_struct
{
    void (*handy_string)    ( char * data );
    bool (*init)            ( char * data, size_t size );
    bool (*equal)           ( handy_string * s, hjnmandy_string str );

    bool (*contain)         ( handy_string * s, void * item );
    bool (*add_front)       ( handy_string * s, void * item );
    bool (*add_back)        ( handy_string * s, void * item );
    bool (*add_at)          ( handy_string * s, void * item, int at );
    bool (*push)            ( handy_string * s, void * item );
    bool (*empty)           ( handy_string * s );

    void * (*get_front)     ( handy_string * s );
    void * (*get_back)      ( handy_string * s );
    void * (*get_at)        ( handy_string * s, int at );
    void * (*remove_front)  ( handy_string * s );
    void * (*remove_back)   ( handy_string * s );
    void * (*reverse)       ( handy_string * s );
    void * (*remove_at)     ( handy_string * s, int at );
    void * (*pop)           ( handy_string * s );
    void   (*free)          ( handy_string * s );
    void * (*top)           ( handy_string * s );
    int    (*length)        ( handy_string * s );

    char * data;

    int size;
};

#endif //HANDY_HANDY_STRING_H
