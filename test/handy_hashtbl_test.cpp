#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"

void TestHashtblAdd( CuTest * tc )
{
    handy_hashtbl table = handy_create_hashtbl();
    CuAssertPtrNotNull( tc, table );

    // check if return of function to create list
    // actually created
    int actualSize = list->size;
    int expectedSize = 0;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    list->free(&list);
    free( list );
}

CuSuite * HandyListGetSuit()
{

    CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST( suite, TestHashtblAdd );
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

    return suite;
}


bool (*contain)         ( handy_hashtbl * l, void * key );
bool (*add)             ( handy_hashtbl * l, void * key, void * item );
bool (*empty)           ( handy_hashtbl * l );

void * (*get)           ( handy_hashtbl * l, void * key );
void * (*remove)        ( handy_hashtbl * l, void * key );
void   (*free)          ( handy_hashtbl * l );