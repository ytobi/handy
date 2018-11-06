#include "../include/handy_vector.h"


int main()
{
    handy_vector my_vector;                             // declare handy_vector object

    my_vector = handy_create_vector();                  // initialise handy_vector object

    int init_cap = my_vector->capacity( &my_vector );   // initial capacity is 1024

    for( int i = 0; i < 10; i++ )                       // let's add 0 - 9 item to the vector
        my_vector->set_at( &my_vector, i, i );


    int zero = my_vector->get_at( &my_vector, 0 );      // get item at position 0, but do not remove the item

    my_vector->rem_at( &my_vector, 0 );                 // well okay, let's remove the item


    my_vector->set_at( &my_vector, "Hello, World" );    // let set a string at position zero, handy_vector is generic
                                                        // ie. can hold different types


    my_vector->free( &my_vector );                      // free all memory allocated by my_vector


    free( my_vector );                                  // final cleanup, free my_vector itself
}