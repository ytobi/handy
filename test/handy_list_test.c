#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"

void TestListCreate     ( CuTest * tc )
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
void TestListAddFront   ( CuTest * tc )
{
    handy_list list = handy_create_list();

    char * input1 = "hello, world!";
    char input2 = 'A';
    int input3 = 10;


    // Input1
    // test response, if positive and hence item was added
    int actualResponse = list->add_front(&list, input1);
    int expectedResponse = 1; // true
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    int actualSize = list->size;
    int expectedSize = 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );



    // Input2
    // test response, if positive and hence item was added
    actualResponse = list->add_front(&list, input2);
    expectedResponse = 1; // true
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    actualSize = list->size;
    expectedSize++;
    CuAssertIntEquals( tc, expectedSize, actualSize );



    // Input3
    // test response, if positive and hence item was added
    actualResponse = list->add_front(&list, input3);
    expectedResponse = 1; // true
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    actualSize = list->size;
    expectedSize++;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    list->free(&list);
    free( list );
}
void TestListAddBack    ( CuTest * tc )
{
    handy_list list = handy_create_list();

    for( int i = 0; i < 10; i++ )
    {
        CuAssertTrue( tc, list->add_back( &list, i ) );
        CuAssertIntEquals( tc, i+1, list->size );
    }

    list->free( &list );
    free( list );
}
void TestListAddAt      ( CuTest * tc )
{
    handy_list list = handy_create_list();
    char * input1 = "hello, world!";
    char input2 = 'A';
    int input3 = 10;


    // Input1
    // test response, if 1 and hence item was added
    int actualResponse = list->add_at( &list, input1, 0 );
    int expectedResponse = 1;
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    int actualSize = list->size;
    int expectedSize = 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );



    // Input2
    // test response, if positive and hence item was added
    actualResponse = list->add_at(&list, input2, 1);
    expectedResponse = 1;
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    actualSize = list->size;
    expectedSize++;
    CuAssertIntEquals( tc, expectedSize, actualSize );


    // Input3
    // test response, if positive and hence item was added
    // Addition to a location past the size of the list should not cause
    // error at all.
    actualResponse = list->add_at( &list, input3, 1 );
    expectedResponse = 1;
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    actualSize = list->size;
    expectedSize++;
    CuAssertIntEquals( tc, expectedSize, actualSize );


    list->free(&list);
    free( list );
}
void TestListContain    ( CuTest * tc )
{
    handy_list list = handy_create_list();

    for( int i = 0; i < 10; i++ )
        list->add_front( &list, i );

    // contain return location of item in list if found or -1 if not found
    // check if it contain all items added
    for( int i = 0; i < 10; i++ )
        CuAssertTrue( tc, list->contain(&list, 1) > -1 );


    list->free( &list );
    free( list );
}
void TestListRemoveFront( CuTest * tc )
{
    handy_list list = handy_create_list();
    int size_list = 10;

    for( int i = 0; i < size_list; i++ )
        list->add_back( &list, i );

    CuAssertTrue( tc, list->rem_back( &list ) );

    int actualSize = list->size;
    int expectedSize = size_list - 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );


    list->free( &list );
    free( list );
}
void TestListRemoveBack ( CuTest * tc )
{
    handy_list list = handy_create_list();
    int size_list = 10;

    for( int i = 0; i < size_list; i++ )
        list->add_back( &list, i );

    CuAssertTrue( tc, list->rem_back( &list ) );

    int actualSize = list->size;
    int expectedSize = size_list - 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );


    list->free( &list );
    free( list );
}
void TestListRemoveAt   ( CuTest * tc )
{
    handy_list list = handy_create_list();
    int size_list = 10;

    for( int i = 0; i < size_list; i++ )
        list->add_back( &list, i );

    CuAssertTrue( tc, list->rem_at( &list, 2 ) );

    int actualSize = list->size;
    int expectedSize = size_list - 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    list->free( &list );
    free( list );
}
void TestListEmpty      ( CuTest * tc )
{
    handy_list list = handy_create_list();

    // should originally be empty(true)
    CuAssertTrue( tc, list->empty(&list) );

    list->add_front( &list, 1 );

    // should not(false) be empty
    CuAssertTrue( tc, !(list->empty(&list)) );


    list->free( &list );
    free( list );
}
void TestListReverse    ( CuTest * tc )
{
    handy_list list = handy_create_list();
    CuAssertPtrNotNull( tc, list );

    list->add_back( &list, "Handy" ); // first
    list->add_back( &list, "is" );
    list->add_back( &list, "name" );
    list->add_back( &list, "my" );
    list->add_back( &list, "world," );
    list->add_back( &list, "Hello" ); // last

    // now list has been reversed
    list->reverse( &list );

    char * actualStr = "Hello";
    char * expectedStr = list->get_front( &list );

    CuAssertStrEquals( tc, expectedStr, actualStr );

    actualStr = "Handy";
    expectedStr = list->get_back( &list );

    CuAssertStrEquals( tc, expectedStr, actualStr );

    list->free(&list);
    free( list );
}
void TestListGetFront   ( CuTest * tc )
{
    handy_list list = handy_create_list();
    int size_list = 10;

    for( int i = 0; i < size_list; i++ )
        list->add_back( &list, i );

    int actualAt = (int)list->get_front( &list );
    int expectedAt = 0;
    CuAssertIntEquals( tc, expectedAt, actualAt );

    // size does not change
    int actualSize = list->size;
    int expectedSize = size_list;
    CuAssertIntEquals( tc, expectedSize, actualSize );


    list->free( &list );
    free( list );

}
void TestListGetBack    ( CuTest * tc )
{
    handy_list list = handy_create_list();
    int size_list = 10;

    for( int i = 0; i < size_list; i++ )
        list->add_back( &list, i );

    int actualAt = (int)list->get_back( &list );
    int expectedAt = 9;
    CuAssertIntEquals( tc, expectedAt, actualAt );

    // size does not change
    int actualSize = list->size;
    int expectedSize = size_list;
    CuAssertIntEquals( tc, expectedSize, actualSize );


    list->free( &list );
    free( list );
}
void TestListGetAt      ( CuTest * tc )
{
    handy_list list = handy_create_list();
    int size_list = 10;

    for( int i = 0; i < size_list; i++ )
        list->add_back( &list, i );

    int actualAt = (int)list->get_at( &list, 5 );
    int expectedAt = 5;
    CuAssertIntEquals( tc, expectedAt, actualAt );

    // size does not change
    int actualSize = list->size;
    int expectedSize = size_list;
    CuAssertIntEquals( tc, expectedSize, actualSize );


    list->free( &list );
    free( list );
}
void TestListFree       ( CuTest * tc )
{
    handy_list list = handy_create_list();
    int size_list = 10;

    for( int i = 0; i < size_list; i++ )
        list->add_back( &list, i );

    list->free( &list );

    // everything should now be null

    CuAssertPtrEquals( tc, NULL, list->get_front(&list) );
    CuAssertPtrEquals( tc, NULL, list->get_back(&list) );

    CuAssertIntEquals( tc, 0, list->size );

    free( list );
}

CuSuite * HandyListGetSuit()
{

	CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST( suite, TestListCreate );
	SUITE_ADD_TEST( suite, TestListAddFront );
    SUITE_ADD_TEST( suite, TestListAddBack );
    SUITE_ADD_TEST( suite, TestListAddAt );
    SUITE_ADD_TEST( suite, TestListContain );
    SUITE_ADD_TEST( suite, TestListRemoveFront );
    SUITE_ADD_TEST( suite, TestListRemoveBack );
    SUITE_ADD_TEST( suite, TestListRemoveAt );
    SUITE_ADD_TEST( suite, TestListEmpty );
    SUITE_ADD_TEST( suite, TestListReverse );
    SUITE_ADD_TEST( suite, TestListGetFront );
    SUITE_ADD_TEST( suite, TestListGetBack );
    SUITE_ADD_TEST( suite, TestListGetAt );
    SUITE_ADD_TEST( suite, TestListFree );

	return suite;
}
