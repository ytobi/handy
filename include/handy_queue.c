#include "handy_queue.h"

int   handy_queue_contain     ( handy_queue self, void * item );
bool   handy_queue_enqueue    ( handy_queue self, void * item );
bool   handy_queue_empty      ( handy_queue self );
void   handy_queue_reverse    ( handy_queue self );
void * handy_queue_dequeue    ( handy_queue self );
void   handy_queue_free       ( handy_queue self );
void * handy_queue_front      ( handy_queue self );
void * handy_queue_back       ( handy_queue self );
int    handy_queue_length     ( handy_queue self );

handy_queue handy_create_queue()
{
    handy_queue  temp_queue = malloc( sizeof(*temp_queue) );

    temp_queue->_handy_dequeued = malloc( sizeof(*temp_queue->_handy_dequeued) );

    temp_queue->_first = temp_queue->_last = NULL;
    temp_queue->_size = 0;

    temp_queue->contain       = handy_queue_contain;
    temp_queue->enqueue       = handy_queue_enqueue;
    temp_queue->empty         = handy_queue_empty;
    temp_queue->reverse       = handy_queue_reverse;
    temp_queue->dequeue       = handy_queue_dequeue;
    temp_queue->free          = handy_queue_free;
    temp_queue->front         = handy_queue_front;
    temp_queue->back          = handy_queue_back;
    temp_queue->length        = handy_queue_length;

    return temp_queue;
}

int   handy_queue_contain    ( handy_queue self, void * item )
{
    _handy_queue_obj iter = self->_first;

    for( int i = 0; i < self->_size; i++ )
    {
        if( memcmp( &iter->_data, &item, sizeof(iter->_data) ) == 0 )
            return i;
        iter = iter->_next;
    }
    return -1;
}
bool   handy_queue_enqueue    ( handy_queue self, void * item )
{
    if( self->_size == 0 )
    {
        // create and assign new item to add
        _handy_queue_obj temp = malloc( sizeof( * temp ) );
        temp->_data = item;

        // first item in queue, _first and _last point to same item
        self->_last  = self->_first = temp;

        self->_size++;

        return true;
    }
    else if ( self->_size > 0 )
    {
        _handy_queue_obj temp = malloc( sizeof( * temp ) );

        temp->_data = item;

        temp->_prev = self->_last;
        self->_last->_next = temp;

        self->_last = temp;
        self->_size++;

        return true;
    }
    return false;
}
bool   handy_queue_empty      ( handy_queue self )
{
    return self->_size == 0 ? true : false;
}
void handy_queue_reverse      ( handy_queue self )
{
    // The front point the end, and _next and _prev of every node
    // reversed.

    _handy_queue_obj hold_front = self->_first;
    _handy_queue_obj hold_back = self->_last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < (self->_size / 2); i++ )
    {
        temp_data = hold_front->_data;
        hold_front->_data = hold_back->_data;
        hold_back->_data = temp_data;

        hold_front = hold_front->_next;
        hold_back = hold_back->_prev;
    }
}
void * handy_queue_dequeue    ( handy_queue self )
{
    memset( &(self->_handy_dequeued[0]), NULL, sizeof(*(self->_handy_dequeued)) );

    if( self->_size == 1 )
    {
        memcpy( &(self->_handy_dequeued[0]), &(self->_first->_data), sizeof(*self->_handy_dequeued) );

        self->_first = ( free(self->_first), NULL );
        self->_first = self->_last = NULL;

        self->_size--;
    }
    else if( self->_size > 1 )
    {
        memcpy( &(self->_handy_dequeued[0]), &self->_first->_data, sizeof(*self->_handy_dequeued) );

        self->_first = self->_first->_next;
        self->_first->_prev = ( free(self->_first->_prev), NULL );

        self->_size--;
    }

    return *(self->_handy_dequeued);
}
void   handy_queue_free       ( handy_queue self )
{
    // free every item in list and then remove them from the queue
    while( self->_first != self->_last )
    {
        self->_first = self->_first->_next;

        self->_first->_prev = (free( self->_first->_prev ), NULL);
    }
    self->_first = (free( self->_first ), NULL);
    self->_size = 0;

    self->_handy_dequeued = ( free(self->_handy_dequeued), NULL );
}
void * handy_queue_front      ( handy_queue self )
{
    if( self->_size == 0 )
    {
        return NULL;
    }
    else if( self->_size > 0 )
    {
        return  self->_first->_data;
    }
    return NULL;
}
void * handy_queue_back       ( handy_queue self )
{
    if( self->_size == 0 )
    {
        return NULL;
    }
    else if( self->_size > 0 )
    {
        return  self->_last->_data;
    }
    return NULL;
}
int    handy_queue_length     ( handy_queue self )
{
    return self->_size;
}

