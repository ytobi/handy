#include <ctype.h>
#include "handy_string.h"
#include "handy.h"

bool handy_append          ( handy_string * s, char * _data );
bool handy_equal           ( handy_string * s1, handy_string * s2 );
bool handy_equal_str       ( handy_string * s, char * str );

bool handy_copy            ( handy_string * des, handy_string * src );
int handy_contain_char     ( handy_string * s, char c );
int handy_contain_str      ( handy_string * s, char * str );
bool handy_add_char_front  ( handy_string * s, char c );
bool handy_add_char_back   ( handy_string * s, char c );
bool handy_add_char_at     ( handy_string * s, char c, int at );
bool handy_is_null         ( handy_string * s );

void handy_to_upper        ( handy_string * s );
void handy_to_lower        ( handy_string * s );

char * handy_get_string    ( handy_string * s );
char handy_get_front_char  ( handy_string * s );
char handy_get_back_char   ( handy_string * s );
char handy_get_char_at     ( handy_string * s, int at );
bool handy_delete_front_char( handy_string * s );
bool handy_delete_back_char( handy_string * s );
bool handy_delete_char_at  ( handy_string * s, int at );
bool handy_reverse         ( handy_string * s );
int handy_word_count       ( handy_string * s, char * delimiter );
void handy_free            ( handy_string * s );
int  handy_length          ( handy_string * s );

handy_string handy_create_string( )
{
    handy_string temp = malloc( sizeof(*temp) );

    temp->_data = malloc( sizeof(char) );
    temp->_size = 0;
    temp->_data = NULL;

    temp->append        = handy_append;
    temp->equal         = handy_equal;
    temp->equal_str     = handy_equal_str;
    temp->contain_char  = handy_contain_char;
    temp->contain_str   = handy_contain_str;
    temp->add_char_front= handy_add_char_front;
    temp->add_char_back = handy_add_char_back;
    temp->add_char_at   = handy_add_char_at;
    temp->is_null       = handy_is_null;
    temp->to_upper      = handy_to_upper;
    temp->to_lower      = handy_to_lower;
    temp->copy          = handy_copy;
    temp->string        = handy_get_string;
    temp->get_front_char= handy_get_front_char;
    temp->get_back_char = handy_get_back_char;
    temp->get_char_at   = handy_get_char_at;
    temp->delete_front_char= handy_delete_front_char;
    temp->delete_back_char= handy_delete_back_char;
    temp->delete_char_at= handy_delete_char_at;
    temp->reverse       = handy_reverse;
    temp->word_count    = handy_word_count;
    temp->free          = handy_free;
    temp->length        = handy_length;

    return temp;
}

bool handy_append           ( handy_string * s, char * str )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);
    size_t str_len  = strlen( str );

    char * new = (char *)realloc( ((*s)->_data), (str_len + (*s)->_size) * sizeof( char ) );

    if( new )
    {
        (*s)->_data = new;
        for( int i = 0; i < str_len; i++ )
        {
            (*s)->_data[(*s)->_size + i] = str[i];
        }
        (*s)->_size += str_len;
    }
}
bool handy_copy             ( handy_string * des, handy_string * src )
{
    // for protection sake
    (*des)->_size = (*des)->length(des);
    (*src)->_size = (*src)->length(src);

    char * new = (char *)realloc( ((*des)->_data), ((*src)->_size + (*des)->_size) * sizeof( char ) );

    if( new )
    {
        (*des)->_data = new;
        for( int i = 0; i < (*src)->_size; i++ )
        {
            (*des)->_data[(*des)->_size + i] = (*src)->_data[i];
        }
        (*des)->_size += (*src)->_size;

        return true;
    }
    return false;
}
bool handy_equal            ( handy_string * s1, handy_string * s2 )
{
    if( (*s1)->length(s1) == (*s2)->length(s2) )
        return  strncmp( (*s1)->_data, ((*s2)->_data), (*s2)->length(s2) ) == 0;
    return false;
}
bool handy_equal_str        ( handy_string * s1, char * s2 )
{
    if( (*s1)->length(s1) == strlen(s2))
        return  strncmp( (*s1)->_data, s2, strlen(s2) ) == 0;
    return false;
    // return  strncmp( (*s1)->_data, s2, strlen( s2) ) == 0;
}
int handy_contain_char     ( handy_string * s, char c )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    for( int i = 0; i < (*s)->_size; i++ )
    {
        if( (*s)->_data[i] == c )
            return i;
    }
    return -1;
}
int handy_contain_str      ( handy_string * s, char * str )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    size_t str_len = strlen( str );
    for( int i = 0; i < (*s)->_size; i++ )
    {
        // found the first char, try finding the rest of the string
        if( (*s)->_data[i] == str[0] )
        {
            for( int j = 0; j < str_len; j++ )
            {
                if((*s)->_data[i + j] == str[j] )
                {
                    // upto last char matches, return true
                    if( j == (str_len - 1) )
                        return i;
                }
                else
                {
                    // skip and continue searching
                    continue;
                }
            }
        }
    }
    return -1;
}
bool handy_add_char_front   ( handy_string * s, char c )
{
    return (*s)->add_char_at( s, c, 0);
}
bool handy_add_char_back    ( handy_string * s, char c )
{
    return (*s)->add_char_at( s, c, (*s)->length(s) );
}
bool handy_add_char_at      ( handy_string * s, char c, int at )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    // add a single char to front of str
    char * new = (char *)realloc( ((*s)->_data), (1 + (*s)->_size) );

    if( new )
    {
        (*s)->_data = new;
        for( int i = (*s)->_size + 1; i >= 0; i-- )
        {
            // if at position add
            if( i == at )
            {
                (*s)->_data[i] = c;
                return true;
            }
            // continue shitting backwards
            (*s)->_data[i] = (*s)->_data[i - 1];
        }
        (*s)->_size++;
    }
    return false;
}
char * handy_get_string     ( handy_string * s )
{
    return (*s)->_data;
}
char handy_get_front_char   ( handy_string * s )
{
    return (*s)->_data[0];
}
char handy_get_back_char    ( handy_string * s )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    return (*s)->_data[(*s)->_size ];
}
char handy_get_char_at      ( handy_string * s, int at )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    if( at > (*s)->_size )
        return '\0';
    return (*s)->_data[at];
}
bool handy_delete_front_char( handy_string * s )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    // add a single char to front of str
    for( int i = 0; i < (*s)->_size; i++ )
    {
        (*s)->_data[i] = (*s)->_data[i + 1];
    }
    char * new = (char *)realloc( ((*s)->_data), (((*s)->_size) - 1) * sizeof( char ) );

    if( new )
    {
        (*s)->_data = new;
        (*s)->_size--;
        return true;
    }
    return false;
}
bool handy_delete_back_char ( handy_string * s )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    char * new = (char *)realloc( ((*s)->_data), (((*s)->_size) - 1) * sizeof( char ) );

    if( new )
    {
        (*s)->_data = new;
        (*s)->_size--;
        return true;
    }
    return false;
}
bool handy_delete_char_at   ( handy_string * s, int at )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    if( at < 0 || at > (*s)->_size )
        return false;
    else
    {
        for( int i = at; i < (*s)->_size; i++ )
        {
            (*s)->_data[i] = (*s)->_data[i + 1];
        }
    }
    return true;
}
bool handy_reverse          ( handy_string * s )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    char temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < ((*s)->_size / 2); i++ )
    {
        temp_data = (*s)->_data[i];
        (*s)->_data[i] = (*s)->_data[(*s)->_size - i];
        (*s)->_data[(*s)->_size - i] = temp_data;
    }
}
int handy_word_count        ( handy_string * s, char * delimiter )
{
    // count the number of words in between a delimiter
    int word_count = 0;
    int found_word = 0;

    for( int i = 0; i < (*s)->_size; i++ )
    {
        found_word = 0;
        // found first char match in delimiter
        if( (*s)->_data[i] == delimiter[0] )
        {
            for( int j = 0; j < strlen( delimiter ); j++ )
            {
                if( (*s)->_data[i + j] == delimiter[j] )
                {
                    found_word++;
                }
                else
                {
                    break;
                }
            }
            // if were already passed some words(i > 0) and found
            // delimiter, then count the word
            // we do not account for delimiter ending a word
            if( i > 0 && i < (*s)->_size && found_word == strlen( delimiter ) )
            {
                word_count++;
            }
        }
    }

    return word_count + 1;
}
void handy_free             ( handy_string * s )
{
    free( (*s)->_data );
}
int  handy_length           ( handy_string * s )
{
    return (*s)->_data == NULL? 0: strlen( ((*s)->_data) );
}
bool  handy_is_null         ( handy_string * s )
{
    // for protection sake
    (*s)->_size = (*s)->length(s);

    return (*s)->_size == 0? true: false;
}
void handy_to_upper         ( handy_string *s )
{
    for( int i = 0; i < (*s)->_size; i++ )
    {
        (*s)->_data[i] = (char)toupper((*s)->_data[i]);
    }
}
void handy_to_lower         ( handy_string *s )
{
    for( int i = 0; i < (*s)->_size; i++ )
    {
        (*s)->_data[i] = (char)tolower((*s)->_data[i]);
    }
}
