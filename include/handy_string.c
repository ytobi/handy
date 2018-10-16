#include "handy_string.h"
#include "handy.h"

bool handy_append          ( handy_string * s, char * data );
bool handy_equal           ( handy_string * s1, handy_string * s2 );
bool handy_equal_str       ( handy_string * s, char * str );

bool handy_copy            ( handy_string * des, handy_string * src );
bool handy_contain_char    ( handy_string * s, char c );
bool handy_contain_str     ( handy_string * s, char * str );
bool handy_add_char_front  ( handy_string * s, char c );
bool handy_add_char_back   ( handy_string * s, char c );
bool handy_add_char_at     ( handy_string * s, char c, int at );
bool handy_is_null         ( handy_string * s );

char * handy_get_string    ( handy_string * s );
char handy_get_front_char  ( handy_string * s );
char handy_get_back_char   ( handy_string * s );
char handy_get_char_at     ( handy_string * s, int at );
bool handy_delete_front_char( handy_string * s );
bool handy_delete_back_char( handy_string * s );
bool handy_delete_char_at  ( handy_string * s, int at );
bool handy_reverse         ( handy_string * s );
void handy_free            ( handy_string * s );
int  handy_length          ( handy_string * s );

handy_string handy_create_string( )
{
    handy_string temp = malloc( sizeof(*temp) );

    temp->data = malloc( sizeof(char) );
    temp->size = 0;
    temp->data = NULL;

    temp->append        = handy_append;
    temp->equal         = handy_equal;
    temp->equal_str     = handy_equal_str;
    temp->contain_char  = handy_contain_char;
    temp->contain_str   = handy_contain_str;
    temp->add_char_front= handy_add_char_front;
    temp->add_char_back = handy_add_char_back;
    temp->add_char_at   = handy_add_char_at;
    temp->is_null       = handy_is_null;
    temp->copy          = handy_copy;
    temp->string        = handy_get_string;
    temp->get_front_char= handy_get_front_char;
    temp->get_back_char = handy_get_back_char;
    temp->get_char_at   = handy_get_char_at;
    temp->delete_front_char= handy_delete_front_char;
    temp->delete_back_char= handy_delete_back_char;
    temp->delete_char_at= handy_delete_char_at;
    temp->reverse       = handy_reverse;
    temp->free          = handy_free;
    temp->length        = handy_length;

    return temp;
}

bool handy_append       ( handy_string * s, char * str )
{
    // for protection sake
    (*s)->size = (*s)->length(s);
    size_t str_len  = strlen( str );

    char * new = (char *)realloc( ((*s)->data), (str_len + (*s)->size) * sizeof( char ) );

    if( new )
    {
        (*s)->data = new;
        for( int i = 0; i < str_len; i++ )
        {
            (*s)->data[(*s)->size + i] = str[i];
        }
        (*s)->size += str_len;
    }
}
bool handy_copy             ( handy_string * des, handy_string * src )
{
    // for protection sake
    (*des)->size = (*des)->length(des);
    (*src)->size = (*src)->length(src);

    char * new = (char *)realloc( ((*des)->data), ((*src)->size + (*des)->size) * sizeof( char ) );

    if( new )
    {
        (*des)->data = new;
        for( int i = 0; i < (*src)->size; i++ )
        {
            (*des)->data[(*des)->size + i] = (*src)->data[i];
        }
        (*des)->size += (*src)->size;

        return true;
    }
    return false;
}
bool handy_equal            ( handy_string * s1, handy_string * s2 )
{
    // for protection sake
    (*s2)->size = (*s2)->length(s2);

    return  strncmp( (*s1)->data, ((*s2)->data), (*s2)->size ) == 0;
}
bool handy_equal_str        ( handy_string * s1, char * s2 )
{
    return  strncmp( (*s1)->data, s2, strlen( s2) ) == 0;
}
bool handy_contain_char     ( handy_string * s, char c )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    for( int i = 0; i < (*s)->size; i++ )
    {
        if( (*s)->data[i] == c )
            return true;
    }
    return false;
}
bool handy_contain_str      ( handy_string * s, char * str )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    size_t str_len = strlen( str );
    for( int i = 0; i < (*s)->size; i++ )
    {
        // found the first char, try finding the rest of the string
        if( (*s)->data[i] == str[0] )
        {
            for( int j = 0; j < str_len; j++ )
            {
                if((*s)->data[i + j] == str[j] )
                {
                    // upto last char matches, return true
                    if( j == (str_len - 1) )
                        return true;
                }
                else
                {
                    // skip and continue searching
                    continue;
                }
            }
        }
    }
    return false;
}
bool handy_add_char_front   ( handy_string * s, char c )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    // add a single char to front of str
    char * new = (char *)realloc( ((*s)->data), (1 + (*s)->size) * sizeof( char ) );

    if( new )
    {
        (*s)->data = new;
        for( int i = (*s)->size + 1; i > 0; i-- )
        {
            (*s)->data[i] = (*s)->data[i - 1];
        }
        (*s)->data[0] = c;
        (*s)->size++;
        return true;
    }
    return false;
}
bool handy_add_char_back    ( handy_string * s, char c )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    // add a single char to back of str
    char * new = (char *)realloc( ((*s)->data), (1 + (*s)->size) * sizeof( char ) );

    if( new )
    {
        (*s)->data = new;
        (*s)->data[(*s)->size + 1] = c;
        (*s)->size++;

        return true;
    }
    return false;
}
bool handy_add_char_at      ( handy_string * s, char c, int at )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    // add a single char to front of str
    char * new = (char *)realloc( ((*s)->data), (1 + (*s)->size) * sizeof( char ) );

    if( new )
    {
        (*s)->data = new;
        for( int i = (*s)->size + 1; i > 0; i-- )
        {
            // if at position add
            if( i == at )
            {
                (*s)->data[i] = c;
                return true;
            }
            // continue shitting backwards
            (*s)->data[i] = (*s)->data[i - 1];
        }
        (*s)->size++;
    }
    return false;
}
char * handy_get_string     ( handy_string * s )
{
    return (*s)->data;
}
char handy_get_front_char   ( handy_string * s )
{
    return (*s)->data[0];
}
char handy_get_back_char    ( handy_string * s )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    return (*s)->data[(*s)->size ];
}
char handy_get_char_at      ( handy_string * s, int at )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    if( at > (*s)->size )
        return '\0';
    return (*s)->data[at];
}
bool handy_delete_front_char( handy_string * s )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    // add a single char to front of str
    for( int i = 0; i < (*s)->size; i++ )
    {
        (*s)->data[i] = (*s)->data[i + 1];
    }
    char * new = (char *)realloc( ((*s)->data), (((*s)->size) - 1) * sizeof( char ) );

    if( new )
    {
        (*s)->data = new;
        (*s)->size--;
        return true;
    }
    return false;
}
bool handy_delete_back_char ( handy_string * s )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    char * new = (char *)realloc( ((*s)->data), (((*s)->size) - 1) * sizeof( char ) );

    if( new )
    {
        (*s)->data = new;
        (*s)->size--;
        return true;
    }
    return false;
}
bool handy_delete_char_at   ( handy_string * s, int at )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    if( at < 0 || at > (*s)->size )
        return false;
    else
    {
        for( int i = at; i < (*s)->size; i++ )
        {
            (*s)->data[i] = (*s)->data[i + 1];
        }
    }
    return true;
}
bool handy_reverse          ( handy_string * s )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    char temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < ((*s)->size / 2); i++ )
    {
        temp_data = (*s)->data[i];
        (*s)->data[i] = (*s)->data[(*s)->size - i];
        (*s)->data[(*s)->size - i] = temp_data;
    }
}
void handy_free             ( handy_string * s )
{
    free( (*s)->data );
}
int  handy_length           ( handy_string * s )
{

    return (*s)->data == NULL? 0: strlen( ((*s)->data) );
}
bool  handy_is_null         ( handy_string * s )
{
    // for protection sake
    (*s)->size = (*s)->length(s);

    return (*s)->size == 0? true: false;
}

