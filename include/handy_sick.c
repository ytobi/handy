#include "handy_sick.h"

void   handy_destroy_client( handy_client * c );
void   handy_destroy_server( handy_server * s );

bool   handy_connect_client( handy_client * h );
bool   handy_connect_server( handy_server * h );

void   handy_disconnect_client ( handy_client * h );
void   handy_disconnect_server ( handy_server * h );

char * handy_name       ( handy_server * h );
char * handy_ip         ( handy_server * h );
char * handy_port       ( handy_server * h );
char * handy_family     ( handy_server * h );
char * handy_type       ( handy_server * h );
char * handy_recv       ( handy_server * h );
int    handy_send       ( handy_server * h, char * msg );
char * handy_error_msg  ( handy_server * h );

handy_client handy_create_client ( char * destination, char * port )
{
    handy_client temp_client = malloc( sizeof(*temp_client) );

    temp_client->connect = handy_connect_client;
    temp_client->send    = handy_send;
    temp_client->recv    = handy_recv;
    temp_client->disconnect = handy_disconnect_client;

    struct addrinfo hints, *result;

    memset( &hints, 0, sizeof hints );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo( destination, port, &hints, &result );

    // find the correct one in hints and assign to (*s).sick_struct
    // result  is a linkedlist of addrinfo check for correct one
    // assign to (*c).client_struct
    (temp_client)->client_struct = result;

    return temp_client;

}
handy_server handy_create_server ( char * host, char * port )
{
    handy_server temp_server = malloc( sizeof(*temp_server) );

    temp_server->connect = handy_connect_server;
    temp_server->send    = handy_send;
    temp_server->recv    = handy_recv;
    temp_server->disconnect = handy_disconnect_server;

    struct addrinfo hints, *result;

    memset( &hints, 0, sizeof hints );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // find the correct one in hints and assign to (*s).sick_struct
    // result  is a linkedlist of addrinfo check for correct one
    // assign to (*s).client_struct
    getaddrinfo( NULL, port, &hints, &result );

    temp_server->server_struct = result;

    return temp_server;
}

void       handy_destroy_client( handy_client * c )
{}
void       handy_destroy_server( handy_server * s )
{}

bool   handy_connect_client( handy_client * c )
{
    // check make sure were are connected to a port, probably force it.
    // and that we got the fd

    for( ; (*c)->client_struct != NULL; (*c)->client_struct->ai_next )
    {
        (*c)->conn_fd = socket( (*c)->client_struct->ai_family, (*c)->client_struct->ai_socktype,
                                (*c)->client_struct->ai_protocol );
        if( (*c)->conn_fd < 0 )
        {
            (*c)->error_msg = errno;
            continue;
        }
        else
            break;
    }
    // connect
    // this is for client to connect, servers will listen and accept
    if( connect( (*c)->conn_fd, (*c)->client_struct->ai_addr, (*c)->client_struct->ai_addrlen ) < -1 )
    {
        (*c)->error_msg = errno;
        return false;
    }

    return true;
    // we are surely connected
}
bool   handy_connect_server ( handy_server * s )
{
    // check make sure were are connected to a port, probably force it.
    // and that we got the fd

    for( ; (*s)->server_struct != NULL; (*s)->server_struct->ai_next )
    {
        (*s)->sick_fd = socket( (*s)->server_struct->ai_family, (*s)->server_struct->ai_socktype,
                                (*s)->server_struct->ai_protocol );
        if( (*s)->sick_fd  < 0 )
        {
            (*s)->error_msg = errno;
            continue;
        }
        else
            break;
    }

    if( bind( (*s)->sick_fd, (*s)->server_struct->ai_addr, (*s)->server_struct->ai_addrlen) < 0 )
    {
        (*s)->error_msg = errno;
        return false;
    }

    if( listen( (*s)->sick_fd, MAX_CONNECTION ) < 0 )
    {
        (*s)->error_msg = errno;
        return false;
    }

    printf( "Waiting for connection...\n" );

    (*s)->conn_fd = accept( (*s)->sick_fd, &((*s)->client_struct), sizeof ((*s)->client_struct) );
    if( (*s)->conn_fd < 0 )
    {
        (*s)->error_msg = errno;
        return false;
    }

    // we handle just single connections
    close( (*s)->sick_fd );

    return true;
}

void   handy_disconnect_server ( handy_server * s )
{
    close( (*s)->sick_fd );
    close( (*s)->conn_fd );
}
void   handy_disconnect_client ( handy_client * c )
{
    close( (*c)->conn_fd );
}
char * handy_name       ( handy_server * s )
{
    char * ip;
    inet_ntop( (*s)->server_struct->ai_family, (*s)->server_struct->ai_addr->sa_data, ip, sizeof (*ip) );
    return ip;
}
char * handy_ip         ( handy_server * s )
{
}
char * handy_port       ( handy_server * s )
{}
char * handy_family     ( handy_server * s )
{}
char * handy_type       ( handy_server * s )
{}
char * handy_recv       ( handy_server * s )
{
     recv( (*s)->conn_fd,  &((*s)->recv_message), MAX_READ, 0 );
}
int handy_send          ( handy_server * s, char * msg )
{
    printf( "server >> %s\n", msg );
    return  send( (*s)->conn_fd, msg, sizeof(msg), 0 );
}
char * handy_error_msg  ( handy_server * s )
{
    return (char *) (*s)->error_msg;
}