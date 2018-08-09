
#include "handy_stack.h"

bool   handy_stack_contain    ( handy_stack * l, void * item );
bool   handy_stack_push       ( handy_stack * l, void * item );
bool   handy_stack_empty      ( handy_stack * l );
void * handy_stack_reverse    ( handy_stack * l );
void * handy_stack_pop        ( handy_stack * l );
void   handy_stack_free       ( handy_stack * l );
void * handy_stack_top        ( handy_stack * l );
void * handy_stack_end        ( handy_stack * l );

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
    temp_list->end           = handy_stack_end;

    return temp_list;
}
bool   handy_stack_contain    ( handy_stack * l, void * item )
{
    handy_Obj iter = (*l)->first;
    for( int i = 0; i < (*l)->size; i++ )
    {
        if( memcmp( &(iter->data), &item, sizeof( iter->data ) ) == 0 )
            return true;
        iter = iter->next;
    }
    return false;
}
bool   handy_stack_push       ( handy_stack * l, void * item )
{
    if( (*l)->size == 0 )
    {
        (*l)->first = malloc( sizeof(handy_Obj *) );
        (*l)->first->data = item;
        (*l)->first->size = sizeof( item );

        (*l)->last  = (*l)->first;
        (*l)->size++;
        return true;
    }
    else if ( (*l)->size > 0 )
    {
        handy_Obj temp = malloc( sizeof(* temp) );

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
bool   handy_stack_empty      ( handy_stack * l )
{
    return (*l)->size == 0 ? true : false;
}
void * handy_stack_reverse    ( handy_stack * l )
{
    return NULL;
}
void * handy_stack_pop        ( handy_stack * l )
{
    if( (*l)->size == 0 )
    {
        return NULL;
    }
    else if( (*l)->size == 1 )
    {
        handy_Obj  temp = (*l)->first;
        (*l)->first = (*l)->last = NULL;
        (*l)->size--;

        return temp->data;
    }
    else if( (*l)->size > 1 )
    {
        handy_Obj temp = (*l)->first;
        (*l)->first = (*l)->first->next;

        (*l)->size--;
        return temp->data;
    }
    return NULL;
}
void   handy_stack_free       ( handy_stack * l ) //TODO
{
    return;
}
void * handy_stack_top        ( handy_stack * l )
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
void * handy_stack_end        ( handy_stack * l )
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