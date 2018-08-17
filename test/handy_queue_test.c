#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"


void TestQueueCreate( CuTest * tc )
{
    handy_queue queue = handy_create_queue();
    CuAssertPtrNotNull( tc, queue );

    // check if return of function to create queue
    // actually created
    int actualSize = queue->size;
    int expectedSize = 0;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    queue->free(&queue);
    free( queue );
}
void TestQueueEnqueue( CuTest * tc )
{
    handy_queue queue = handy_create_queue();
    char * input = strdup("hello, world!");

    // test response, if positive and hence item was added
    int actualResponse = queue->enqueue(&queue, input);
    int expectedResponse = 1;
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    int actualSize = queue->size;
    int expectedSize = 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    // we test getting item at back
    char * actualGetString = (char *)queue->front(&queue);
    char * expectedGetString = "hello, world!";
    CuAssertStrEquals( tc, expectedGetString, actualGetString );

    // test removing item at back
    char * actualRemoveString = (char *)queue->dequeue(&queue);
    char * expectedRemoveString = "hello, world!";
    CuAssertStrEquals( tc, expectedRemoveString, actualRemoveString );

    queue->free(&queue);
    free( queue );
}
void TestQueueContain( CuTest * tc )
{
    handy_queue queue = handy_create_queue();

    for( int i = 0; i < 10; i++ )
        queue->enqueue( &queue, i );

    CuAssertTrue( tc, queue->contain(&queue, 5) );

    queue->free( &queue );
    free( queue );
}
void TestQueueDequeue( CuTest * tc )
{
    handy_queue queue = handy_create_queue();

    for( int i = 0; i < 10; i++ )
        queue->enqueue( &queue, i );

    int actualBack = (int)queue->front( &queue );
    int expectedBack = 0;
    CuAssertIntEquals( tc, expectedBack, actualBack );

    int actualFront = (int)queue->dequeue( &queue );
    int expectedFront = 0;
    CuAssertIntEquals( tc, expectedFront, actualFront );

    int actualSize = queue->size;
    int expectedSize = 9;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    queue->free( &queue );
    free( queue );
}
void TestQueueReverse( CuTest * tc )
{
    handy_queue queue = handy_create_queue();
    CuAssertPtrNotNull( tc, queue );

    queue->enqueue( &queue, "Handy" ); // front
    queue->enqueue( &queue, "is" );
    queue->enqueue( &queue, "name" );
    queue->enqueue( &queue, "my" );
    queue->enqueue( &queue, "world," );
    queue->enqueue( &queue, "Hello" ); // back

    // Now the queue has been reversed
    queue->reverse( &queue );

    char * actualStr = "Hello";
    char * expectedStr = queue->dequeue( &queue );

    CuAssertStrEquals( tc, expectedStr, actualStr );

    actualStr = "Handy";
    expectedStr = queue->back( &queue );

    CuAssertStrEquals( tc, expectedStr, actualStr );

    queue->free(&queue);
    free( queue );
}

CuSuite * HandyQueueGetSuit()
{
    CuSuite * suite = CuSuiteNew();

    SUITE_ADD_TEST( suite, TestQueueEnqueue );
    SUITE_ADD_TEST( suite, TestQueueCreate );
    SUITE_ADD_TEST( suite, TestQueueContain );
    SUITE_ADD_TEST( suite, TestQueueDequeue );
    SUITE_ADD_TEST( suite, TestQueueReverse );

    return suite;
}

