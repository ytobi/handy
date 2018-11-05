#include "handy_queue.h"

int   handy_queue_contain    ( handy_queue * q, void * item );
bool   handy_queue_enqueue    ( handy_queue * q, void * item );
bool   handy_queue_empty      ( handy_queue * q );
void   handy_queue_reverse    ( handy_queue * q );
void * handy_queue_dequeue    ( handy_queue * q );
void   handy_queue_free       ( handy_queue * q );
void * handy_queue_front      ( handy_queue * q );
void * handy_queue_back       ( handy_queue * q );
int    handy_queue_length     ( handy_queue * q );

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

int   handy_queue_contain    ( handy_queue * q, void * item )
{
    _handy_queue_obj iter = (*q)->_first;

    for( int i = 0; i < (*q)->_size; i++ )
    {
        if( memcmp( &iter->_data, &item, sizeof(iter->_data) ) == 0 )
            return i;
        iter = iter->_next;
    }
    return -1;
}
bool   handy_queue_enqueue    ( handy_queue * q, void * item )
{
    if( (*q)->_size == 0 )
    {
        // create and assign new item to add
        _handy_queue_obj temp = malloc( sizeof( * temp ) );
        temp->_data = item;

        // first item in queue, _first and _last point to same item
        (*q)->_last  = (*q)->_first = temp;

        (*q)->_size++;

        return true;
    }
    else if ( (*q)->_size > 0 )
    {
        _handy_queue_obj temp = malloc( sizeof( * temp ) );

        temp->_data = item;

        temp->_prev = (*q)->_last;
        (*q)->_last->_next = temp;

        (*q)->_last = temp;
        (*q)->_size++;

        return true;
    }
    return false;
}
bool   handy_queue_empty      ( handy_queue * q )
{
    return (*q)->_size == 0 ? true : false;
}
void handy_queue_reverse      ( handy_queue * q )
{
    // The front point the end, and _next and _prev of every node
    // reversed.

    _handy_queue_obj hold_front = (*q)->_first;
    _handy_queue_obj hold_back = (*q)->_last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < ((*q)->_size / 2); i++ )
    {
        temp_data = hold_front->_data;
        hold_front->_data = hold_back->_data;
        hold_back->_data = temp_data;

        hold_front = hold_front->_next;
        hold_back = hold_back->_prev;
    }
}
void * handy_queue_dequeue    ( handy_queue * q )
{
    memset( &((*q)->_handy_dequeued[0]), NULL, sizeof(*((*q)->_handy_dequeued)) );

    if( (*q)->_size == 1 )
    {
        memcpy( &((*q)->_handy_dequeued[0]), &((*q)->_first->_data), sizeof(*(*q)->_handy_dequeued) );

        (*q)->_first = ( free((*q)->_first), NULL );
        (*q)->_first = (*q)->_last = NULL;

        (*q)->_size--;
    }
    else if( (*q)->_size > 1 )
    {
        memcpy( &((*q)->_handy_dequeued[0]), &(*q)->_first->_data, sizeof(*(*q)->_handy_dequeued) );

        (*q)->_first = (*q)->_first->_next;
        (*q)->_first->_prev = ( free((*q)->_first->_prev), NULL );

        (*q)->_size--;
    }

    return *((*q)->_handy_dequeued);
}
void   handy_queue_free       ( handy_queue * q )
{
    // free every item in list and then remove them from the queue
    while( (*q)->_first != (*q)->_last )
    {
        (*q)->_first = (*q)->_first->_next;

        (*q)->_first->_prev = (free( (*q)->_first->_prev ), NULL);
    }
    (*q)->_first = (free( (*q)->_first ), NULL);
    (*q)->_size = 0;

    (*q)->_handy_dequeued = ( free((*q)->_handy_dequeued), NULL );
}
void * handy_queue_front      ( handy_queue * q )
{
    if( (*q)->_size == 0 )
    {
        return NULL;
    }
    else if( (*q)->_size > 0 )
    {
        return  (*q)->_first->_data;
    }
    return NULL;
}
void * handy_queue_back       ( handy_queue * q )
{
    if( (*q)->_size == 0 )
    {
        return NULL;
    }
    else if( (*q)->_size > 0 )
    {
        return  (*q)->_last->_data;
    }
    return NULL;
}
int    handy_queue_length     ( handy_queue * q )
{
    return (*q)->_size;
}

