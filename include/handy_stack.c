
#include "handy_stack.h"

bool   handy_stack_contain    ( handy_stack * s, void * item );
bool   handy_stack_push       ( handy_stack * s, void * item );
bool   handy_stack_empty      ( handy_stack * s );
void * handy_stack_reverse    ( handy_stack * s );
void * handy_stack_pop        ( handy_stack * s );
void   handy_stack_free       ( handy_stack * s );
void * handy_stack_top        ( handy_stack * s );
void * handy_stack_bottom     ( handy_stack * s );

handy_stack handy_create_stack()
{
    handy_stack  temp_list = malloc( sizeof(*temp_list) );

    temp_list->size = 0;

    temp_list->contain       = handy_stack_contain;
    temp_list->push          = handy_stack_push;
    temp_list->empty         = handy_stack_empty;
    temp_list->reverse       = handy_stack_reverse;
    temp_list->pop           = handy_stack_pop;
    temp_list->free          = handy_stack_free;
    temp_list->top           = handy_stack_top;
    temp_list->bottom        = handy_stack_bottom;

    return temp_list;
}
bool   handy_stack_contain    ( handy_stack * s, void * item )
{
    handy_Obj iter = (*s)->first;
    for( int i = 0; i < (*s)->size; i++ )
    {
        if( memcmp( &(iter->data), &item, iter->size ) == 0 )
            return true;
        iter = iter->next;
    }
    return false;
}
bool   handy_stack_push       ( handy_stack * s, void * item )
{
    if( (*s)->size == 0 )
    {
        handy_Obj temp = malloc( sizeof( *temp ) );

        temp->data = item;
        temp->size = sizeof( item );

        (*s)->last  = (*s)->first = temp;

        (*s)->size++;

        return true;
    }
    else if ( (*s)->size > 0 )
    {
        handy_Obj temp = malloc( sizeof( *temp ) );

        temp->size = sizeof( item );;
        temp->data = item;
        temp->next = (*s)->first;

        (*s)->first->prev = temp;
        (*s)->first = temp;
        (*s)->size++;

        return true;
    }
    return false;
}
bool   handy_stack_empty      ( handy_stack * s )
{
    return (*s)->size == 0 ? true : false;
}
void * handy_stack_reverse    ( handy_stack * s )   // TODO
{
    return NULL;
}
void * handy_stack_pop        ( handy_stack * s )
{
    if( (*s)->size == 0 )
        return NULL;
    else if( (*s)->size == 1 )
    {
        handy_Obj  temp = (*s)->first;
        (*s)->first = (*s)->last = NULL;
        (*s)->size--;

        return temp->data;
    }
    else if( (*s)->size > 1 )
    {
        handy_Obj temp = (*s)->first;
        (*s)->first = (*s)->first->next;

        (*s)->size--;
        return temp->data;
    }
    return NULL;
}
void   handy_stack_free       ( handy_stack * s )
{
    // free every item in list and then remove them from the list
    while( (*s)->size > 0 )
    {
        free( (*s)->first );
        (*s)->pop(s);
    }
}
void * handy_stack_top        ( handy_stack * s )
{
    if( (*s)->size == 0 )
    {
        return NULL;
    }
    else if( (*s)->size > 0 )
    {
        return  (*s)->first->data;
    }
    return NULL;
}
void * handy_stack_bottom     ( handy_stack * s )
{
    if( (*s)->size == 0 )
    {
        return NULL;
    }
    else if( (*s)->size > 0 )
    {
        return  (*s)->last->data;
    }
    return NULL;
}