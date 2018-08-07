#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"


void TestCreateList( CuTest * tc )
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
void TestAddFront( CuTest * tc )
{
	handy_list list = handy_create_list();
	char * input = strdup("hello, world!");

	// We test the response if truly item was added
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

CuSuite * HandyListGetSuit()
{
	CuSuite * suite = CuSuiteNew();
	SUITE_ADD_TEST( suite, TestAddFront );
	SUITE_ADD_TEST( suite, TestCreateList );
	return suite;
}

