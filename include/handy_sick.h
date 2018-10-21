#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <errno.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


#ifndef HANDY_HANDY_SICK_H
#define HANDY_HANDY_SICK_H

static int MAX_CONNECTION = 10;
static int MAX_READ       = 1024;

typedef struct _handy_client_struct * handy_client;
typedef struct _handy_server_struct * handy_server;

struct _handy_client_struct
{
    bool    (*connect)  ( handy_client * c );
    void    (*disconnect)( handy_client * c );
    char *  (*name)     ( handy_client * c );
    char *  (*ip)       ( handy_client * c );
    char *  (*port)     ( handy_client * c );
    char *  (*family)   ( handy_client * c );
    char *  (*type)     ( handy_client * c );
    char *  (*recv)     ( handy_server * c );
    int     (*send)     ( handy_server * c,  char * msg );
    char *  (*error_msg)( handy_client * c );

    char * _error_message;
    char * _recv_message;

    struct addrinfo * _destination_struct;

    int _connection_fd;
};

struct _handy_server_struct
{
    bool    (*connect)  ( handy_server * s );
    void    (*disconnect)( handy_server * s );
    char *  (*name)     ( handy_server * s );
    char *  (*ip)       ( handy_server * s );
    char *  (*port)     ( handy_server * s );
    char *  (*family)   ( handy_server * s );
    char *  (*type)     ( handy_server * s );
    char *  (*recv)     ( handy_server * s );
    int     (*send)     ( handy_server * s,  char * msg );
    char *  (*error_msg)( handy_server * s );

    char * _error_message;
    char * _recv_message;

    // a linked list of addrinfo
    struct addrinfo * _server_struct;
    struct addrinfo _client_struct;

    int _sick_fd;
    int _connection_fd;
};

handy_client handy_create_client ( char * destination, char * port );
handy_server handy_create_server ( char * host, char * port );


#endif //HANDY_HANDY_SICK_H