#include "../include/handy_hashtbl.h"


int main()
{
    handy_hashtbl my_hashtbl;                           // Declare handy_hashtbl  object

    my_hashtbl = handy_create_hashtbl();                // initialize hash table object


    my_hashtbl->add( &my_hashtbl, "1y33", 'A' );        // add a char 'A' with key 1y33 to table

    my_hashtbl->add( &my_hashtbl, "a", 1234 );          // add an int with key "a" to table


    bool t = my_hashtbl->contain( &my_hashtbl, "a" );   // check if item with key "a" is in table


    my_hashtbl->remove( &my_hashtbl, "1y33" );          // remove key-value pair from table

    my_hashtbl->free( &my_hashtbl );                    // free all memory allocated to table


    free( my_hashtbl );                                 // finally free handy_hashtbl object as well


    return 0;
}
