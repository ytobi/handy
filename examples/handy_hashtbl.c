#include <stdio.h>
// #include "src/handy.h"

#include "src/handy_stack.h"

int main()
{
    handy_stack mys = handy_create_stack();

    mys->push( &mys, "hello", sizeof( "hello"  ) );
    mys->push( &mys, "world", sizeof( "world"  ) );

    printf("- %s -\n", mys->contain( &mys, "world", NULL ) );

    return 0;
}
