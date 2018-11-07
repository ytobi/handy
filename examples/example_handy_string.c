#include "../include/handy_string.h"


int main()
{
    handy_string my_string;                                 // declare handy_string object

    my_string = handy_create_string();                      // initialise my_string object


    my_string->append( my_string, "Hello, World!" );       // append new string to my_string

    int lent = my_string->length( my_string );             // we can find the length of the string in my_string


    bool cont = my_string->contain_str( my_string, "Hello" ); // we can check if a sub-string is in my_string


    int w_count = my_string->word_count( my_string, ' ' ); // count the number of words in the string at the delimiter ' '

    my_string->to_upper( my_string );                      // change my_string to all UPPERCASE

    char * content = my_string->string( my_string );       //  get the actual string in my_string


    char H = my_string->get_front_char( my_string );       // get only the front char in my_string but do not remove


    my_string->free( my_string );                          // free all memory allocated by my_string

    free( my_string );                                      // final cleanup, free my_string object


    return 0;
}