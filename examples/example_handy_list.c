#include "../include/handy_list.h"


int main()
{
    handy_list alphabet_list;                                  // create a handy_list object "alphabet_list"


    alphabet_list = handy_create_list();                       // initialize handy_list object


    for( int i = 0; i < 26; i++ )
    {
        alphabet_list->add_at( alphabet_list, 'A' + i, i );    // add A - Z to list
    }

    int contains = alphabet_list->contain( alphabet_list, 'Z' );// if contains, returns position of item else return -1

    alphabet_list->reverse( alphabet_list );                   // reverse all items in list

    int len = alphabet_list->length( alphabet_list );          // returns number of item in list.

    alphabet_list->rem_back( alphabet_list );                  // remove item at back 'A'

    alphabet_list->add_back( alphabet_list, 'A' );             // add 'A' to back of list



    alphabet_list->free( alphabet_list );                      // free all memory allocated to items in list

    free( alphabet_list );                                     // finally clean up, free alphabet itself


    return 0;
}

