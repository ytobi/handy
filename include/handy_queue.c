
#include "handy_queue.h"

bool   handy_queue_contain    ( handy_queue * l, void * item );
bool   handy_queue_enqueue    ( handy_queue * l, void * item );
bool   handy_queue_empty      ( handy_queue * l );
void * handy_queue_reverse    ( handy_queue * l );
void * handy_queue_dequeue    ( handy_queue * l );
void   handy_queue_free       ( handy_queue * l );
void * handy_queue_front      ( handy_queue * l );
void * handy_queue_back       ( handy_queue * l );

handy_queue handy_create_queue()
{
    struct queue_struct *  temp_list = malloc( sizeof(*temp_list) );

    temp_list->size = 0;

    temp_list->contain       = handy_queue_contain;
    temp_list->enqueue       = handy_queue_enqueue;
    temp_list->empty         = handy_queue_empty;
    temp_list->reverse       = handy_queue_reverse;
    temp_list->dequeue       = handy_queue_dequeue;
    temp_list->free          = handy_queue_free;
    temp_list->front         = handy_queue_front;
    temp_list->back          = handy_queue_back;

    return temp_list;
}
bool   handy_queue_contain    ( handy_queue * l, void * item )
{
    handy_Obj iter = (*l)->first;
    for( int i = 0; i < (*l)->size; i++ )
    {
        if( memcmp( iter->data, item, iter->size ) == 0 )
            return true;
        iter = iter->next;
    }
    return false;
}
bool   handy_queue_enqueue    ( handy_queue * l, void * item )
{
    if( (*l)->size == 0 )
    {
        (*l)->first = malloc( sizeof( handy_Obj *) );
        (*l)->first->data = item;
        (*l)->first->size = sizeof( item );

        (*l)->last  = (*l)->first;
        (*l)->size++;
        return true;
    }
    else if ( (*l)->size > 0 )
    {
        handy_Obj temp = malloc( sizeof( * temp ) );

        temp->size = sizeof( item );
        temp->data = item;
        temp->next = (*l)->first;

        (*l)->first->prev = temp;
        (*l)->first = temp;
        (*l)->size++;

        return true;
    }
    return false;
}
bool   handy_queue_empty      ( handy_queue * l )
{
    return (*l)->size == 0 ? true : false;
}
void * handy_queue_reverse    ( handy_queue * l )
{
    return NULL;
}
void * handy_queue_dequeue    ( handy_queue * l )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size == 1 )
    {
        handy_Obj  temp = (*l)->last;
        (*l)->first = (*l)->last = NULL;
        (*l)->size--;

        printf(" - %s - \n", (char *)temp->data );
        return temp->data;
    }
    else if( (*l)->size > 1 )
    {
        handy_Obj temp = (*l)->last;
        (*l)->last = (*l)->last->prev;

        (*l)->size--;
        return temp->data;
    }
    return NULL;
}
void   handy_queue_free       ( handy_queue * l )
{
    return;
}
void * handy_queue_front      ( handy_queue * l )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size > 0 )
    {
        return  (*l)->first->data;
    }
    return NULL;
}
void * handy_queue_back       ( handy_queue * l )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size > 0 )
    {
        return  (*l)->last->data;
    }
    return NULL;
}

