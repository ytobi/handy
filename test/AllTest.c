#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"

CuSuite * HandyListGetSuit();
CuSuite * HandyStackGetSuit();
CuSuite * HandyQueueGetSuit();
CuSuite * HandyStringGetSuit();
CuSuite * HandyHashtblGetSuit();

void RunAllTests(void)
{
	CuString * output = CuStringNew();
	CuSuite * suite = CuSuiteNew();
	
	CuSuiteAddSuite( suite, HandyListGetSuit() );
	CuSuiteAddSuite( suite, HandyStackGetSuit() );
	CuSuiteAddSuite( suite, HandyQueueGetSuit() );
	CuSuiteAddSuite( suite, HandyStringGetSuit() );
	// CuSuiteAddSuite( suite, HandyHashtblGetSuit() );

	CuSuiteRun( suite );
	CuSuiteSummary( suite, output );
	CuSuiteDetails( suite, output );
	printf("%s\n", output->buffer );
}

int main(void)
{
	RunAllTests();
}
