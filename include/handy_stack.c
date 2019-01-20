#include "handy_stack.h"

bool   handy_stack_contain    ( handy_stack self, void * item );
bool   handy_stack_push       ( handy_stack self, void * item );
bool   handy_stack_empty      ( handy_stack self );
void   handy_stack_reverse    ( handy_stack self );
void * handy_stack_pop        ( handy_stack self );
void   handy_stack_free       ( handy_stack self );
void * handy_stack_top        ( handy_stack self );
void * handy_stack_bottom     ( handy_stack self );
int    handy_stack_length     ( handy_stack self );

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
bool   handy_stack_contain    ( handy_stack self, void * item )
{
    _handy_stack_obj iter = self->_first;
    for( int i = 0; i < self->_size; i++ )
    {
        if( memcmp( &(iter->_data), &item, sizeof(iter->_data) ) == 0 )
            return true;
        iter = iter->_next;
    }
    return false;
}
bool   handy_stack_push       ( handy_stack self, void * item )
{
    if( self->_size == 0 )
    {
        _handy_stack_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;

        self->_last  = self->_first = temp;

        self->_size++;

        return true;
    }
    else if ( self->_size > 0 )
    {
        _handy_stack_obj temp = malloc( sizeof( *temp ) );

        temp->_data = item;
        temp->_next = self->_first;

        self->_first->_prev = temp;
        self->_first = temp;
        self->_size++;

        return true;
    }
    return false;
}
bool   handy_stack_empty      ( handy_stack self )
{
    return self->_size == 0 ? true : false;
}
void   handy_stack_reverse    ( handy_stack self )
{
    // The front point the end, and _next and _prev of every node
    // reversed.

    _handy_stack_obj hold_top = self->_first;
    _handy_stack_obj hold_bottom = self->_last;

    void * temp_data;

    // exchange front and back till we reach middle
    for( int i = 0 ; i < (self->_size / 2); i++ )
    {
        temp_data = hold_top->_data;
        hold_top->_data = hold_bottom->_data;
        hold_bottom->_data = temp_data;

        hold_top = hold_top->_next;
        hold_bottom = hold_bottom->_prev;
    }
}
void * handy_stack_pop        ( handy_stack self )
{
    // set temp storage to null in case something goes wrong
    memset( &(self->_handy_poped[0]), NULL, sizeof(*self->_handy_poped) );

    if( self->_size == 0 )
        return NULL;
    else if( self->_size == 1 )
    {
        memcpy( &(self->_handy_poped[0]), &self->_first->_data, sizeof(*self->_handy_poped) );

        // free the memory of the item to remove
        self->_first = ( free(self->_first), NULL );
        self->_first = self->_last = NULL;

        self->_size--;
    }
    else if( self->_size > 1 )
    {
        memcpy( &(self->_handy_poped[0]), &self->_first->_data, sizeof(*self->_handy_poped) );

        // free the memory of the item to remove
        self->_first = self->_first->_next;
        self->_first->_prev = ( free(self->_first->_prev), NULL );


        self->_size--;
    }
    return *self->_handy_poped;
}
void   handy_stack_free       ( handy_stack self )
{
   while( self->_first != self->_last )
    {
        self->_first = self->_first->_next;

        self->_first->_prev = ( free( self->_first->_prev ), NULL );
    }
    self->_first = ( free( self->_first ), NULL );
    self->_size = 0;

    self->_handy_poped = ( free(self->_handy_poped), NULL );
}
void * handy_stack_top        ( handy_stack self )
{
    if( self->_size == 0 )
    {
        return NULL;
    }
    else if( self->_size > 0 )
    {
        return self->_first->_data;
    }
    return NULL;
}
void * handy_stack_bottom     ( handy_stack self )
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
int    handy_stack_length     ( handy_stack self)
{
    return self->_size;
}
