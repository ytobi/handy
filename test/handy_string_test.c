#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"


void TestStringCreate( CuTest * tc )
{
    handy_string string = handy_create_string();
    CuAssertPtrNotNull( tc, string );

    // check if return of function to create string
    // actually created
    int actualSize = string->length( &string );
    int expectedSize = 0;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    string->free(&string);
    free( string );
}
void TestStringEqual( CuTest * tc )
{
    handy_string string1 = handy_create_string();
    handy_string string2 = handy_create_string();

    CuAssertPtrNotNull( tc, string1 );
    CuAssertPtrNotNull( tc, string2 );

    // when created string1 and string2 should equal( size == 0 )
    CuAssertTrue( tc, string1->is_null(&string1) );
    CuAssertTrue( tc, string2->is_null(&string1) );

    string1->append( &string1, "string1" );
    string2->append( &string2, "string1" );

    // check if string(s) is equal to itself
    CuAssertTrue( tc, string1->equal( &string1, &string1) );
    CuAssertTrue( tc, string2->equal( &string2, &string2) );

    // string1 and string2 initialise thesema, check if equal
    CuAssertTrue( tc, string1->equal( &string1, &string2) );

    // change string1 and check equality with string2
    string1->append( &string1, "hello" );
    CuAssertTrue( tc, !string1->equal( &string1, &string2) );

    string1->free( &string1 );
    string2->free( &string2 );
    free( string1 );
    free( string2 );
}
void TestStringEqualStr( CuTest * tc )
{
    handy_string string1 = handy_create_string();
    handy_string string2 = handy_create_string();

    CuAssertPtrNotNull( tc, string1 );
    CuAssertPtrNotNull( tc, string2 );

    // when created string1 and string2 should equal NULL
    CuAssertTrue( tc, string1->equal_str(&string1, "") );
    CuAssertTrue( tc, string2->equal_str(&string2, "") );

    string1->append( &string1, "string1" );
    string2->append( &string2, "string1" );

    // concatinating a null string to string1 should still equal string1
    string1->append( &string1, "");
    CuAssertTrue( tc, string1->equal_str( &string1, string1->string(&string1)) );

    // string1 and string2 initialise thesame, should be equal.
    CuAssertTrue( tc, string1->equal_str( &string1, string2->string(&string2) ) );

    // adding "10" to string one should equal concatinating string1 to "10"
    string1->append( &string1, "10" );
    CuAssertTrue( tc, string1->equal_str( &string1,"string110") );

    string1->free( &string1 );
    string2->free( &string2 );
    free( string1 );
    free( string2 );
}
void TestStringAddCharFront( CuTest * tc )
{
    handy_string str = handy_create_string();
    CuAssertTrue( tc, str->add_char_front(&str, "B") );
    CuAssertTrue( tc, str->length(&str) == 1 );

    CuAssertTrue( tc, str->add_char_front(&str, "A") );
    CuAssertTrue( tc, str->length(&str) == 2 );

    str->free( &str );
    free( str );
}
void TestStringAddCharBack( CuTest * tc )
{
    handy_string str = handy_create_string();

    // test response, if positive and hence item was added
    CuAssertTrue( tc, str->add_char_back(&str, 'A') );
    CuAssertTrue( tc, str->length(&str) == 1 );

    CuAssertTrue( tc, str->add_char_back(&str, 'B') );
    CuAssertTrue( tc, str->length(&str) == 2 );

    str->free(&str);
    free( str );
}
void TestStringAddCharAt( CuTest * tc )
{
    handy_string str = handy_create_string();

    // This is a possible valid location since str length is 0
    CuAssertTrue( tc, str->add_char_at( &str, 'A', 0 ) );

    // This is NOT a possible valid location since str length is 10
    CuAssertTrue( tc, !str->add_char_at( &str, 'B', 10 ) );

    str->free(&str);
    free(str);
}
void TestStringContainChar( CuTest * tc ) // TODO fail
{
    handy_string str = handy_create_string();
    str->append(&str, "Hello, World" );

    // return postion of first occurrence aka 0
    CuAssertTrue( tc, str->contain_char( &str, 'H') == 0 );

    // return -1 for not found
    CuAssertTrue( tc, !str->contain_char( &str, 'A') == -1 );

    str->free(&str);
    free(str);
}
void TestStringContainStr( CuTest * tc ) // TODO
{
    handy_string str = handy_create_string();
    str->append(&str, "Hello, World" );

    // return postion of first occurrence aka 0
    CuAssertIntEquals( tc, 0, str->contain_str( &str, "Hello" ) );

    // return 7 for world
    CuAssertIntEquals( tc, 7, str->contain_str( &str, "World" ) );

    str->free(&str);
    free(str);
}
void TestStringGet( CuTest * tc ) // TODO
{
}
void TestStringRemove( CuTest * tc ) // TODO
{
}
void TestStringReverse( CuTest * tc ) // TODO
{
}

CuSuite * HandyStringGetSuit()
{
    CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST( suite, TestStringCreate );
    SUITE_ADD_TEST( suite, TestStringEqual );
    SUITE_ADD_TEST( suite, TestStringEqualStr );
    SUITE_ADD_TEST( suite, TestStringAddCharFront );
    SUITE_ADD_TEST( suite, TestStringAddCharBack );
    SUITE_ADD_TEST( suite, TestStringAddCharAt );
    SUITE_ADD_TEST( suite, TestStringContainChar );
    SUITE_ADD_TEST( suite, TestStringContainStr );

    return suite;
}
