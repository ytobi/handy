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
void TestStringAddFront( CuTest * tc )
{
    handy_string string = handy_create_string();
    CuAssertPtrNotNull( tc, string );

    // test response, if positive and hence item was added
    int actualResponse = string->add_char_front( &string, 'i' );
    int expectedResponse = 1; // true
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // We test the size if a change in size
    int actualSize = string->length( &string );
    int expectedSize = 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    //  add char as letter or number is accepted
    actualResponse = string->add_char_front( &string, 95 );
    expectedResponse = 1; // true;
    CuAssertIntEquals( tc, expectedResponse, actualResponse );


    //  add char as letter or number is accepted, false is 0
    actualResponse = string->add_char_front( &string, false );
    expectedResponse = 1; // true;
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // size should change as added numeric data sucessfull
    actualSize = string->length( &string );
    expectedSize = 3;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    actualResponse = string->add_char_front( &string, 'H' );
    expectedResponse = 1; // true
    CuAssertIntEquals( tc, expectedResponse, actualResponse );

    // size should change, as added "H" data successfully
    actualSize = string->length( &string );
    expectedSize = 2;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    // final string is "Hi", added "i" and "H"
    CuAssertStrEquals( tc, "Hi", string->string(&string) );

    string->free( &string );
    free( string );
}
void TestStringAddBack( CuTest * tc )
{
    handy_string string = handy_create_string();
    char * input = strdup("hello, world!");

    // test response, if positive and hence item was added
    bool actualResponse = string->append(&string, input);
    CuAssertTrue( tc, actualResponse );

    // We test the size if a change in size
    int actualSize = string->length( &string );
    int expectedSize = strlen( input );
    CuAssertIntEquals( tc, expectedSize, actualSize );

    //  add  a single char a test every bahavoir and result for addition
    string->add_char_front( &string, 'A' );
    char actualChar = string->get_front_char( &string );
    char expectedChar = 'A';
    CuAssertIntEquals( tc, expectedChar, actualChar );

    // added single char check if length increase by one
    actualSize = string->length( &string );
    expectedSize = strlen( input ) + 1;
    CuAssertIntEquals( tc, expectedSize, actualSize );

    string->add_char_back( &string, 'A' );
    actualChar = string->get_back_char( &string );
    expectedChar = 'A';
    CuAssertIntEquals( tc, expectedChar, actualChar );

    string->free(&string);
    free( string );
}
void TestStringAddAt( CuTest * tc ) // TODO
{
}
void TestStringContain( CuTest * tc ) // TODO
{
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
    SUITE_ADD_TEST( suite, TestStringAddFront );
    SUITE_ADD_TEST( suite, TestStringAddBack );

    return suite;
}
