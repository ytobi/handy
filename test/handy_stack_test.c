#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"


void TestStackCreate    ( CuTest * tc )
{
    handy_stack stack = handy_create_stack();
    CuAssertPtrNotNull( tc, stack );

    // check if return of function to create stack
    // actually created
    int actualSize = stack->size;
    int expectedSize = 0;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    stack->free( &stack );
    free( stack );
}
void TestStackContain   ( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    for( int i = 0; i < 10; i++ )
        stack->push( &stack, i );

    CuAssertTrue( tc, stack->contain(&stack, 5) );

    CuAssertTrue( tc, !stack->contain(&stack, 10) );

    stack->free( &stack );
    free( stack );
}
void TestStackPush      ( CuTest * tc )
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
void TestStackEmpty     ( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    //  1 = true, empty is true
    CuAssertIntEquals( tc, 1, stack->empty( &stack ) );

    // after adding items, stack to be not empty
    for( int i = 0; i < 10; i++ )
        stack->push( &stack, i );

    // 0 = false
    CuAssertIntEquals( tc, 0, stack->empty( &stack ) );

    stack->free( &stack );
    free( stack );
}
void TestStackReverse   ( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    for( int i = 0; i < 10; i++ )
        stack->push( &stack , i );

    // assume that top does not fail
    CuAssertIntEquals( tc, 9, (int)stack->top(&stack) );

    // after reversing, the top should now have change.
    stack->reverse( &stack );
    CuAssertIntEquals( tc, 0, (int)stack->top(&stack) );

    stack->free(&stack);
    free( stack );
}
void TestStackPop       ( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    for( int i = 0; i < 10; i++ )
        stack->push( &stack, i );

    // pop all item in stack and compare to expected
    for( int i = 10; i > 0; i-- )
    CuAssertIntEquals( tc, i - 1, (int)stack->pop(&stack) );

    stack->free( &stack );
    free( stack );
}
void TestStackFree      ( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    for( int i = 1; i <= 10; i++ )
        stack->push( &stack, i );

    // before free, stack top and bottom are not null
    CuAssertPtrNotNull( tc, stack->top(&stack) );
    CuAssertPtrNotNull( tc, stack->bottom(&stack) );

    // before free, stack top and bottom are null, safely
    // assume all positions are now null
    stack->free( &stack );
    CuAssertPtrEquals( tc, NULL, stack->top(&stack) );
    CuAssertPtrEquals( tc, NULL, stack->bottom(&stack) );

    free( stack );
}
void TestStackTop       ( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    for( int i = 0; i < 10; i++ )
        stack->push( &stack, i );

    CuAssertIntEquals( tc, 9, stack->top(&stack) );

    // assume pop passed test, the now top to should 8
    stack->pop( &stack );
    CuAssertIntEquals( tc, 8, stack->top(&stack) );


    stack->free( &stack );
    free( stack );
}
void TestStackBottom    ( CuTest * tc )
{
    handy_stack stack = handy_create_stack();

    for( int i = 0; i < 10; i++ )
        stack->push( &stack, i );

    CuAssertIntEquals( tc, 0, stack->bottom(&stack) );

    stack->free(&stack);
    free( stack );
}


CuSuite * HandyStackGetSuit()
{
    CuSuite * suite = CuSuiteNew();

    SUITE_ADD_TEST( suite, TestStackCreate );
    SUITE_ADD_TEST( suite, TestStackContain );
    SUITE_ADD_TEST( suite, TestStackPush );
    // SUITE_ADD_TEST( suite, TestStackEmpty );
    // SUITE_ADD_TEST( suite, TestStackReverse );
    // SUITE_ADD_TEST( suite, TestStackPop );
    // SUITE_ADD_TEST( suite, TestStackFree );
    // SUITE_ADD_TEST( suite, TestStackTop );
    // SUITE_ADD_TEST( suite, TestStackBottom );

    return suite;
}