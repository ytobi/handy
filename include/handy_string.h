#include <stdbool.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef HANDY_HANDY_STRING_H
#define HANDY_HANDY_STRING_H

typedef struct string_struct  * handy_string;

struct string_struct
{
    void (*append_int)      ( handy_string self, long long num );
    void (*append_double)   ( handy_string self, double num );
    bool (*append)          ( handy_string self, char * str );
    bool (*equal)           ( handy_string self, handy_string str );
    bool (*equal_str)       ( handy_string self, char * str );

    int (*contain_char)     ( handy_string self, char c );
    int (*contain_str)      ( handy_string self, char * str );
    bool (*add_char_front)  ( handy_string self, char c );
    bool (*add_char_back)   ( handy_string self, char c );
    bool (*add_char_at)     ( handy_string self, char c, int at );
    bool (*is_null)         ( handy_string self );
    bool (*copy)            ( handy_string des, handy_string src );

    void (*to_upper)        ( handy_string self );
    void (*to_lower)        ( handy_string self );

    char * (*string)        ( handy_string self );
    char (*get_front_char)  ( handy_string self );
    char (*get_back_char)   ( handy_string self );
    char (*get_char_at)     ( handy_string self, int at );
    bool (*del_front_char)  ( handy_string self );
    bool (*del_back_char)   ( handy_string self );
    bool (*del_char_at)     ( handy_string self, int at );
    void (*reverse)         ( handy_string self );
    int  (*word_count)      ( handy_string self, char * delimiter );
    void (*free)            ( handy_string self );
    int  (*length)          ( handy_string self );


    char * _data;

    int _size;
};

handy_string handy_create_string();

#endif //HANDY_HANDY_STRING_H
