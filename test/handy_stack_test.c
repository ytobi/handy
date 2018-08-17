#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"


void TestStackCreate( CuTest * tc )
{
    handy_stack stack = handy_create_stack();
    CuAssertPtrNotNull( tc, stack );

    // check if return of function to create stack
    // actually created
    int actualSize = stack->size;
    int expectedSize = 0;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    stack->free(&stack);
    free( stack );
}
void TestStackPush( CuTest * tc )
{
    handy_stack stack = handy_create_stack();
    char * input = strdup("hello, world!");

    // test response, if positive and hence item was added
    int actualResponse = stack->push(&stack, input);
    int expectedResponse = 1;
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    int actualSize = stack->size;
    int expectedSize = 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    // we test getting item at top
    char * actualGetString = stack->top(&stack);
    char * expectedGetString = "hello, world!";
    CuAssertStrEquals( tc, expectedGetString, actualGetString );

    // test removing item at top
    char * actualRemoveString = stack->pop(&stack);
    char * expectedRemoveString = "hello, world!";
    CuAssertStrEquals( tc, expectedRemoveString, actualRemoveString );

    stack->free(&stack);
    free( stack );
}
void TestStackContain( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    for( int i = 0; i < 10; i++ )
        stack->push( &stack, i );

    CuAssertTrue( tc, stack->contain(&stack, 5) );

    CuAssertTrue( tc, !stack->contain(&stack, 10) );

    stack->free( &stack );
    free( stack );
}
void TestStackPop( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    for( int i = 0; i < 10; i++ )
        stack->push( &stack, i );

    int actualBack = stack->pop( &stack );
    int expectedBack = 9;
    CuAssertIntEquals( tc, expectedBack, actualBack );

    int actualFront = stack->pop( &stack );
    int expectedFront = 8;
    CuAssertIntEquals( tc, expectedFront, actualFront );

    int actualSize = stack->size;
    int expectedSize = 8;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    stack->free( &stack );
    free( stack );
}
void TestStackReverse( CuTest * tc )
{
    handy_stack stack = handy_create_stack();
    CuAssertPtrNotNull( tc, stack );

    stack->push( &stack, "Handy" ); // bottom
    stack->push( &stack, "is" );
    stack->push( &stack, "name" );
    stack->push( &stack, "my" );
    stack->push( &stack, "world," );
    stack->push( &stack, "Hello" ); // top

    // now stack has been reversed
    stack->reverse( &stack );

    char * actualStr = "Hello";
    char * expectedStr = stack->bottom( &stack );
    CuAssertStrEquals( tc, expectedStr, actualStr );

    actualStr = "Handy";
    expectedStr = stack->top( &stack );
    CuAssertStrEquals( tc, expectedStr, actualStr );

    actualStr = "Hello";
    expectedStr = stack->pop( &stack );
    CuAssertStrEquals( tc, expectedStr, actualStr );



    stack->free(&stack);
    free( stack );
}

CuSuite * HandyStackGetSuit()
{
    CuSuite * suite = CuSuiteNew();

    SUITE_ADD_TEST( suite, TestStackCreate );
    SUITE_ADD_TEST( suite, TestStackPush );
    SUITE_ADD_TEST( suite, TestStackContain );
    SUITE_ADD_TEST( suite, TestStackPop );
    SUITE_ADD_TEST( suite, TestStackReverse );

    return suite;
}

