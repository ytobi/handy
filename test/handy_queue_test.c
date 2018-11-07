#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"


void TestQueueCreate    ( CuTest * tc )
{
    handy_queue queue;

    // after initialization, queue should now not be equal to zero
    queue = handy_create_queue();
    CuAssertPtrNotNull( tc, queue );

    // validate the size for queue is 0
    CuAssertIntEquals( tc, 0, queue->length(queue) );

    queue->free( queue );
    free( queue );
}
void TestQueueContain   ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();

    for( int i = 0; i < 10; i++ )
        queue->enqueue( queue, i );

    // test queue contains all enqueued elements
    for( int i = 0; i < 10; i++ )
        CuAssertTrue( tc, queue->contain(queue, i) != -1 );

    queue->free( queue );
    free( queue );
}
void TestQueueEnqueue   ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();
    char * input = "hello, world!";

    // test response, if positive and hence item was added
    int actualResponse = queue->enqueue(queue, input);
    int expectedResponse = 1;
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    int actualSize = queue->length( queue );
    int expectedSize = 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    queue->free(queue);
    free( queue );
}
void TestQueueEmpty     ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();

    // should be empty
    CuAssertTrue( tc, queue->empty(queue) );

    // add things and test not true
    char * input = "hello, world!";
    queue->enqueue(queue, input);
    CuAssertTrue( tc, !queue->empty(queue) );

    queue->free(queue);
    free( queue );
}
void TestQueueReverse   ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();
    CuAssertPtrNotNull( tc, queue );

    for( int i = 0 ; i < 10; i++ )
        queue->enqueue( queue, i );

    CuAssertIntEquals( tc, 0, queue->dequeue(queue) );

    // Now the queue has been reversed
    queue->reverse( queue );
    CuAssertIntEquals( tc, 9, queue->dequeue(queue) );

    queue->free(queue);
    free( queue );
}
void TestQueueDequeue   ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();

    for( int i = 0; i < 10; i++ )
        queue->enqueue( queue, i );

    int actualBack = (int)queue->front( queue );
    int expectedBack = 0;
    CuAssertIntEquals( tc, expectedBack, actualBack );

    int actualFront = (int)queue->dequeue( queue );
    int expectedFront = 0;
    CuAssertIntEquals( tc, expectedFront, actualFront );

    int actualSize = queue->length( queue );
    int expectedSize = 9;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    queue->free( queue );
    free( queue );
}
void TestQueueFree      ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();
    CuAssertPtrNotNull( tc, queue );

    for( int i = 1; i <= 10; i++ )
       queue->enqueue( queue, i );

    // queue contains items, and hence not null
    CuAssertPtrNotNull( tc, queue->front(queue) );
    CuAssertPtrNotNull( tc, queue->back(queue) );

    queue->free(queue);

    // everything should now be null
    CuAssertPtrEquals( tc, NULL, queue->front(queue) );
    CuAssertPtrEquals( tc, NULL, queue->back(queue) );

    free( queue );
}
void TestQueueFront     ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();
    CuAssertPtrNotNull( tc, queue );

    for( int i = 0; i < 10; i++ )
        queue->enqueue( queue, i );

    CuAssertIntEquals( tc, 0, queue->front(queue) );

    queue->free(queue);
    free( queue );
}
void TestQueueBack      ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();
    CuAssertPtrNotNull( tc, queue );

    for( int i = 0; i < 10; i++ )
        queue->enqueue( queue, i );

    CuAssertIntEquals( tc, 9, queue->back(queue) );

    queue->free(queue);
    free( queue );
}
void TestQueueLength    ( CuTest * tc )
{
    handy_queue queue = handy_create_queue();

    CuAssertIntEquals( tc, 0, queue->length(queue) );

    for( int i = 0; i < 10; i++ )
        queue->enqueue( queue, i );

    CuAssertIntEquals( tc, 10, queue->length(queue) );

    queue->free(queue);

    CuAssertIntEquals( tc, 0, queue->length(queue) );

    free( queue );
}

CuSuite * HandyQueueGetSuit()
{
    CuSuite * suite = CuSuiteNew();

    SUITE_ADD_TEST( suite, TestQueueCreate );
    SUITE_ADD_TEST( suite, TestQueueContain );
    SUITE_ADD_TEST( suite, TestQueueEnqueue );
    SUITE_ADD_TEST( suite, TestQueueEmpty );
    SUITE_ADD_TEST( suite, TestQueueReverse );
    SUITE_ADD_TEST( suite, TestQueueDequeue );
    SUITE_ADD_TEST( suite, TestQueueFree );
    SUITE_ADD_TEST( suite, TestQueueFront );
    SUITE_ADD_TEST( suite, TestQueueBack );
    SUITE_ADD_TEST( suite, TestQueueLength );

    return suite;
}
