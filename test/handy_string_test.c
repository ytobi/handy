#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"


void TestStringCreate       ( CuTest * tc )
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
void TestStringAppend       ( CuTest * tc )
{
    handy_string string = handy_create_string();

    CuAssertTrue( tc, string->append( &string, "string" ) );

    CuAssertIntEquals( tc, strlen("string"), string->length(&string) );

    string->free(&string);
    free( string );
}
void TestStringEqual        ( CuTest * tc )
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
void TestStringEqualStr     ( CuTest * tc )
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
void TestStringAddCharFront ( CuTest * tc )
{
    handy_string str = handy_create_string();
    CuAssertTrue( tc, str->add_char_front(&str, 'B') );
    CuAssertTrue( tc, str->length(&str) == 1 );

    CuAssertTrue( tc, str->add_char_front(&str, 'A') );
    CuAssertTrue( tc, str->length(&str) == 2 );

    str->free( &str );
    free( str );
}
void TestStringAddCharBack  ( CuTest * tc )
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
void TestStringAddCharAt    ( CuTest * tc )
{
    handy_string str = handy_create_string();

    // This is a possible valid location since str length is 0
    CuAssertTrue( tc, str->add_char_at( &str, 'A', 0 ) );

    // This is NOT a possible valid location since str length is 10
    CuAssertTrue( tc, !str->add_char_at( &str, 'B', 10 ) );

    str->free(&str);
    free(str);
}
void TestStringContainChar  ( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append(&str, "Hello, World" );

    // return position of first occurrence aka 0
    CuAssertTrue( tc, str->contain_char( &str, 'H') == 0 );

    // return -1 for not found
    CuAssertTrue( tc, str->contain_char( &str, 'A') == -1 );

    str->free(&str);
    free(str);
}
void TestStringContainStr   ( CuTest * tc )
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
void TestStringGetBackChar  ( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append( &str, "Hello, World" );

    CuAssertIntEquals( tc, 'd', str->get_back_char(&str) );

    str->free( &str );
    free( str );
}
void TestStringGetFrontChar ( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append( &str, "Hello, World" );

    CuAssertIntEquals( tc, 'H', str->get_front_char(&str) );

    str->free( &str );
    free( str );
}
void TestStringGetCharAt    ( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append( &str, "Hello, World" );

    CuAssertIntEquals( tc, 'H', str->get_char_at(&str, 0) );

    CuAssertIntEquals( tc, 'd', str->get_char_at(&str, str->length(&str) - 1) );

    str->free( &str );
    free( str );
}
void TestStringDeleteFrontChar( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append( &str, "Hello, World" );

    CuAssertTrue( tc, str->del_front_char(&str) );

    // assume string.get_front_char passed
    CuAssertTrue( tc, str->get_front_char(&str) != 'H' );


    str->free( &str );
    free( str );
}
void TestStringDeleteBackChar( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append( &str, "Hello, World" );

    CuAssertTrue( tc, str->del_back_char(&str) );

    // assume string.get_back_char passed
    char b = str->get_back_char(&str);
    CuAssertTrue( tc, str->get_back_char(&str) != 'd' );

    str->free( &str );
    free( str );
}
void TestStringDeleteCharAt ( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append( &str, "Hello, World" );

    CuAssertTrue( tc, str->del_char_at(&str, 1) );
    // assume string.get_char_at passed, position 1 now has l
    CuAssertTrue( tc, str->get_char_at(&str, 1) != 'e' );

    CuAssertTrue( tc, str->del_char_at(&str, 2) );
    // assume string.get_char_at passed, position 2 now has o
    CuAssertTrue( tc, str->get_char_at(&str, 2) != 'l' );

    str->free( &str );
    free( str );
}
void TestStringReverse      ( CuTest * tc )
{
    handy_string str2 = handy_create_string();
    handy_string str1 = handy_create_string();

    // even string length
    char * even = "even";
    // odd string length
    char * odd = "odd";

    str1->append( &str1, even );
    // assume string.get_char_at passed, before position 0 has 'e'
    CuAssertTrue( tc, str1->get_char_at(&str1, 0) == 'e' );
    str1->reverse( &str1 );
    // assume string.get_char_at passed, after reverse position 0 now has n
    CuAssertTrue( tc, str1->get_char_at(&str1, 0) == 'n' );


    str2->append( &str2, odd );
    // assume string.get_char_at passed, before position 0 has 'o'
    CuAssertTrue( tc, str2->get_char_at(&str2, 0) == 'o' );
    str2->reverse( &str2 );
    // assume string.get_char_at passed, after reverse position 0 now has d
    CuAssertTrue( tc, str2->get_char_at(&str2, 0) == 'd' );


    str1->free( &str1 );
    str2->free( &str2 );
    free( str1 );
    free( str2 );
}
void TestStringWordCount    ( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append( &str, "  I   love    you   " );

    // with ' ' as delimiter, word count should be 3, ignore space(s)
    str->word_count( &str, " " );
    CuAssertIntEquals( tc, 3, str->word_count( &str, " " ) );

    // with ',' as delimiter, word count should be 3, ignore space(s)
    str->word_count( &str, "," );
    CuAssertIntEquals( tc, 1, str->word_count( &str, "," ) );

    str->free( &str );
    free( str );
}
void TestStringFree         ( CuTest * tc )
{
    handy_string str = handy_create_string();
    str->append( &str, "Hello, World" );

    // before freeing, string is not null
    CuAssertPtrNotNull( tc, str->string(&str) );
    CuAssertIntEquals( tc, strlen("Hello, World"), str->length(&str) );

    str->free( &str );
    // after freeing, string is maybe not null, but size should reflect that fact
    CuAssertIntEquals( tc, 0, str->length(&str) );

    free( str );
}
void TestStringLength       ( CuTest * tc )
{
    handy_string str = handy_create_string();
    // before appending, length is 0
    CuAssertIntEquals( tc, 0, str->length(&str) );

    // after appending, length has now changed to expected.
    str->append( &str, "Hello, World" );
    CuAssertIntEquals( tc, strlen("Hello, World"), str->length(&str) );

    str->free( &str );
    free( str );

}
void TestStringToUpper      ( CuTest * tc )
{
    handy_string str = handy_create_string();

    str->append( &str, "Hello, World" );
    str->to_upper( &str );

    CuAssertStrEquals( tc, "HELLO, WORLD", str->string(&str) );

    str->free( &str );
    free( str );
}
void TestStringToLower      ( CuTest * tc )
{
    handy_string str = handy_create_string();

    str->append( &str, "Hello, World" );
    str->to_lower( &str );

    CuAssertStrEquals( tc, "hello, world" , str->string(&str) );

    str->free( &str );
    free( str );
}

CuSuite * HandyStringGetSuit()
{
    CuSuite * suite = CuSuiteNew();
    SUITE_ADD_TEST( suite, TestStringCreate );
    SUITE_ADD_TEST( suite, TestStringAppend );
    SUITE_ADD_TEST( suite, TestStringEqual );
    SUITE_ADD_TEST( suite, TestStringEqualStr );
    SUITE_ADD_TEST( suite, TestStringAddCharFront );
    SUITE_ADD_TEST( suite, TestStringAddCharBack );
    SUITE_ADD_TEST( suite, TestStringAddCharAt );
    SUITE_ADD_TEST( suite, TestStringContainChar );
    SUITE_ADD_TEST( suite, TestStringContainStr );
    SUITE_ADD_TEST( suite, TestStringGetBackChar );
    SUITE_ADD_TEST( suite, TestStringGetFrontChar );
    SUITE_ADD_TEST( suite, TestStringGetCharAt );
    SUITE_ADD_TEST( suite, TestStringDeleteFrontChar );
    SUITE_ADD_TEST( suite, TestStringDeleteBackChar );
    SUITE_ADD_TEST( suite, TestStringDeleteCharAt );
    SUITE_ADD_TEST( suite, TestStringReverse );
    SUITE_ADD_TEST( suite, TestStringWordCount );
    SUITE_ADD_TEST( suite, TestStringFree );
    SUITE_ADD_TEST( suite, TestStringLength );
    SUITE_ADD_TEST( suite, TestStringToUpper );
    SUITE_ADD_TEST( suite, TestStringToLower );

    return suite;
}
