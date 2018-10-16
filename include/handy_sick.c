#include "handy_sick.h"

void   handy_destroy_client( handy_client * c );
void   handy_destroy_server( handy_server * s );

bool   handy_connect_client( handy_client * h );
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

handy_client handy_create_client ( char * destination, char * port )
{
    handy_client temp_client = malloc( sizeof(*temp_client) );

    temp_client->connect = handy_connect_client;
    temp_client->send    = handy_send;
    temp_client->recv    = handy_recv;
    temp_client->disconnect = handy_disconnect_client;
    temp_client->name   = handy_client_name;

    temp_client->error_message = malloc(1024);

    struct addrinfo hints, *result;

    memset( &hints, 0, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo( destination, port, &hints, &result );

    // find the correct one in hints and assign to (*s).sick_struct
    // result  is a linkedlist of addrinfo check for correct one
    // assign to (*c).client_struct
    (temp_client)->destination_struct = result;

    return temp_client;

}
handy_server handy_create_server ( char * host, char * port )
{
    handy_server temp_server = malloc( sizeof(*temp_server) );

    temp_server->connect = handy_connect_server;
    temp_server->send    = handy_send;
    temp_server->recv    = handy_recv;
    temp_server->disconnect = handy_disconnect_server;
    temp_server->name   = handy_server_name;

    temp_server->error_message = malloc(1024);
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

    for( ; (*c)->destination_struct != NULL; (*c)->destination_struct->ai_next )
    {
        (*c)->connection_fd = socket( (*c)->destination_struct->ai_family, (*c)->destination_struct->ai_socktype,
                                (*c)->destination_struct->ai_protocol );
        if( (*c)->connection_fd < 0 )
        {
            (*c)->error_message = strcat( ((*c)->error_message), "Error!, Could not create sockect for" );
            (*c)->error_message = strcat( ((*c)->error_message), (*c)->name(c) );
            continue;
        }
        else
            break;
    }
    struct sockaddr_in sin;
    socklen_t  len = sizeof(sin);

    getsockname( (*c)->connection_fd, (struct sockaddr *)&sin, &len);
    printf("port number %d\n", ntohs(sin.sin_port));

    sin;
    len = sizeof(sin);

    getsockname((*c)->destination_struct->ai_addr, (struct sockaddr *)&sin, &len);
    printf("port number %d\n", ntohs(sin.sin_port));
    // connect
    // this is for client to connect, servers will listen and accept

    // if( connect((*c)->connection_fd, (struct sockaddr *) &((*c)->destination_struct), sizeof((*c)->destination_struct)) );
    if( connect( (*c)->connection_fd, (*c)->destination_struct->ai_addr, (*c)->destination_struct->ai_addrlen ) )
    {
        (*c)->error_message = strcat( ((*c)->error_message), "Error!, Could not create connection to " );
        (*c)->error_message = strcat( ((*c)->error_message), (*c)->name(c) );

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
        (*s)->connection_fd = socket( (*s)->server_struct->ai_family, (*s)->server_struct->ai_socktype,
                                (*s)->server_struct->ai_protocol );
        if( (*s)->connection_fd  < 0 )
        {
            strcat( (*s)->error_message, "Error!, Could not create socket at " );
            strcat( (*s)->error_message, (*s)->name(s) );
            continue;
        }
        else
            break;
    }

    if( bind( (*s)->connection_fd, (*s)->server_struct->ai_addr, (*s)->server_struct->ai_addrlen) < 0 )
    {
        strcat( (*s)->error_message, "Error!, Could not bind socket at " );
        strcat( (*s)->error_message, (*s)->name(s) );
        return false;
    }

    if( listen( (*s)->connection_fd, MAX_CONNECTION ) < 0 )
    {
        strcat( (*s)->error_message, "Error!, Could not listen socket at " );
        strcat( (*s)->error_message, (*s)->name(s) );
        return false;
    }

    printf( "Waiting for connection...\n" );

    (*s)->sick_fd = accept( (*s)->connection_fd, &((*s)->client_struct), sizeof ((*s)->client_struct) );

    char * client_name = malloc( 1024 );
    inet_ntop( (*s)->client_struct.ai_family, (*s)->client_struct.ai_addr->sa_data, client_name, 1024 );

    if( (*s)->sick_fd < 0 )
    {
        strcat( (*s)->error_message, "Error!, Could not accept connection from " );
        strcat( (*s)->error_message, client_name );
        return false;
    }

    printf( "\nSUCCESS!, Connection from %s", client_name );
    return true;
}

void   handy_disconnect_server ( handy_server * s )
{
    close( (*s)->sick_fd );
    close( (*s)->connection_fd );
}
void   handy_disconnect_client ( handy_client * c )
{
    close( (*c)->connection_fd );
}
char * handy_server_name       ( handy_server * s )
{
    char * ip = malloc( 1024 );
    inet_ntop( (*s)->server_struct->ai_family, (*s)->server_struct->ai_addr->sa_data, ip, sizeof (*ip) );
    return ip;
}
char * handy_client_name       ( handy_client * c )
{
    char * ip = malloc( 1024 );
    inet_ntop( (*c)->destination_struct->ai_family, (*c)->destination_struct->ai_addr->sa_data, ip, 1024 );
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
     recv( (*s)->connection_fd,  &((*s)->recv_message), MAX_READ, 0 );
}
int handy_send          ( handy_server * s, char * msg )
{
    printf( "server >> %s\n", msg );
    return  send( (*s)->connection_fd, msg, sizeof(msg), 0 );
}
char * handy_error_msg  ( handy_server * s )
{
    return (char *) (*s)->error_msg;
}