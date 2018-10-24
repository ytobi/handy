#include "handy_stack.h"

bool   handy_stack_contain    ( handy_stack * s, void * item );
bool   handy_stack_push       ( handy_stack * s, void * item );
bool   handy_stack_empty      ( handy_stack * s );
void   handy_stack_reverse    ( handy_stack * s );
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
    _handy_stack_obj iter = (*s)->_first;
    for( int i = 0; i < (*s)->size; i++ )
    {
        if( memcmp( &(iter->_data), &item, sizeof(iter->_data) ) == 0 )
            return true;
        iter = iter->_next;
    }
    return false;
}
bool   handy_stack_push       ( handy_stack * s, void * item )
{
    if( (*s)->size == 0 )
    {
        _handy_stack_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;

        (*s)->_last  = (*s)->_first = temp;

        (*s)->size++;

        return true;
    }
    else if ( (*s)->size > 0 )
    {
        _handy_stack_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;
        temp->_next = (*s)->_first;

        (*s)->_first->_prev = temp;
        (*s)->_first = temp;
        (*s)->size++;

        return true;
    }
    return false;
}
bool   handy_stack_empty      ( handy_stack * s )
{
    return (*s)->size == 0 ? true : false;
}
void   handy_stack_reverse    ( handy_stack * s )
{
    // The front point the end, and _next and _prev of every node
    // reversed.

    _handy_stack_obj hold_top = (*s)->_first;
    _handy_stack_obj hold_bottom = (*s)->_last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < ((*s)->size / 2); i++ )
    {
        temp_data = hold_top->_data;
        hold_top->_data = hold_bottom->_data;
        hold_bottom->_data = temp_data;

        hold_top = hold_top->_next;
        hold_bottom = hold_bottom->_prev;
    }
}
void * handy_stack_pop        ( handy_stack * s )
{
    if( (*s)->size == 0 )
        return NULL;
    else if( (*s)->size == 1 )
    {
        void * r_d  = (*s)->_first->_data;

        (*s)->_first = (*s)->_last = NULL;
        (*s)->size--;

        return r_d;
    }
    else if( (*s)->size > 1 )
    {
        void * r_d = (*s)->_first->_data;

        (*s)->_first = (*s)->_first->_next;

        (*s)->size--;
        return r_d;
    }
    return NULL;
}
void   handy_stack_free       ( handy_stack * s )
{
    // free every item in list and then remove them from the list
   /* while( (*s)->size > 0 )
    {
        free( (*s)->_first );
        (*s)->pop(s);
    }*/
   while( (*s)->_first != (*s)->_last )
    {
        (*s)->_first = (*s)->_first->_next;

        (*s)->_first->_prev = ( free( (*s)->_first->_prev ), NULL );
    }
    (*s)->_first = ( free( (*s)->_first ), NULL );
    (*s)->size = 0;
}
void * handy_stack_top        ( handy_stack * s )
{
    if( (*s)->size == 0 )
    {
        return NULL;
    }
    else if( (*s)->size > 0 )
    {
        return  (*s)->_first->_data;
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
        return  (*s)->_last->_data;
    }
    return NULL;
}
