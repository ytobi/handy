#include "CuTest-1.5/CuTest.h"
#include "../include/handy.h"

CuSuite * HandyListGetSuit();

void RunAllTests(void)
{
	CuString * output = CuStringNew();
	CuSuite * suite = CuSuiteNew();
	
	CuSuiteAddSuite( suite, HandyListGetSuit() );
	
	CuSuiteRun( suite );
	CuSuiteSummary( suite, output );
	CuSuiteDetails( suite, output );
	printf("%s\n", output->buffer );
}

int main(void)
{
	RunAllTests();
}
