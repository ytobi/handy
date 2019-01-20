// TODO: Document code

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "handy_list.h"

#ifndef HANDY_HANDY_ARGPARSER_H
#define HANDY_HANDY_ARGPARSER_H

enum handy_argparser_type
{
    handy_argparser_single_arg,
    handy_argparser_multiple_arg
};

typedef struct _handy_argparser_struct * handy_argparser;

#ifndef HANDY_HANDY_ARGPARSER_ARGUMENT_OBJ_H
#define HANDY_HANDY_ARGPARSER_ARGUMENT_OBJ_H

typedef struct _handy_argparser_arg_obj * handy_argparser_arg;

struct _handy_argparser_arg_obj
{
    void *  (*get_value) ( handy_argparser_arg self );

    char * __name;
    char * __description;
    void * __value;
    enum handy_argparser_type __type;
};

#endif //HANDY_HANDY_ARGPARSER_ARGUMENT_OBJ_H

struct _handy_argparser_struct
{
    void    (*add_argument) ( handy_argparser self, handy_argparser_arg arg );
    void    (*print_help)   ( handy_argparser self );
    void    (*free)         ( handy_argparser self );
    handy_list arg_list;
    char * __help;
    int __argc;
    char ** __argv;
};


handy_argparser handy_create_argparser          ( char * description, int argc, char ** argv );
handy_argparser_arg handy_create_argparser_arg  ( char * name, char * help,
                                                  enum handy_argparser_type );

#endif //HANDY_HANDY_ARGPARSER_H