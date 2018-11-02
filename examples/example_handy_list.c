#include "../include/handy_list.h"


int main()
{

    handy_list alphabet_list;                                   // create a handy_list object "alphabet_list"

    alphabet_list = handy_create_list();                        // initialize handy_list object


    for( int i = 0; i < 26; i++ )
    {
        alphabet_list->add_at( &alphabet_list, 'A' + i );       // add A - Z to list
    }





    return 0;
}

