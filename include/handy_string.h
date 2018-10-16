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
    bool (*append)          ( handy_string * s, char * data );
    bool (*equal)           ( handy_string * s1, handy_string * s2 );
    bool (*equal_str)       ( handy_string * s, char * str );

    bool (*contain_char)    ( handy_string * s, char c );
    bool (*contain_str)     ( handy_string * s, char * str );
    bool (*add_char_front)  ( handy_string * s, char c );
    bool (*add_char_back)   ( handy_string * s, char c );
    bool (*add_char_at)     ( handy_string * s, char c, int at );
    bool (*is_null)         ( handy_string * s );
    bool (*copy)            ( handy_string * des, handy_string * src );

    char * (*string)        ( handy_string * s );
    char (*get_front_char)  ( handy_string * s );
    char (*get_back_char)   ( handy_string * s );
    char (*get_char_at)     ( handy_string * s, int at );
    bool (*delete_front_char)( handy_string * s );
    bool (*delete_back_char)( handy_string * s );
    bool (*delete_char_at)  ( handy_string * s, int at );
    bool (*reverse)         ( handy_string * s );
    void (*free)            ( handy_string * s );
    int  (*length)          ( handy_string * s );

    char * data;

    int size;
};

handy_string handy_create_string();

#endif //HANDY_HANDY_STRING_H
