#include <stdio.h>
#include "src/handy.h"

int main()
{
    handy_client hclient = handy_create_client( "127.0.0.1", "50453" );

    hclient->connect( &hclient );

    hclient->recv( &hclient );

    printf("client >> %s \n", hclient->recv_message );


    handy_list my_list = handy_create_list();

    my_list->add_back( &my_list, "Hello!, ", sizeof( "Hello!, " ) );
    my_list->add_back( &my_list, 129, sizeof( 129 ) );

    my_list->free( &my_list );

    printf("- %s -\n", (char *)my_list->pop( &my_list, NULL ) );
    printf("- %d -\n", (int)my_list->pop( &my_list, NULL ) );

    return 0;
}
