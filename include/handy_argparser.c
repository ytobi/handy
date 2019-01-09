// TODO: Document code

#include "handy_argparser.h"


int handy_argparser_get_arg_name_indx( handy_argparser self, char * name )
{
    for( int i = 1; i < self->__argc; i++ )
    {
        if( strcmp(self->__argv[i], name) == 0 )
            return i;
    }
    printf( "\nError, could not parse argument: {%s}", name );
    exit( 0 );
}

void handy_argparser_add_argument   ( handy_argparser self, handy_argparser_arg arg )
{
    int idx = handy_argparser_get_arg_name_indx( self, arg->__name );

    for( int i = idx + 1; i < self->__argc; i++ )
    {
        if( arg->__type == handy_argparser_single_arg )
        {
            memcpy( arg->__value, self->__argv[i], sizeof(self->__argv[i]) );
            break;
        }
        else if( arg->__type == handy_argparser_multiple_arg )
        {
            while( i < self->__argc && self->__argv[i][0] != '-' )
            {
                ( (handy_list)arg->__value )->add_back( arg->__value, self->__argv[i] );
                i++;
            }
            break;
        }
    }

    self->arg_list->add_back( self->arg_list, arg );

    return;
}
void * handy_argparser_get_argument ( handy_argparser self, char * name )
{
    handy_argparser_arg iter;

    for( int i = 0; i < self->arg_list->length(self->arg_list); i++ )
    {
        iter = self->arg_list->get_at( self->arg_list , i );
        // found the arg with name
        if( strcmp(iter->__name, name) == 0 )
        {
            return iter->__value;
        }
    }
    return NULL;
}
void handy_argparser_print_help     ( handy_argparser self )
{
    // print the argparser and display all argument
    // in nice format.
    handy_argparser_arg iter;

    printf( "\n%s ", __FILE__ );
    for( int i = 0; i < self->arg_list->length(self->arg_list); i++ )
    {
        iter = self->arg_list->get_at( self->arg_list, i );
        printf( "%s ", iter->__name );
    }
    printf( "\n\t%s ", self->__help );

    for( int i = 0; i < self->arg_list->length(self->arg_list); i++ )
    {
        iter = self->arg_list->get_at( self->arg_list, i );

        printf( "\n\t\t%s, %s", iter->__name, iter->__description );
    }

    return;
}
void handy_argparser_free           ( handy_argparser self )
{
    handy_argparser_arg iter;
    for (int i = 0; i < self->arg_list->length(self->arg_list) ; ++i)
    {
        iter = self->arg_list->get_at( self->arg_list, i );

        free(iter);
    }

    self->arg_list->free( self->arg_list );
    self->arg_list = ( free(self->arg_list), NULL );

    return;
}

handy_argparser handy_create_argparser(  char * description, int argc, char ** argv )
{
    handy_argparser temp = malloc(sizeof(* temp));

    temp->__help = description;

    temp->__argc = argc;
    temp->__argv = argv;

    temp->arg_list = handy_create_list();

    temp->print_help = handy_argparser_print_help;
    temp->add_argument = handy_argparser_add_argument;
    temp->get_argument = handy_argparser_get_argument;
    temp->free = handy_argparser_free;


    return temp;
}

handy_argparser_arg handy_create_argparser_arg( char * name, char * des,
                                                enum handy_argparser_type type )
{
    handy_argparser_arg temp = malloc( sizeof(*temp) );

    temp->__name = name;
    temp->__description = des;
    temp->__type = type;

    // if we expect multiple values, then create a list
    // to hold values
    if( type == handy_argparser_multiple_arg )
        temp->__value = handy_create_list();
    else if( type == handy_argparser_single_arg )
    {
        temp->__value = malloc( sizeof(temp->__value) );
        memset( temp->__value, 0, sizeof(temp->__value) );
    }


    return temp;
}
