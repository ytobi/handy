
#include "handy_queue.h"

bool   handy_queue_contain    ( handy_queue * q, void * item );
bool   handy_queue_enqueue    ( handy_queue * q, void * item );
bool   handy_queue_empty      ( handy_queue * q );
void * handy_queue_reverse    ( handy_queue * q );
void * handy_queue_dequeue    ( handy_queue * q );
void   handy_queue_free       ( handy_queue * q );
void * handy_queue_front      ( handy_queue * q );
void * handy_queue_back       ( handy_queue * q );

handy_queue handy_create_queue()
{
    struct queue_struct *  temp_queue = malloc( sizeof(*temp_queue) );

    temp_queue->size = 0;

    temp_queue->contain       = handy_queue_contain;
    temp_queue->enqueue       = handy_queue_enqueue;
    temp_queue->empty         = handy_queue_empty;
    temp_queue->reverse       = handy_queue_reverse;
    temp_queue->dequeue       = handy_queue_dequeue;
    temp_queue->free          = handy_queue_free;
    temp_queue->front         = handy_queue_front;
    temp_queue->back          = handy_queue_back;

    return temp_queue;
}
bool   handy_queue_contain    ( handy_queue * q, void * item )
{
    handy_Obj iter = (*q)->first;
    for( int i = 0; i < (*q)->size; i++ )
    {
        if( memcmp( &iter->data, &item, iter->size ) == 0 )
            return true;
        iter = iter->next;
    }
    return false;
}
bool   handy_queue_enqueue    ( handy_queue * q, void * item )
{
    if( (*q)->size == 0 )
    {
        handy_Obj temp = malloc( sizeof( * temp ) );

        temp->data = item;
        temp->size = sizeof( item );

        (*q)->last  = (*q)->first = temp;

        (*q)->size++;

        return true;
    }
    else if ( (*q)->size > 0 )
    {
        handy_Obj temp = malloc( sizeof( * temp ) );

        temp->size = sizeof( item );
        temp->data = item;

        temp->prev = (*q)->last;
        (*q)->last->next = temp;

        (*q)->last = temp;
        (*q)->size++;

        return true;
    }
    return false;
}
bool   handy_queue_empty      ( handy_queue * q )
{
    return (*q)->size == 0 ? true : false;
}
void * handy_queue_reverse    ( handy_queue * q )   // TODO
{
    return NULL;
}
void * handy_queue_dequeue    ( handy_queue * q )
{
    if( (*q)->size == 0 )
        return NULL;
    else if( (*q)->size == 1 )
    {
        handy_Obj  temp = (*q)->first;
        (*q)->first = (*q)->last = NULL;
        (*q)->size--;

        return temp->data;
    }
    else if( (*q)->size > 1 )
    {
        handy_Obj temp = (*q)->first;
        (*q)->first = (*q)->first->next;

        (*q)->size--;
        return temp->data;
    }
    return NULL;
}
void   handy_queue_free       ( handy_queue * q )
{
    // free every item in list and then remove them from the queue
    while( (*q)->size > 0 )
    {
        free( (*q)->first );
        (*q)->dequeue(q);
    }
}
void * handy_queue_front      ( handy_queue * q )
{
    if( (*q)->size == 0 )
    {
        return NULL;
    }
    else if( (*q)->size > 0 )
    {
        return  (*q)->first->data;
    }
    return NULL;
}
void * handy_queue_back       ( handy_queue * q )
{
    if( (*q)->size == 0 )
    {
        return NULL;
    }
    else if( (*q)->size > 0 )
    {
        return  (*q)->last->data;
    }
    return NULL;
}

