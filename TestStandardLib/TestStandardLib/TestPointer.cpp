#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ObjectWriterChunkedTestClasses.h"
#include "EmbeddedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerNegation(void)
{
	ObjectsInit();

	Ptr<CTestObject>	pcObject;
	CPointer			pcBase;

	pcObject = OMalloc(CTestObject);
	pcObject->Init(NULL);
	AssertFalse(!pcObject);

	pcObject = NULL;
	AssertTrue(!pcObject);

	pcBase = OMalloc(CTestObject);
	((CTestObject*)&pcBase)->Init(NULL);
	AssertFalse(!pcBase);

	pcBase = NULL;
	AssertTrue(!pcBase);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerConstructor(void)
{
	ObjectsInit();

	CEmbeddedContainer	cCluster;

	cCluster.PreInit();
	cCluster.Init();
	AssertNull(cCluster.mpTest.Object());
	AssertPointer(&cCluster, cCluster.mpTest.Embedding());

	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerDestructorDestruct(STestObjectKilledNotifier* psKillNotifier)
{
	CTestObject					cTestObject;

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	cTestObject.Init(NULL);
	cTestObject.mpTest = OMalloc(CTestObject)->Init(psKillNotifier);

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	//cTestObject Destructor called here.  It should cause the allocated object it points to to be destroyed too.
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerDestructor(void)
{
	ObjectsInit();

	STestObjectKilledNotifier	sKillNotifier;

	TestPointerDestructorDestruct(&sKillNotifier);
	
	AssertTrue(sKillNotifier.bKilled);
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerStackToEmbeddedDestruct(void)
{
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	Ptr<CEmbeddedContainer> pMissile = OMalloc(CEmbeddedContainer);

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerStackToEmbedded(void)
{
	ObjectsInit();

	TestPointerStackToEmbeddedDestruct();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAssignment()
{
	ObjectsInit();

	Ptr<CTestWithArray>	pcObject1;
	pcObject1 = ONMalloc(CTestWithArray, "Urgle-burgle");
	pcObject1->Init("Warning", 17);

	AssertNotNull(&pcObject1);
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointer(void)
{
	BeginTests();

	TestPointerConstructor();
	TestPointerDestructor();
	TestPointerStackToEmbedded();
	TestAssignment();
	TestPointerNegation();

	TestStatistics();
}

