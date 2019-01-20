#include <string.h>
#include "handy_vector.h"

void * handy_get_at ( handy_vector self, int at );
bool handy_set_at   ( handy_vector self, void * item, int at );
int handy_contain   ( handy_vector self, void * item );
bool handy_rem_at   ( handy_vector self, int at );
int handy_capacity  ( handy_vector self );
void handy_free     ( handy_vector self );

handy_vector handy_create_vector()
{
    handy_vector temp_vector = malloc(sizeof(*temp_vector) );

    temp_vector->_capacity = 1024;
    temp_vector->_size = 0;
    temp_vector->_bucket = malloc( sizeof(*temp_vector->_bucket) * temp_vector->_capacity );

    temp_vector->get_at = handy_get_at;
    temp_vector->set_at = handy_set_at;
    temp_vector->contain= handy_contain;
    temp_vector->rem_at = handy_rem_at;
    temp_vector->capacity= handy_capacity;
    temp_vector->free   = handy_free;

    // Initialise all memory location before using them
    for( int i = 0; i < temp_vector->_capacity; i++ )
    {
        temp_vector->_bucket[i] = NULL;
    }


    return temp_vector;
}

void * handy_get_at ( handy_vector self, int at )
{
    if( at < 0 || at > self->_capacity || self->_bucket[at] == NULL )
        return NULL;
    return self->_bucket[at];
}
bool handy_set_at   ( handy_vector self, void * item, int at )
{
    // if at is less than 0, then we can't add item, must specify a
    // location greater than 0
    if( at < 0 )
        return false;

    else if( at >= self->_capacity )
    {
        // if we have used all our capacity and at is such that we can expand to + 1/4 of original
        // capacity, then expand. +4 is because of integer division
        if( self->_size >= self->_capacity && at < (self->_capacity + ((self->_capacity + 4) / 4)) )
        {
            void ** new = realloc( (self->_bucket), ((self->_capacity + ((self->_capacity + 4) / 4)) * sizeof(*new)) );

            if( new )
            {
                self->_bucket = new;
                // don't know if realloc initialise the newly allocated memory,
                // we do in case not.
                for( int c = self->_capacity; c < (self->_capacity + ((self->_capacity + 4) / 4)); c++ )
                {
                    self->_bucket[c] = NULL;
                }

                self->_capacity = (self->_capacity + ((self->_capacity + 4) / 4));

                self->_bucket[at] = item;

                self->_size++;

                return true;
            }
        }
        else
        {
            // at is more than our capacity, hence increase size up to at, then insert
            // count from zero, hence add +1
            void ** new = realloc( (self->_bucket), ((at + 1) * sizeof(*new)) );

            if( new )
            {
                self->_bucket = new;
                // don't know if realloc initialise the newly allocated memory,
                // we do it increase not.
                for( int c = self->_capacity; c < at; c++ )
                {
                    // (*self)->_bucket[c] = malloc( sizeof((*self)->_bucket[c]) );
                    self->_bucket[c] = NULL;
                }

                self->_capacity = at;

                self->_bucket[at] = item;

                self->_size++;

                return true;
            }
        }

    }
    else
    {
        // if location(at) is empty, just insert at location
        if( self->_bucket[at] == NULL )
        {
            self->_bucket[at] = item;

            self->_size++;

            return true;
        }
        else
        {
            // if location is not empty, but contain another item, then, resize vector and
            // shift all item at location one place to the right.
            // resize vector to capacity + 1
            void ** new = realloc( (self->_bucket), (self->_capacity + 1) * sizeof(*new) );

            if( new )
            {
                self->_bucket = new;

                // initialise allocated space to null
                self->_bucket[self->_capacity] = NULL;

                // shift all items one-place to the right
                // assign new capacity
                self->_capacity = (self->_capacity + 1);

                for( int i = (self->_capacity -1); i >= 0; i-- )
                {
                    // if at position add, stop shifting and place item
                    if( i == at )
                    {
                        self->_bucket[at] = item;

                        self->_size++;

                        return true;
                    }
                        // continue shitting all items before position to the right
                    else if( i > 0 )
                        self->_bucket[i] = self->_bucket[i - 1];
                }
            }
        }

    }
    return false;
}
int handy_contain   ( handy_vector self, void * item )
{
    for( int i = 0; i < self->_size; i++ )
    {
        if( memcmp( &(self->_bucket[i]), &item, sizeof(item) ) == 0 )
            return i;
    }
    return -1;

}
bool handy_rem_at   ( handy_vector self, int at )
{
    if( at < 0 || at > self->_capacity )
        return false;
    else if( self->_bucket[at] == NULL )
        return true; // don't know, but since noting is there is as well as removed
    else
    {
        // found position to delete, shift all item from right to left
        // and fill position with left most item form position.
        // we go to capacity - 1 since we are deleting
        for( int i = at; i < (self->_capacity - 1); i++ )
        {
            self->_bucket[i] = self->_bucket[i + 1];
        }
        self->_bucket[self->_capacity - 1 ] = NULL;
        self->_size--;
    }
    return true;
}
int handy_capacity  ( handy_vector self )
{
    return self->_capacity;
}
void handy_free     ( handy_vector self )
{
    // free all items in list
    self->_bucket = (free( self->_bucket ), NULL );
}
