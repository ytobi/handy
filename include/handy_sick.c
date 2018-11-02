#include "handy_sick.h"

void   handy_destroy_client( handy_client * c );
void   handy_destroy_server( handy_server * s );

bool   handy_connect_client( handy_client * h, char * addr, int port );
bool   handy_connect_server( handy_server * h );

void   handy_disconnect_client ( handy_client * h );
void   handy_disconnect_server ( handy_server * h );

char * handy_server_name       ( handy_server * s );
char * handy_client_name       ( handy_client * c );
char * handy_ip         ( handy_server * h );
char * handy_port       ( handy_server * h );
char * handy_family     ( handy_server * h );
char * handy_type       ( handy_server * h );
char * handy_recv       ( handy_server * h );
int    handy_send       ( handy_server * h, char * msg );
char * handy_error_msg  ( handy_server * h );

handy_client handy_create_client()
{
    handy_client temp_client = malloc( sizeof(*temp_client) );

    temp_client->connect = handy_connect_client;
    temp_client->send    = handy_send;
    temp_client->recv    = handy_recv;
    temp_client->disconnect = handy_disconnect_client;
    temp_client->name   = handy_client_name;

    temp_client->_error_message = malloc(1024 * sizeof(char));

    // struct addrinfo hints, *result;

    /*memset( &hints, 0, sizeof(hints) );

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo( destination, port, &hints, &result );

    // find the correct one in hints and assign to (*s).sick_struct
    // result  is a linkedlist of addrinfo check for correct one
    // assign to (*c)._client_struct
    (temp_client)->_destination_struct = result;*/

    return temp_client;

}
handy_server handy_create_server( char * host, char * port )
{
    handy_server temp_server = malloc( sizeof(*temp_server) );

    temp_server->connect = handy_connect_server;
    temp_server->send    = handy_send;
    temp_server->recv    = handy_recv;
    temp_server->disconnect = handy_disconnect_server;
    temp_server->name   = handy_server_name;

    temp_server->_error_message = malloc(1024);
    struct addrinfo hints, *result;

    memset( &hints, 0, sizeof hints );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // find the correct one in hints and assign to (*s).sick_struct
    // result  is a linkedlist of addrinfo check for correct one
    // assign to (*s)._client_struct
    getaddrinfo( NULL, port, &hints, &result );

    temp_server->_server_struct = result;

    return temp_server;
}

void       handy_destroy_client ( handy_client * c )
{}
void       handy_destroy_server ( handy_server * s )
{}

bool   handy_connect_client     ( handy_client * c, char * adrr, int port )
{
    // check make sure were are connected to a port, probably force it.
    // and that we got the fd

    (*c)->_connection_fd = socket( AF_INET, SOCK_STREAM, 0 );

    if( (*c)->_connection_fd < 0 )
    {
        (*c)->_error_message = strcat( ((*c)->_error_message), "Error!, Could not create socket for:" );
        (*c)->_error_message = strcat( ((*c)->_error_message), (*c)->name(c) );
        return false;
    }
    else
    {
        (*c)->_error_message = strcat( ((*c)->_error_message), "Created socket for:" );
        (*c)->_error_message = strcat( ((*c)->_error_message), (*c)->name(c) );
    }


    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons( port );
    server_addr.sin_addr.s_addr = "127.0.0.1";


    // if( connect((*c)->_connection_fd, (struct sockaddr *) &((*c)->_destination_struct), sizeof((*c)->_destination_struct)) );
    if( connect( (*c)->_connection_fd, (struct sockaddr *)&server_addr, sizeof(server_addr) ) == -1 )
    {
        (*c)->_error_message = strcat( ((*c)->_error_message), "Error!, Could not create connection to " );
        (*c)->_error_message = strcat( ((*c)->_error_message), (*c)->name(c) );

        return false;
    }

    (*c)->_error_message = strcat( ((*c)->_error_message), "\nCreated connection to:  " );
    (*c)->_error_message = strcat( ((*c)->_error_message), server_addr.sin_addr.s_addr );

    char cnn_r[1024];

    recv( (*c)->_connection_fd, &cnn_r, sizeof(cnn_r), 0 );
    printf( "Got message from sever: %s\n", cnn_r );
    close( (*c)->_connection_fd );
    return true;
    // we are surely connected
}
bool   handy_connect_server     ( handy_server * s )
{
    // check make sure were are connected to a port, probably force it.
    // and that we got the fd

    for( ; (*s)->_server_struct != NULL; (*s)->_server_struct->ai_next )
    {
        (*s)->_connection_fd = socket( (*s)->_server_struct->ai_family, (*s)->_server_struct->ai_socktype,
                                (*s)->_server_struct->ai_protocol );
        if( (*s)->_connection_fd  < 0 )
        {
            strcat( (*s)->_error_message, "Error!, Could not create socket at " );
            strcat( (*s)->_error_message, (*s)->name(s) );
            continue;
        }
        else
            break;
    }

    if( bind( (*s)->_connection_fd, (*s)->_server_struct->ai_addr, (*s)->_server_struct->ai_addrlen) < 0 )
    {
        strcat( (*s)->_error_message, "Error!, Could not bind socket at " );
        strcat( (*s)->_error_message, (*s)->name(s) );
        return false;
    }

    if( listen( (*s)->_connection_fd, MAX_CONNECTION ) < 0 )
    {
        strcat( (*s)->_error_message, "Error!, Could not listen socket at " );
        strcat( (*s)->_error_message, (*s)->name(s) );
        return false;
    }

    printf( "Waiting for connection...\n" );

    (*s)->_sick_fd = accept( (*s)->_connection_fd, &((*s)->_client_struct), sizeof ((*s)->_client_struct) );

    char * client_name = malloc( 1024 );
    inet_ntop( (*s)->_client_struct.ai_family, (*s)->_client_struct.ai_addr->sa_data, client_name, 1024 );

    if( (*s)->_sick_fd < 0 )
    {
        strcat( (*s)->_error_message, "Error!, Could not accept connection from " );
        strcat( (*s)->_error_message, client_name );
        return false;
    }

    printf( "\nSUCCESS!, Connection from %s", client_name );
    return true;
}

void   handy_disconnect_server  ( handy_server * s )
{
    close( (*s)->_sick_fd );
    close( (*s)->_connection_fd );
}
void   handy_disconnect_client  ( handy_client * c )
{
    close( (*c)->_connection_fd );
}
char * handy_server_name        ( handy_server * s )
{
    char * ip = malloc( 1024 );
    inet_ntop( (*s)->_server_struct->ai_family, (*s)->_server_struct->ai_addr->sa_data, ip, sizeof (*ip) );
    return ip;
}
char * handy_client_name        ( handy_client * c )
{
    char * ip = malloc( 1024 );
    // inet_ntop( (*c)->_destination_struct->ai_family, (*c)->_destination_struct->ai_addr->sa_data, ip, 1024 );
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
     recv( (*s)->_connection_fd,  &((*s)->_recv_message), MAX_READ, 0 );
}
int handy_send          ( handy_server * s, char * msg )
{
    printf( "server >> %s\n", msg );
    return  send( (*s)->_connection_fd, msg, sizeof(msg), 0 );
}
char * handy_error_msg  ( handy_server * s )
{
    return (char *) (*s)->error_msg;
}
