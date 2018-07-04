#include <stdio.h>
#include "../include/handy.h"

int main()
{
    handy_list myList = handy_create_list();

    for( int i = 0; i < 100; i++ )
        myList->add_back( &myList, i );

    printf(" - %d - \n", myList->remove_at( &myList, 50 ) );        // 49
    printf(" - %d - \n", myList->remove_at( &myList, 50 ) );        // 50
    printf(" - %d - \n", myList->get_at( &myList, myList->size ) ); // 99
    printf(" - %d - \n", myList->remove_front( &myList ) );         // 0
    printf(" - %d - \n", myList->remove_front( &myList ) );         // 1

    myList->push( &myList, 1010 );

    printf(" - %d - \n", myList->pop( &myList ) );                  // 1010

    // TODO
    // printf(" - %d - \n", myList->contain( &myList, 56 ) );

    return 0;
}
