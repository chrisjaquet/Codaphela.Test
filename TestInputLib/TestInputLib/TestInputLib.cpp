#include "TestLib/Assert.h"
#include "TestInputChords.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{	
	InitTotalStatistics();

	TestInputChords();

	return TestTotalStatistics();
}

