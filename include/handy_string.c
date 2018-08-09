//
// Created by tobi on 7/13/18.
//

#include "handy_string.h"

bool handy_add_string      ( handy_string * s, char * data,  size_t size );
bool handy_equal           ( handy_string * s1, handy_string s2 );
bool handy_equal_str       ( handy_string * s, char * str );

bool handy_contain_char    ( handy_string * s, char c );
bool handy_contain_str     ( handy_string * s, char * str );
bool handy_add_front       ( handy_string * s, char c );
bool handy_add_back        ( handy_string * s, char c );
bool handy_add_at          ( handy_string * s, char c, int at );
bool handy_null            ( handy_string * s );

char handy_get_front       ( handy_string * s );
char handy_get_back        ( handy_string * s );
char handy_get_at          ( handy_string * s, int at );
void * handy_delete_front  ( handy_string * s );
void * handy_delete_back   ( handy_string * s );
void handy_delete_at       ( handy_string * s, int at );
void handy_reverse         ( handy_string * s );
void handy_free            ( handy_string * s );
int  handy_length          ( handy_string * s );


handy_string handy_create_string( )
{
    handy_string temp = malloc( sizeof(*temp) );

    temp->data = malloc( sizeof(char) );
    temp->size = 0;
    temp->data[0] = '\0';

    temp->add_string = handy_add_string;
    temp->equal = handy_equal;
    temp->equal_str = handy_equal_str;
    temp->contain_char = handy_contain_char;
    temp->contain_str = handy_contain_str;
    temp->add_front = handy_add_front;

    return temp;
}

bool handy_add_string      ( handy_string * s, char * str, size_t size )
{
    char * temp_hold = malloc( (*s)->size * sizeof(char) );
    memcpy( &temp_hold, &((*s)->data), ((*s)->size) );


    if( realloc( ((*s)->data), (size + (*s)->size) ) == NULL ) // TODO
        return false;

    memcpy( &((*s)->data), &temp_hold, ((*s)->size) );
    memcpy( &((*s)->data), &str, size );

    (*s)->size += size;

    free( temp_hold );
}
bool handy_equal           ( handy_string * s1, handy_string s2 )
{
    if( strcmp( (*s1)->data, (*s2).data ) == 0 )
        return true;
    return false;
}
bool handy_equal_str       ( handy_string * s1, char * s2 )
{
    if( strcmp( (*s1)->data, s2 ) == 0 )
        return true;
    return false;
}
bool handy_contain_char    ( handy_string * s, char c )
{
    for( int i = 0; i < (*s)->size; i++ )
    {
        if( (*s)->data[i] == c )
            return true;
    }
    return false;
}
bool handy_contain_str     ( handy_string * s, char * str )
{
    int len = sizeof(str) / sizeof(char);
    for( int i = 0; i < (*s)->size; i++ )
    {
        if( (*s)->data[i] == str[0] )
        {
            for( int j = 0; j < len; j++ )
            {
                if((*s)->data[i + j] != str[j] )
                    continue;
            }
            return true;
        }
    }
    return false;
}
bool handy_add_front       ( handy_string * s, char c )
{
    char * temp = malloc( (*s)->size + sizeof(char) );

    if( temp == NULL )
        return false;

    temp[0] = c;

    for( int i = 1; i < (*s)->size + 1; i++ )
        temp[i] = (*s)->data[i];

    return  strncpy( (*s)->data, temp, (*s)->size + 1 );
}
bool handy_add_back        ( handy_string * s, char c ){}
bool handy_add_at          ( handy_string * s, char c, int at ){}
bool handy_push            ( handy_string * s, char c ){}
bool handy_empty           ( handy_string * s ){}

char handy_get_front       ( handy_string * s ){}
char handy_get_back        ( handy_string * s ){}
char handy_get_at          ( handy_string * s, int at ){}
void * handy_delete_front  ( handy_string * s ){}
void * handy_delete_back   ( handy_string * s ){}
void handy_delete_at       ( handy_string * s, int at ){}
void handy_reverse         ( handy_string * s ){}
void handy_free            ( handy_string * s ){}
int  handy_length          ( handy_string * s ){}

handy_string (*concat)  ( handy_string * s1, handy_string * s2 );