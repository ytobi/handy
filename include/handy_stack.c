#include "handy_stack.h"

bool   handy_stack_contain    ( handy_stack s, void * item );
bool   handy_stack_push       ( handy_stack s, void * item );
bool   handy_stack_empty      ( handy_stack s );
void   handy_stack_reverse    ( handy_stack s );
void * handy_stack_pop        ( handy_stack s );
void   handy_stack_free       ( handy_stack s );
void * handy_stack_top        ( handy_stack s );
void * handy_stack_bottom     ( handy_stack s );
int    handy_stack_length     ( handy_stack s );

handy_stack handy_create_stack()
{
    handy_stack  temp_stack = malloc( sizeof(*temp_stack) );

    temp_stack->_size = 0;
    temp_stack->_handy_poped = malloc( sizeof(*temp_stack->_handy_poped) );
    temp_stack->_first = temp_stack->_last = NULL;

    temp_stack->contain       = handy_stack_contain;
    temp_stack->push          = handy_stack_push;
    temp_stack->empty         = handy_stack_empty;
    temp_stack->reverse       = handy_stack_reverse;
    temp_stack->pop           = handy_stack_pop;
    temp_stack->free          = handy_stack_free;
    temp_stack->top           = handy_stack_top;
    temp_stack->bottom        = handy_stack_bottom;
    temp_stack->length        = handy_stack_length;

    return temp_stack;
}
bool   handy_stack_contain    ( handy_stack s, void * item )
{
    _handy_stack_obj iter = s->_first;
    for( int i = 0; i < s->_size; i++ )
    {
        if( memcmp( &(iter->_data), &item, sizeof(iter->_data) ) == 0 )
            return true;
        iter = iter->_next;
    }
    return false;
}
bool   handy_stack_push       ( handy_stack s, void * item )
{
    if( s->_size == 0 )
    {
        _handy_stack_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;

        s->_last  = s->_first = temp;

        s->_size++;

        return true;
    }
    else if ( s->_size > 0 )
    {
        _handy_stack_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;
        temp->_next = s->_first;

        s->_first->_prev = temp;
        s->_first = temp;
        s->_size++;

        return true;
    }
    return false;
}
bool   handy_stack_empty      ( handy_stack s )
{
    return s->_size == 0 ? true : false;
}
void   handy_stack_reverse    ( handy_stack s )
{
    // The front point the end, and _next and _prev of every node
    // reversed.

    _handy_stack_obj hold_top = s->_first;
    _handy_stack_obj hold_bottom = s->_last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < (s->_size / 2); i++ )
    {
        temp_data = hold_top->_data;
        hold_top->_data = hold_bottom->_data;
        hold_bottom->_data = temp_data;

        hold_top = hold_top->_next;
        hold_bottom = hold_bottom->_prev;
    }
}
void * handy_stack_pop        ( handy_stack s )
{
    // set temp storage to null in case something goes wrong
    memset( &(s->_handy_poped[0]), NULL, sizeof(*s->_handy_poped) );

    if( s->_size == 0 )
        return NULL;
    else if( s->_size == 1 )
    {
        memcpy( &(s->_handy_poped[0]), &s->_first->_data, sizeof(*s->_handy_poped) );

        // free the memory of the item to remove
        s->_first = ( free(s->_first), NULL );
        s->_first = s->_last = NULL;

        s->_size--;
    }
    else if( s->_size > 1 )
    {
        memcpy( &(s->_handy_poped[0]), &s->_first->_data, sizeof(*s->_handy_poped) );

        // free the memory of the item to remove
        s->_first = s->_first->_next;
        s->_first->_prev = ( free(s->_first->_prev), NULL );


        s->_size--;
    }
    return *s->_handy_poped;
}
void   handy_stack_free       ( handy_stack s )
{
   while( s->_first != s->_last )
    {
        s->_first = s->_first->_next;

        s->_first->_prev = ( free( s->_first->_prev ), NULL );
    }
    s->_first = ( free( s->_first ), NULL );
    s->_size = 0;

    s->_handy_poped = ( free(s->_handy_poped), NULL );
}
void * handy_stack_top        ( handy_stack s )
{
    if( s->_size == 0 )
    {
        return NULL;
    }
    else if( s->_size > 0 )
    {
        return s->_first->_data;
    }
    return NULL;
}
void * handy_stack_bottom     ( handy_stack s )
{
    if( s->_size == 0 )
    {
        return NULL;
    }
    else if( s->_size > 0 )
    {
        return  s->_last->_data;
    }
    return NULL;
}
int    handy_stack_length     ( handy_stack s)
{
    return s->_size;
}
