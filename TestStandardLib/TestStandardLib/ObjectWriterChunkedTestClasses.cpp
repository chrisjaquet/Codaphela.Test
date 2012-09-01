#include "StandardLib/Objects.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"
#include "ObjectWriterChunkedTestClasses.h"


void CTestWithArray::Init(char* szString, int x)
{
	mcArray.Init(this);
	mcArray = OMalloc(CArray);
	mcArray->Init();
	mszString.Init(szString);
	mx = x;
}

void CTestWithArray::Kill(void)
{
	mszString.Kill();
	CObject::Kill();
}

void CTestWithArray::Add(CPointerObject pcObject)
{
	mcArray->Add(pcObject);
}

BOOL CTestWithArray::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WritePointer(mcArray));
	ReturnOnFalse(pcFile->WriteString(&mszString));
	ReturnOnFalse(pcFile->WriteInt(mx));
	return TRUE;
}

BOOL CTestWithArray::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadPointer(mcArray.This(this)));
	ReturnOnFalse(pcFile->ReadString(&mszString));
	ReturnOnFalse(pcFile->ReadInt(&mx));
	return TRUE;
}


void CTestInteger::Init(int x, int y, int z)
{
	mx = x;
	my = y;
	mz = z;
}

void CTestInteger::Kill(void)
{
	CObject::Kill();
}

BOOL CTestInteger::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WriteInt(mx));
	ReturnOnFalse(pcFile->WriteInt(my));
	ReturnOnFalse(pcFile->WriteInt(mz));
	return TRUE;
}

BOOL CTestInteger::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadInt(&mx));
	ReturnOnFalse(pcFile->ReadInt(&my));
	ReturnOnFalse(pcFile->ReadInt(&mz));
	return TRUE;
}


void CTestNamedString::Init(CPointer<CString> szString, CPointer<CTestNamedString> pAnother, char* szEmbedded)
{
	mszString.Init(this);
	mpAnother.Init(this);
	mszString = szString;
	mpAnother = pAnother;
	mszEmbedded.Init(szEmbedded);
}


void CTestNamedString::Kill(void)
{
	mszString->Kill();
	CObject::Kill();
}

BOOL CTestNamedString::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WritePointer(mszString));
	ReturnOnFalse(pcFile->WritePointer(mpAnother));
	ReturnOnFalse(pcFile->WriteString(&mszEmbedded));
	return TRUE;
}

BOOL CTestNamedString::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadPointer(mszString.This(this)));
	ReturnOnFalse(pcFile->ReadPointer(mpAnother.This(this)));
	ReturnOnFalse(pcFile->ReadString(&mszEmbedded));
	return TRUE;
}

