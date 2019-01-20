#include "handy_hashtbl.h"

bool   handy_hashtbl_contain  ( handy_hashtbl self, char * _key );
bool   handy_hashtbl_add      ( handy_hashtbl self, char * _key, void * item );
void * handy_hashtbl_get      ( handy_hashtbl self, char * _key );
void   handy_hashtbl_remove   ( handy_hashtbl self, char * _key );
void   handy_hashtbl_free     ( handy_hashtbl self );


unsigned long handy_hash_function( char * _key )
{
    unsigned long hashValue = 0;

    int shift = 0;

    int index = 0;

    while( _key[index] != '\0' )
    {
        if( shift == 32 )
            shift = 0;
        hashValue += _key[index++] << shift;
        shift += 8;
    }

    return hashValue;
}
unsigned long handy_hash_djb2( char * str )
{
    unsigned long hash = 5381;
    int c;

    // will return false if read end of string
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;

}

handy_hashtbl handy_create_hashtbl()
{
    handy_hashtbl  temp_tbl = malloc( sizeof(*temp_tbl) );

    // initial size of hash table is 1024
    // This size could be change to anything close to the
    // the expected size of the table
    temp_tbl->_size = 1024;

    temp_tbl->contain       = handy_hashtbl_contain;
    temp_tbl->add           = handy_hashtbl_add;
    temp_tbl->get           = handy_hashtbl_get;
    temp_tbl->remove        = handy_hashtbl_remove;
    temp_tbl->free          = handy_hashtbl_free;

    temp_tbl->_bucket = malloc( sizeof(*(temp_tbl->_bucket)) * temp_tbl->_size );

    for( int i = 0; i < temp_tbl->_size; i++ )
        temp_tbl->_bucket[i] = NULL;

    return temp_tbl;
}

bool handy_hashtbl_contain    ( handy_hashtbl self, char * _key )
{
    // iterate through all item in linked list at position  of hashed _key
    // compare keys and return true if found, return false if not found
    
    if( strlen(_key) <= 0 )
        return false;

    unsigned long hash_key = handy_hash_djb2( _key ) % self->_size;

    _handy_hashtbl_obj current_item;

    for( int i = 0; self->_bucket[hash_key] != NULL && i < self->_bucket[hash_key]->length( self->_bucket[hash_key]); i++ )
    {
        current_item = self->_bucket[hash_key]->get_at( self->_bucket[hash_key], i );

        if( memcmp( &(current_item->_key), &hash_key, sizeof(_key) ) == 0 )
        {
            return true;
        }
    }

    return false;
}
bool handy_hashtbl_add        ( handy_hashtbl self, char * _key, void * _value )
{

    // Create item to add to table, assign _value and _key
    // add _value to linked list at _key position
    // in certian cases were the is colission add _value to back of linked list
    unsigned long hash_key = handy_hash_djb2( _key ) % self->_size;

    _handy_hashtbl_obj add_item = malloc( sizeof(*add_item) );

    add_item->_value = _value;
    add_item->_key = hash_key;

    if( self->_bucket[hash_key] == NULL )
    {
        self->_bucket[hash_key] = handy_create_list();

        return self->_bucket[hash_key]->add_back( self->_bucket[hash_key], add_item );
    }
    else
    {
        // contain return index of item if found and return -1 if not found
        // added identical item

        if( self->_bucket[hash_key]->contain( self->_bucket[hash_key], add_item ) == -1 )
        {
            return self->_bucket[hash_key]->add_back( self->_bucket[hash_key], add_item );
        }

        add_item = ( free(add_item), NULL );
    }

    return false;
}
void * handy_hashtbl_get      ( handy_hashtbl self, char * _key )
{
    if( self->_bucket == NULL )
        return NULL;

    unsigned long hash_key = handy_hash_djb2(_key) % self->_size;

    _handy_hashtbl_obj temp_obj;

    if( self->_bucket[hash_key] != NULL )
    {
        for( int i = 0; i < self->_bucket[hash_key]->length( self->_bucket[hash_key]); i++ )
        {
            temp_obj = self->_bucket[hash_key]->get_at( self->_bucket[hash_key], i );

            if( memcmp( &(temp_obj->_key), &hash_key, sizeof(_key) ) == 0 )
            {
                return ( (_handy_hashtbl_obj)self->_bucket[hash_key]->get_at( self->_bucket[hash_key], i ) )->_value;
            }
        }
    }

    return NULL;
}
void   handy_hashtbl_remove   ( handy_hashtbl self, char * _key )
{
    unsigned long hash_key = handy_hash_djb2(_key) % self->_size;

    _handy_hashtbl_obj temp_obj;

    for( int i = 0; i < self->_bucket[hash_key]->length( self->_bucket[hash_key]); i++ )
    {
        temp_obj = self->_bucket[hash_key]->get_at( (self->_bucket[hash_key]), i );

        if( memcmp( &(temp_obj->_key), &hash_key, sizeof(_key) ) == 0 )
        {
            self->_bucket[hash_key]->rem_at( self->_bucket[hash_key], i );
        }
    }

    return;
}
void   handy_hashtbl_free     ( handy_hashtbl self )
{
    for( int i = 0; i < self->_size ; i++ )
    {
        if( self->_bucket[i] != NULL )
        {
            self->_bucket[i]->free( self->_bucket[i] );
        }
        self->_bucket[i] = ( free(self->_bucket[i]), NULL );
    }
    self->_bucket = (free( self->_bucket ), NULL);
}
