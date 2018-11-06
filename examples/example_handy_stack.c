#include "../include/handy_stack.h"


int main()
{
    handy_stack my_stack;                           // declare handy_stack object

    my_stack = handy_create_stack();                // initialise my_stack object


    for( int i = 0; i < 10; i++ )                   // add 0 - 10 items to the stack
        if( my_stack->push(&my_stack, i) );


    int lent = my_stack->length( &my_stack );       // we can also know the length of the stack

    bool con = my_stack->contain( &my_stack, 0 );   // let's check if 0 is on the stack

    int top_item = my_stack->top( &my_stack );      // let's get the top item, but we do not remove the item
    int rem_top_item = my_stack->pop( &my_stack );  // let's remove the top item from the stack


    my_stack->reverse( &my_stack );                 // reverse all items on the stack


    my_stack->free( &my_stack );                    // free all memory allocated by my_stack

    free( my_stack );                               // cleanup, free my_stack it self


    return  0;
}