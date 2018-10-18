#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"

void TestHashtblAdd( CuTest * tc )
{
    handy_hashtbl table = handy_create_hashtbl();
    CuAssertPtrNotNull( tc, table );

    // check if return of function to create list
    // actually created

    int actualReturn = table->add( &table, "123", (void *)"Hello, world!" );
    int expectedReturn = 1; // true
    CuAssertIntEquals( tc, expectedReturn, actualReturn );

    table->free(&table);
    free( table );
}
void TestHashtblContain( CuTest * tc )
{
    handy_hashtbl table = handy_create_hashtbl();
    CuAssertPtrNotNull( tc, table );

    // check if return of function to create list
    // actually created

    table->add( &table, "123", (void *)"Hello,!" );
    CuAssertTrue( tc, table->contain(&table, "123") );

    table->add( &table, "124", (void *)" world!" );
    CuAssertTrue( tc, table->contain(&table, "124") );

    table->free(&table);
    free( table );
}
void TestHashtblGet( CuTest * tc )
{
    handy_hashtbl table = handy_create_hashtbl();
    CuAssertPtrNotNull( tc, table );

    // check if return of function to create list
    // actually created

    table->add( &table, "123", (void *)"Hello,!" );
    table->add( &table, "124", (void *)" world!" );

    char * actualReturn = (char *)table->get( &table, "124" );
    char * expectReturn = " world!";
    CuAssertStrEquals( tc, expectReturn, actualReturn );

    table->free(&table);
    free( table );
}
void TestHashtblRemove( CuTest * tc )
{
    handy_hashtbl table = handy_create_hashtbl();
    CuAssertPtrNotNull( tc, table );

    // check if return of function to create list
    // actually created

    // I actually don't know why it is insisting for me to cast!
    table->add( &table, "123", (void *)"Hello,!" );
    table->add( &table, "124", (void *)" world!" );

    char * actualReturn = (char *)table->get( &table, "124" );
    char * expectReturn = (char *)" world!";
    CuAssertStrEquals( tc, expectReturn, actualReturn );

    table->free(&table);
    free( table );
}

CuSuite * HandyListGetSuit()
{
    CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST( suite, TestHashtblAdd );
    SUITE_ADD_TEST( suite, TestHashtblContain );
    SUITE_ADD_TEST( suite, TestHashtblGet );
    SUITE_ADD_TEST( suite, TestHashtblRemove );

    return suite;
}
