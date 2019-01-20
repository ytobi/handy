#include <ctype.h>
#include "handy_string.h"
#include "handy.h"

bool handy_append          ( handy_string self, char * _data );
bool handy_equal           ( handy_string s1, handy_string s2 );
bool handy_equal_str       ( handy_string self, char * str );

bool handy_copy            ( handy_string des, handy_string src );
int handy_contain_char     ( handy_string self, char c );
int handy_contain_str      ( handy_string self, char * str );
bool handy_add_char_front  ( handy_string self, char c );
bool handy_add_char_back   ( handy_string self, char c );
bool handy_add_char_at     ( handy_string self, char c, int at );
bool handy_is_null         ( handy_string self );

void handy_to_upper        ( handy_string self );
void handy_to_lower        ( handy_string self );

char * handy_get_string    ( handy_string self );
char handy_get_front_char  ( handy_string self );
char handy_get_back_char   ( handy_string self );
char handy_get_char_at     ( handy_string self, int at );
bool handy_del_front_char  ( handy_string self );
bool handy_del_back_char   ( handy_string self );
bool handy_del_char_at     ( handy_string self, int at );
void handy_reverse         ( handy_string self );
int handy_word_count       ( handy_string self, char * delimiter );
void handy_string_free     ( handy_string self );
int  handy_string_length   ( handy_string self );

handy_string handy_create_string( )
{
    handy_string temp = malloc( sizeof(*temp) );

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
    temp->del_front_char= handy_del_front_char;
    temp->del_back_char = handy_del_back_char;
    temp->del_char_at   = handy_del_char_at;
    temp->reverse       = handy_reverse;
    temp->word_count    = handy_word_count;
    temp->free          = handy_string_free;
    temp->length        = handy_string_length;

    return temp;
}

char * _handy_string_dict_value[2][10] = {
        { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" },
        { "0-", "1-", "2-", "-3", "4-", "5-", "6-", "7-", "8-", "9-" } };

void handy_append_int       ( handy_string self, long long num )
{
    long long back = 0;
    while( num != 0 )
    {
        back = num % 10;

        if( back < 0 )
            self->append(self, _handy_string_dict_value[1][back*-1] );
        else
            self->append(self, _handy_string_dict_value[0][back] );

        num /= 10;
    }
    self->reverse(self);
}
void handy_append_double    ( handy_string self, double num )
{

}
bool handy_append           ( handy_string self, char * str )
{
    // for protection sake
    // 1 + size to account for null terminated string
    self->_size = self->length(self) + 1;
    size_t str_len  = strlen( str );

    char * new = (char *)realloc( (self->_data), (str_len + self->_size) * sizeof( char ) );

    if( new )
    {
        self->_data = new;
        for( int i = 0; i < str_len; i++ )
        {
            self->_data[(self->_size - 1) + i] = str[i];
        }
        self->_size += str_len;
        self->_data[self->_size - 1] = NULL;
        return true;
    }
    return false;
}
bool handy_copy             ( handy_string des, handy_string src )
{
    // for protection sake
    // 1 + size to account for null terminated string
    des->_size = des->length(des) + 1;
    src->_size = src->length(src);

    char * new = (char *)realloc( (des->_data), (src->_size + des->_size) * sizeof( char ) );

    if( new )
    {
        des->_data = new;
        for( int i = 0; i < src->_size; i++ )
        {
            des->_data[des->_size + i] = src->_data[i];
        }
        des->_size += src->_size;
        des->_data[des->_size - 1] = NULL;
        return true;
    }
    return false;
}
bool handy_equal            ( handy_string s1, handy_string s2 )
{
    if( s1->length(s1) == s2->length(s2) )
        return  strncmp( s1->_data, (s2->_data), s2->length(s2) ) == 0;
    return false;
}
bool handy_equal_str        ( handy_string s1, char * s2 )
{
    if( s1->length(s1) == strlen(s2))
        return  strncmp( s1->_data, s2, strlen(s2) ) == 0;
    return false;
    // return  strncmp( (*s1)->_data, s2, strlen( s2) ) == 0;
}
int handy_contain_char      ( handy_string self, char c )
{
    // for protection sake
    self->_size = self->length(self);

    for( int i = 0; i < self->_size; i++ )
    {
        if( self->_data[i] == c )
            return i;
    }
    return -1;
}
int handy_contain_str       ( handy_string self, char * str )
{
    // for protection sake
    self->_size = self->length(self);

    size_t str_len = strlen( str );
    for( int i = 0; i < self->_size; i++ )
    {
        // found the first char, try finding the rest of the string
        if( self->_data[i] == str[0] )
        {
            for( int j = 0; j < str_len; j++ )
            {
                if(self->_data[i + j] == str[j] )
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
bool handy_add_char_front   ( handy_string self, char c )
{
    return self->add_char_at( self, c, 0);
}
bool handy_add_char_back    ( handy_string self, char c )
{
    return self->add_char_at( self, c, self->length(self) );
}
bool handy_add_char_at      ( handy_string self, char c, int at )
{
    // for protection sake
    // 1 + size to account for null terminated string
    self->_size = self->length(self) + 1;

    // add a single char to front of str + 1 for char to add
    char * new = (char *)realloc( (self->_data), (self->_size + 1) * sizeof(char) );

    if( new )
    {
        self->_data = new;
        for( int i = (self->_size -1); i >= 0; i-- )
        {
            // if at position add
            if( i == at )
            {
                self->_data[i] = c;
                self->_size++;
                self->_data[self->_size - 1] = NULL;
                return true;
            }
            // continue shitting backwards
            else if( i > 0 )
                self->_data[i] = self->_data[i - 1];
        }
    }
    return false;
}
char * handy_get_string     ( handy_string self )
{
    return self->_data;
}
char handy_get_front_char   ( handy_string self )
{
    return self->_data[0];
}
char handy_get_back_char    ( handy_string self )
{
    // for protection sake
    self->_size = self->length(self);

    return self->_data[self->_size - 1 ];
}
char handy_get_char_at      ( handy_string self, int at )
{
    // for protection sake
    self->_size = self->length(self);

    if( at > self->_size )
        return '\0';
    return self->_data[at];
}
bool handy_del_front_char   ( handy_string self )
{
    // for protection sake
    // account for null terminating char, this is already in length,
    // since we iterating from zero
    self->_size = self->length(self);

    // shift all char to fill front
    for( int i = 0; i < self->_size; i++ )
    {
        self->_data[i] = self->_data[i + 1];
    }
    // This seems to always chop off the last byte for a memory location
    // I don't know if there is any chance of front byte instead
    char * new = (char *)realloc( (self->_data), ((self->_size)) * sizeof( char ) );

    if( new )
    {
        self->_data = new;
        self->_size--;
        return true;
    }
    return false;
}
bool handy_del_back_char    ( handy_string self )
{
    // for protection sake
    // account for null termiting char
    self->_size = self->length(self) + 1;

    char * new = (char *)realloc( (self->_data), (self->_size - 1) * sizeof( char ) );

    if( new )
    {
        self->_data = new;
        self->_size--;
        self->_data[self->_size - 1] = NULL;
        return true;
    }
    return false;
}
bool handy_del_char_at      ( handy_string self, int at )
{
    // for protection sake
    // shift null terminating char
    self->_size = self->length(self) + 1;

    // if position is not within range, not able to delete char
    if( at < 0 || at > self->_size )
        return false;
    else
    {
        // if found position to delete, shift all char from right to left
        // and fill position with left most char form position.
        for( int i = at; i < (self->_size - 1); i++ )
        {
            self->_data[i] = self->_data[i + 1];
        }
        // fill last location which is not empty to null
        self->_data[self->_size - 1] = NULL;

        char * new = (char *)realloc( (self->_data), ((self->_size) - 1) * sizeof( char ) );

        if( new )
        {
            self->_data = new;
        }
    }
    return true;
}
void handy_reverse          ( handy_string self )
{
    // for protection sake
    self->_size = self->length(self);

    char temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < (self->_size / 2); i++ )
    {
        temp_data = self->_data[i];
        self->_data[i] = self->_data[(self->_size - 1) - i];
        self->_data[(self->_size - 1) - i] = temp_data;
    }
}
int handy_word_count        ( handy_string self, char * delimiter )
{
    // whenever we found a new letter that is not part(start) of
    // delimiter, count as new word

    bool found_letter = false;
    int count = 0;

    for( int i = 0; i < self->_size; i++ )
    {
        if( !found_letter && self->_data[i] != delimiter[0] && self->_data[i] != NULL )
        {
            found_letter = true;
            count++;
        }
        else if( self->_data[i] == delimiter[0] )
        {
            // match all letters in delimiter to afirme delimiters existence
            for (int j = 0; j < strlen(delimiter); j++)
            {
                if (  self->_data[i + j] == delimiter[j] )
                {
                    // successfully read delimiter, we are ready to find new word
                    found_letter = false;
                } else
                {
                    // No! false alarm, we have not found delimiter
                    // we are still on new word
                    found_letter = true;
                    break;
                }
            }
        }
    }
    return count;
}
void handy_string_free      ( handy_string self )
{
    // after freeing, string is maybe not null, but size should reflect that fact
    self->_data = ( free( self->_data ), NULL );
    self->_size = 0;
}
int  handy_string_length    ( handy_string self )
{
    return self->_data == NULL? 0: strlen( (self->_data) );
}
bool  handy_is_null         ( handy_string self )
{
    // for protection sake
    self->_size = self->length(self);

    return self->_size == 0? true: false;
}
void handy_to_upper         ( handy_string self )
{
    for( int i = 0; i < self->_size; i++ )
    {
        self->_data[i] = (char)toupper(self->_data[i]);
    }
}
void handy_to_lower         ( handy_string self )
{
    for( int i = 0; i < self->_size; i++ )
    {
        self->_data[i] = (char)tolower(self->_data[i]);
    }
}
