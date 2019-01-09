//
// Created by tobi on 1/8/19.
//


#include "../include/handy_argparser.h"

int main( int argc, char ** argv )
{
    handy_argparser parser = handy_create_argparser( "An example argument parser", argc, argv );

    handy_argparser_arg args1 = handy_create_argparser_arg( "--f", "Example name of file to read", handy_argparser_single_arg );
    handy_argparser_arg args2 = handy_create_argparser_arg( "--candy", "Example candy values", handy_argparser_multiple_arg );

    parser->add_argument( parser, args1 );
    parser->add_argument( parser, args2 );

    parser->print_help( parser );

    handy_list candies = parser->get_argument( parser, "--candy" );
    char * f    = parser->get_argument( parser, "--f" );

    parser->free( parser );
    parser = ( free(parser), NULL );

    return 0;
}