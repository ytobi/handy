
#include "handy_hashtbl.h"


bool   handy_hashtbl_contain  ( handy_hashtbl * l, void * key );
bool   handy_hashtbl_add      ( handy_hashtbl * l, void * key, void * item );
void * handy_hashtbl_get      ( handy_hashtbl * l, void * key );
void * handy_hashtbl_remove   ( handy_hashtbl * l, void * key );
void   handy_hashtbl_free     ( handy_hashtbl * l );


unsigned long handy_hash_function( char * key )
{
    unsigned long hashValue = 0;

    int shift = 0;

    int index = 0;

    while( key[index] != '\0' )
    {
        if( shift == 32 )
            shift = 0;
        hashValue += key[index++] << shift;
        shift += 8;
    }

    return hashValue;
}

unsigned long handy_hash_djb2( char * str )
{
    unsigned long hash = 5381;
    int c;

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
    temp_tbl->size = 1024;

    temp_tbl->contain       = handy_hashtbl_contain;
    temp_tbl->add           = handy_hashtbl_add;
    temp_tbl->get           = handy_hashtbl_get;
    temp_tbl->remove        = handy_hashtbl_remove;
    temp_tbl->free          = handy_hashtbl_free;

    temp_tbl->bucket = malloc( sizeof(*(temp_tbl->bucket)) * temp_tbl->size );

    return temp_tbl;
}
bool handy_hashtbl_contain    ( handy_hashtbl * t, void * key )
{
    unsigned long hash_key = handy_hash_djb2( key );

    hashtbl_obj current_item;

    // iterate through all item in linked list at position  of hashed key
    // compare keys and return true if found, return false if not found

    for( int i = 0; i < (*t)->bucket[hash_key]->size; i++ )
    {
        current_item = (*t)->bucket[hash_key]->get_at( &((*t)->bucket[hash_key]), i );

        if( memcmp( &(current_item->key), &hash_key, sizeof(key) ) == 0 )
        {
            return true;
        }
    }

    return false;
}
bool handy_hashtbl_add        ( handy_hashtbl * t, void * key, void * value )
{

    // Create item to add to table, assign value and key
    // add value to linked list at key position
    // in certian cases were the is colission add value to back of linked list
    unsigned long hash_key = handy_hash_djb2( key ) % (*t)->size;

    hashtbl_obj add_item = malloc( sizeof(*add_item) );

    add_item->value = value;
    add_item->key = hash_key;

    if( (*t)->bucket[hash_key] == NULL )
    {
        (*t)->bucket[hash_key] = handy_create_list();

        (*t)->bucket[hash_key]->add_back( &((*t)->bucket[hash_key]), add_item );
        return true;
    }
    else
    {
        // contain return index of item if found and return -1 if not found
        // added identical item
        if( (*t)->bucket[hash_key]->contain( &((*t)->bucket[hash_key]), add_item ) == -1 ) // TODO
        {
            (*t)->bucket[hash_key]->add_back( &((*t)->bucket[hash_key]), add_item );
            return true;
        }
    }

    return false;
}
void * handy_hashtbl_get      ( handy_hashtbl * t, void * key )
{
    unsigned long hash_key = handy_hash_djb2(key) % (*t)->size;

    hashtbl_obj temp_obj;

    for( int i = 0; i < (*t)->bucket[hash_key]->size; i++ )
    {
        temp_obj = (*t)->bucket[hash_key]->get_at( &((*t)->bucket[hash_key]), i );

        if( memcmp( &(temp_obj->key), &hash_key, sizeof(key) ) == 0 )
        {
            return ((hashtbl_obj)(*t)->bucket[hash_key]->get_at( &((*t)->bucket[hash_key]), i ))->value;
        }
    }
    return NULL;
}
void * handy_hashtbl_remove   ( handy_hashtbl * t, void * key )
{
    unsigned long hash_key = handy_hash_djb2(key) % (*t)->size;

    void * temp_item_return = malloc( sizeof(void*) );

    hashtbl_obj temp_obj;

    for( int i = 0; i < (*t)->bucket[hash_key]->size; i++ )
    {
        temp_obj = (*t)->bucket[hash_key]->get_at( &((*t)->bucket[hash_key]), i );

        if( memcmp( &(temp_obj->key), &hash_key, sizeof(key) ) == 0 )
        {
            memcpy( temp_item_return, ((hashtbl_obj)(*t)->bucket[hash_key]->get_at( &((*t)->bucket[hash_key]), i ))->value,
                    sizeof(temp_item_return) );

            (*t)->bucket[hash_key]->remove_at( &((*t)->bucket[hash_key]), i );

            return temp_item_return;
        }
    }

    return NULL;
}
void   handy_hashtbl_free     ( handy_hashtbl * t )
{
    for( int i = 0; i < (*t)->size; i++ )
    {
        if( (*t)->bucket[i] != NULL )
            free((*t)->bucket[i]);
    }
    free( (*t)->bucket );
}