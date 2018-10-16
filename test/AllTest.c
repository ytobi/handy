#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"

CuSuite * HandyListGetSuit();
CuSuite * HandyStackGetSuit();
CuSuite * HandyQueueGetSuit();
CuSuite * HandyStringGetSuit();

void RunAllTests(void)
{
	CuString * output = CuStringNew();
	CuSuite * suite = CuSuiteNew();
	
	CuSuiteAddSuite( suite, HandyListGetSuit() );
	CuSuiteAddSuite( suite, HandyStackGetSuit() );
	CuSuiteAddSuite( suite, HandyQueueGetSuit() );
	CuSuiteAddSuite( suite, HandyStringGetSuit() );

	CuSuiteRun( suite );
	CuSuiteSummary( suite, output );
	CuSuiteDetails( suite, output );
	printf("%s\n", output->buffer );
}

int main(void)
{
	RunAllTests();
}
