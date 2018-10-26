#include <string.h>
#include "handy_vector.h"

void * handy_get_at ( handy_vector * v, int at );
bool handy_set_at   ( handy_vector * v, void * item, int at );
int handy_contain   ( handy_vector * v, void * item );
bool handy_rem_at   ( handy_vector * v, int at );
int handy_capacity  ( handy_vector * v );
void handy_free     ( handy_vector * v );

handy_vector handy_create_vector()
{
    handy_vector temp_vector = malloc(sizeof(*temp_vector) );

    temp_vector->_capacity = 1024;
    temp_vector->_size = 0;
    temp_vector->_bucket = malloc( sizeof(*temp_vector->_bucket) * temp_vector->_size );

    temp_vector->get_at = handy_get_at;
    temp_vector->set_at = handy_set_at;
    temp_vector->contain= handy_contain;
    temp_vector->rem_at = handy_rem_at;
    temp_vector->capacity= handy_capacity;
    temp_vector->free   = handy_free;

    for( int i = 0; i < temp_vector->_capacity; i++ )
        temp_vector->_bucket[i] = NULL;

    return temp_vector;
}

void * handy_get_at ( handy_vector * v, int at )
{
    if( at < 0 || at > (*v)->_capacity )
        return NULL;
    return (*v)->_bucket[at];
}
bool handy_set_at   ( handy_vector * v, void * item, int at )
{
    // if at is less than 0, then we can't add item, must specify a
    // location greater than 0
    if( at < 0 )
        return false;

    else if( at >= (*v)->_capacity )
    {
        // if we have used all our capacity and at is such that we can expand to + 1/4 of original
        // capacity, then expand. +4 is because of integer division
        if( (*v)->_size >= (*v)->_capacity && at < ((*v)->_capacity + (((*v)->_capacity + 4) / 4)) )
        {
            void ** new = realloc( ((*v)->_bucket), (((*v)->_capacity + (((*v)->_capacity + 4) / 4)) * sizeof(*new)) );

            if( new )
            {
                (*v)->_bucket = new;
                // don't know if realloc initialise the newly allocated memory,
                // we do in case not.
                for( int c = (*v)->_capacity; c < ((*v)->_capacity + (((*v)->_capacity + 4) / 4)); c++ )
                {
                    (*v)->_bucket[c] = NULL;
                }
                (*v)->_capacity = ((*v)->_capacity + (((*v)->_capacity + 4) / 4));
                (*v)->_bucket[at] = item;
                (*v)->_size++;
                return true;
            }
        }
        else
        {
            // at is more than our capacity, hence increase size up to at, then insert
            // count from zero, hence add +1
            void ** new = realloc( ((*v)->_bucket), ((at + 1) * sizeof(*new)) );

            if( new )
            {
                (*v)->_bucket = new;
                // don't know if realloc initialise the newly allocated memory,
                // we do it increase not.
                for( int c = (*v)->_capacity; c < at; c++ )
                {
                    (*v)->_bucket[c] = NULL;
                }
                (*v)->_capacity = at;
                (*v)->_bucket[at] = item;
                (*v)->_size++;
                return true;
            }
        }

    }
    else
    {
        // if location(at) is empty, just insert at location
        if( (*v)->_bucket[at] == NULL )
        {
            (*v)->_bucket[at] = item;
            (*v)->_size++;
            return true;
        }
        else
        {
            // if location is not empty, but contain another item, then, resize vector and
            // shift all item at location one place to the right.
            // resize vector to capacity + 1
            void ** new = realloc( ((*v)->_bucket), ((*v)->_capacity + 1) * sizeof(*new) );
            if( new )
            {
                (*v)->_bucket = new;

                // initialise allocated space to null
                (*v)->_bucket[(*v)->_capacity] = NULL;

                // shift all items one-place to the right
                // assign new capacity
                (*v)->_capacity = ((*v)->_capacity + 1);

                for( int i = ((*v)->_capacity -1); i >= 0; i-- )
                {
                    // if at position add, stop shifting and place item
                    if( i == at )
                    {
                        (*v)->_bucket[i] = item;
                        (*v)->_size++;
                        return true;
                    }
                        // continue shitting all items before position to the right
                    else if( i > 0 )
                        (*v)->_bucket[i] = (*v)->_bucket[i - 1];
                }
            }
        }

    }
    return false;
}
int handy_contain   ( handy_vector * v, void * item )
{
    for( int i = 0; i < (*v)->_size; i++ )
    {
        if( memcmp( &((*v)->_bucket[i]), &item, sizeof(&((*v)->_bucket[i])) ) == 0 )
            return i;
    }
    return -1;

}
bool handy_rem_at   ( handy_vector * v, int at )
{
    if( at < 0 || at > (*v)->_size )
        return false;

    else if( (*v)->_bucket[at] == NULL )
        return true; // don't know, but since noting is there is as well as removed
    else
    {
        // found position to delete, shift all item from right to left
        // and fill position with left most item form position.
        // we go to capacity - 1 since we are deleting
        for( int i = at; i < ((*v)->_capacity - 1); i++ )
        {
            (*v)->_bucket[i] = (*v)->_bucket[i + 1];
        }
        (*v)->_bucket[(*v)->_size--] = NULL;
    }
    return true;
}
int handy_capacity  ( handy_vector * v )
{
    return (*v)->_capacity;
}
void handy_free     ( handy_vector * v )
{
    //
    for( int i = 0; i < (*v)->_size; i++ )
        (*v)->_bucket[i] = ( free((*v)->_bucket[i]), NULL );

    // (*v)->_bucket = (free( (*v)->_bucket ), NULL );
}