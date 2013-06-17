#ifndef __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#define __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__
#include "StandardLib/Object.h"
#include "StandardLib/NamedObject.h"
#include "StandardLib/Array.h"
#include "StandardLib/String.h"


class CTestWithArray : public CNamedObject
{
BASE_FUNCTIONS(CTestWithArray);
public:
	Ptr<CArray>	mcArray;

	CChars		mszString;
	int			mx;

	void Init(char* szString, int x);
	void KillData(void);

	void Add(CPointerObject pcObject);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestInteger : public CObject
{
BASE_FUNCTIONS(CTestInteger);
public:
	int mx;
	int my; 
	int mz;

	void Init(int x, int y, int z);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestNamedString : public CNamedObject
{
BASE_FUNCTIONS(CTestNamedString);
public:
	Ptr<CString>			mszString;
	Ptr<CTestNamedString>	mpAnother;
	CChars					mszEmbedded;

	void Init(Ptr<CString> szString, Ptr<CTestNamedString> pAnother, char* szEmbedded);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


class CTestDoubleNamedString : public CNamedObject
{
BASE_FUNCTIONS(CTestDoubleNamedString);
public:
	Ptr<CString>			mszString;
	Ptr<CTestNamedString>	mpSplit2;
	Ptr<CTestNamedString>	mpSplit1;

	void Init(void);
	void Init(Ptr<CString> szString, Ptr<CTestNamedString> pSplit2, Ptr<CTestNamedString> pSplit1);
	void KillData(void);

	BOOL Save(CObjectSerialiser* pcFile);
	BOOL Load(CObjectDeserialiser* pcFile);
};


#endif // __OBJECT_WRITER_CHUNKED_TEST_CLASSES_H__

