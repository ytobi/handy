#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"


void TestListCreate( CuTest * tc )
{
	handy_list list = handy_create_list();
	CuAssertPtrNotNull( tc, list );

	// check if return of function to create list
	// actually created
	int actualSize = list->size;
	int expectedSize = 0;
	CuAssertIntEquals( tc, expectedSize, actualSize );

	list->free(&list);
	free( list );
}
void TestListAdd( CuTest * tc )
{
	handy_list list = handy_create_list();
	char * input = strdup("hello, world!");

    // test response, if positive and hence item was added
	int actualResponse = list->add_front(&list, input);
	int expectedResponse = 1;
	CuAssertIntEquals( tc, expectedResponse, actualResponse );

	// We test the size if a change in size
	int actualSize = list->size;
	int expectedSize = 1;
	CuAssertIntEquals( tc, expectedSize, actualSize );

	// we test getting item at front
	char * actualGetString = list->get_front(&list);
	char * expectedGetString = "hello, world!";
	CuAssertStrEquals( tc, expectedGetString, actualGetString );

	// test removing item at front
	char * actualRemoveString = list->get_front(&list);
	char * expectedRemoveString = "hello, world!";
	CuAssertStrEquals( tc, expectedRemoveString, actualRemoveString );

	list->free(&list);
	free( list );
}
void TestListContain( CuTest * tc )
{
    handy_list list = handy_create_list();

    for( int i = 0; i < 10; i++ )
        list->add_front( &list, i );

    CuAssertTrue( tc, list->contain(&list, 5) );

    list->free( &list );
    free( list );
}
void TestListRemove( CuTest * tc )
{
    handy_list list = handy_create_list();

    for( int i = 0; i < 10; i++ )
        list->add_back( &list, i );

    int actualAt = list->remove_at( &list, 2 );
    int expectedAt = 2;
    CuAssertIntEquals( tc, expectedAt, actualAt );

    int actualBack = list->remove_back( &list );
    int expectedBack = 9;
    CuAssertIntEquals( tc, expectedBack, actualBack );

    int actualFront = list->remove_front( &list );
    int expectedFront = 0;
    CuAssertIntEquals( tc, expectedFront, actualFront );

    int actualSize = list->size;
    int expectedSize = 7;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    actualAt = list->remove_at( &list, 0 );
    expectedAt = 1;
    CuAssertIntEquals( tc, expectedAt, actualAt );

    actualAt = list->remove_at( &list, list->size - 1 );
    expectedAt = 8;
    CuAssertIntEquals( tc, expectedAt, actualAt );

    list->free( &list );
    free( list );
}
void TestListReverse( CuTest * tc )
{}

CuSuite * HandyListGetSuit()
{
	CuSuite * suite = CuSuiteNew();
	SUITE_ADD_TEST( suite, TestListAdd );
	SUITE_ADD_TEST( suite, TestListCreate );
    SUITE_ADD_TEST( suite, TestListContain );
    SUITE_ADD_TEST( suite, TestListRemove );
    SUITE_ADD_TEST( suite, TestListReverse );

	return suite;
}

