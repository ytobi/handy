#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"

void TestVectorCreate   ( CuTest * tc )
{
    handy_vector v = handy_create_vector();

    // assume capacity passed
    CuAssertTrue( tc,v->capacity( &v ) > 0 );

    v->free( &v );
    free( v );
}
void TestVectorSetAt    ( CuTest * tc )
{
    handy_vector v = handy_create_vector();


    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        CuAssertTrue( tc, v->set_at( &v, i, i ) );
    }

    // adding item to index less than zero: Not possible, assert we get a not-true
    CuAssertTrue( tc, !v->set_at( &v, "hello", -1 ) );

    // adding past capacity of v, will cause v to resize properly
    CuAssertTrue( tc, v->set_at(&v, "hello", v->capacity(&v) + 100) );

    // addition and position already filed should be possible.
    CuAssertTrue( tc, v->set_at(&v, "hello, world", v->capacity(&v) + 0) );

    v->free( &v );
    free( v );
}
void TestVectorGetAt    ( CuTest * tc )
{
    handy_vector v = handy_create_vector();

    CuAssertPtrEquals( tc, NULL, v->get_at(&v, 1) );

    // assume set_at and capacity passed.
    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        CuAssertTrue( tc, v->set_at( &v, i, i ) );
    }

    // try getting all added item back, see if they match what we expect
    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        CuAssertIntEquals( tc, i, v->get_at(&v, i) );
    }

    // not allowed to read before/past memory allocation, hence expect null
    CuAssertPtrEquals( tc, NULL, v->get_at(&v, v->capacity(&v) + 1) );
    CuAssertPtrEquals( tc, NULL, v->get_at(&v, -1) );

    v->free( &v );
    free( v );
}
void TestVectorContain  ( CuTest * tc )
{
    handy_vector v = handy_create_vector();

    // noting in vector, should be not-true
    CuAssertTrue( tc, v->contain(&v, "hello") == -1 );

    // assume set_at and capacity passed.
    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        CuAssertTrue( tc, v->set_at( &v, i, i ) );
    }

    // expect it contain all item just added
    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        // should contain all item recently add
        CuAssertTrue( tc, v->contain(&v, i) == i );
    }

    // after addition of item, still does not contain hello
    CuAssertTrue( tc, v->contain(&v, "hello") == -1 );

    v->free( &v );
    free( v );
}
void TestVectorRemoveAT ( CuTest * tc )
{
    handy_vector v = handy_create_vector();

    // noting in vector, is same as removed
    CuAssertTrue( tc, v->rem_at(&v, 1) );

    // assume set_at and capacity passed.
    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        CuAssertTrue( tc, v->set_at( &v, i, i ) );
    }

    // remove all item just added
    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        CuAssertTrue( tc, v->rem_at(&v, i) );
    }

    // remove at location outside vector should not be allowed
    CuAssertTrue( tc, !v->rem_at(&v, v->capacity(&v) + 100) );
    CuAssertTrue( tc, !v->rem_at(&v, -1) );

    v->free( &v );
    free( v );
}
void TestVectorCapacity ( CuTest * tc )
{
    handy_vector v = handy_create_vector();

    // noting in vector, is same as removed
    int originalCapacity = v->capacity( &v );

    // assume set_at and capacity passed.
    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        CuAssertTrue( tc, v->set_at( &v, i, i ) );
    }
    // should still be the same
    CuAssertTrue( tc, v->capacity(&v) == originalCapacity );

    v->set_at( &v, 'hello', v->capacity(&v) + 1 );

    // we add passed capacity, capacity should expand by 1/4
    CuAssertTrue( tc, v->capacity(&v) == (originalCapacity + (originalCapacity + 4) / 4) );

    // this is more the 1/4 + capacity, hence capacity should be 5000
    int at = 5000;
    v->set_at( &v, 'hello',  5000 );
    CuAssertTrue( tc, v->capacity(&v) == 5000 );

    v->free( &v );
    free( v );
}
void TestVectorFree     ( CuTest * tc )
{
    handy_vector v = handy_create_vector();

    // assume set_at and capacity passed.
    for( int i = 0; i < v->capacity( &v ); i++ )
    {
        CuAssertTrue( tc, v->set_at( &v, i, i ) );
    }

    v->free( &v );

    // after call free all vector is now empty,
    // noting to test here else we might run into runtime
    // error. Pretty sure every this is removed.
    // NOTE: to gain confidence in this run with valgrind
    // notice no error reported.

    free( v );
}

CuSuite * HandyVectorGetSuit()
{

    CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST( suite, TestVectorCreate );
    SUITE_ADD_TEST( suite, TestVectorSetAt );
    SUITE_ADD_TEST( suite, TestVectorGetAt );
    SUITE_ADD_TEST( suite, TestVectorContain );
    SUITE_ADD_TEST( suite, TestVectorRemoveAT );
    SUITE_ADD_TEST( suite, TestVectorFree );
    SUITE_ADD_TEST( suite, TestVectorCapacity );

    return suite;
}