#include "StandardLib/Objects.h"
#include "StandardLib/ObjectSerialiser.h"
#include "StandardLib/ObjectDeserialiser.h"
#include "ObjectTestSetup.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGraphicPicture::Init(void)
{
	strcpy(mszPretenedImAPicture, "012345678901234");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGraphicPicture::Kill(void)
{
	strcpy(mszPretenedImAPicture, "Alas I am Dead!");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CPlayerVehicle> CPlayerVehicle::Init(void)
{
	mpsPoint = (SPhysicsPoint*)malloc(sizeof(SPhysicsPoint));
	mcPicture.Init();

	mpsPoint->x = 'X';
	mpsPoint->y = 'Y';
	mpsPoint->z = 'Z';

	mpsBeforeDeath = NULL;
	mpsAfterDeath = NULL;

	return Ptr<CPlayerVehicle>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayerVehicle::Class(void)
{
	CObject::Class();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayerVehicle::KillData(void)
{
	if (mpsBeforeDeath)
	{
		memcpy(&mpsBeforeDeath->sPoint, mpsPoint, sizeof(SPhysicsPoint));
		memcpy(&mpsBeforeDeath->cPicture, &mcPicture, sizeof(CGraphicPicture));
	}

	mcPicture.Kill();
	free(mpsPoint);
	mpsPoint = NULL;

	if (mpsAfterDeath)
	{
		memset(&mpsAfterDeath->sPoint, 0, sizeof(SPhysicsPoint));
		memcpy(&mpsAfterDeath->cPicture, &mcPicture, sizeof(CGraphicPicture));
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayerVehicle::SetKillHook(SStateOnKill* psBeforeDeath, SStateOnKill* psAfterDeath)
{
	mpsBeforeDeath = psBeforeDeath;
	mpsAfterDeath = psAfterDeath;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CHarrier> CHarrier::Init(Ptr<CGameWorld> pWorld)
{
	CPlayerVehicle::Init();
	mpWorld = pWorld;
	miSpeed = 7;

	maMissiles = OMalloc(CArrayObject);
	maMissiles->Init();

	return Ptr<CHarrier>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHarrier::Class(void)
{
	CPlayerVehicle::Class();
	Pointer(mpWorld.This());
	Pointer(maMissiles.This());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHarrier::KillData(void)
{
	CPlayerVehicle::KillData();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CMissile> CHarrier::FireMissile(CPointer& pTarget)
{
	Ptr<CMissile> pMissile = OMalloc(CMissile);
	pMissile->Init(mpWorld);
	maMissiles->Add(pMissile);
	pMissile->SetTarget(pTarget);

	mpWorld->AddTickable(pMissile);

	return pMissile;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CArrayObject> CHarrier::GetMissiles(void)
{
	return maMissiles;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CJeep> CJeep::Init(Ptr<CGameWorld> pWorld)
{
	CPlayerVehicle::Init();
	mpWorld = pWorld;
	mfBackWheel = 2.3f;
	mfFrontWheel = 2.1f;

	return Ptr<CJeep>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CJeep::Class(void)
{
	CPlayerVehicle::Class();
	Pointer(mpWorld.This());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CJeep::KillData(void)
{
	CPlayerVehicle::KillData();
	mfBackWheel = 0.0f;
	mfFrontWheel = 0.0f;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CMissile> CMissile::Init(Ptr<CGameWorld> pWorld)
{
	mpWorld = pWorld;
	mpTarget = NULL;

	mszKillState = NULL;

	return Ptr<CMissile>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMissile::Class(void)
{
	CObject::Class();
	Pointer(mpWorld.This());
	Pointer(mpTarget.This());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMissile::KillData(void)
{
	if (mszKillState)
	{
		strcpy(mszKillState, "Killed");
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer CMissile::GetTarget(void)
{
	return mpTarget;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMissile::SetTarget(CPointer& pTarget)
{
	mpTarget = pTarget;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CMissile::Save(CObjectSerialiser* pcFile)
{ 
	ReturnOnFalse(pcFile->WritePointer(mpWorld));
	ReturnOnFalse(pcFile->WritePointer(mpTarget));
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CMissile::Load(CObjectDeserialiser* pcFile) 
{ 
	ReturnOnFalse(pcFile->ReadPointer(Pointer(mpWorld.This())));
	ReturnOnFalse(pcFile->ReadPointer(Pointer(mpTarget.This())));
	return TRUE; 
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMissile::SetKillString(char* szKillString)
{
	mszKillState = szKillString;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CRedJet> CRedJet::Init(Ptr<CGameWorld> pWorld)
{
	mpsPoint = (SPhysicsPoint*)malloc(sizeof(SPhysicsPoint));
	mcPicture.Init();

	mpWorld = pWorld;

	Ptr<CRedJet> pThis;
	pThis = this;
	mpWorld->AddTickable(pThis);

	return Ptr<CRedJet>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRedJet::Class(void)
{
	CObject::Class();
	Pointer(mpWorld.This());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRedJet::KillData(void)
{
	memcpy(&mpsBeforeDeath->sPoint, mpsPoint, sizeof(SPhysicsPoint));
	memcpy(&mpsBeforeDeath->cPicture, &mcPicture, sizeof(CGraphicPicture));

	mcPicture.Kill();
	free(mpsPoint);
	mpsPoint = NULL;

	memset(&mpsAfterDeath->sPoint, 0, sizeof(SPhysicsPoint));
	memcpy(&mpsAfterDeath->cPicture, &mcPicture, sizeof(CGraphicPicture));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRedJet::SetKillHook(SStateOnKill* psBeforeDeath, SStateOnKill* psAfterDeath)
{
	mpsBeforeDeath = psBeforeDeath;
	mpsAfterDeath = psAfterDeath;

	strcpy(mpsBeforeDeath->cPicture.mszPretenedImAPicture, "Kill not called");
	strcpy(mpsAfterDeath->cPicture.mszPretenedImAPicture, "Kill not called");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CClusterMissile> CClusterMissile::Init(Ptr<CGameWorld> pWorld)
{
	mcMissile1.Init(pWorld);
	mcMissile2.Init(pWorld);

	mszKillState = NULL;

	return Ptr<CClusterMissile>(this);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterMissile::Class(void)
{
	CObject::Class();
	Pointer(mpWorld.This());
	Embedded(&mcMissile1);
	Embedded(&mcMissile2);

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterMissile::KillData(void)
{
	if (mszKillState)
	{
		strcpy(mszKillState, "Killed");
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterMissile::SetKillString(char* szKillString)
{
	mszKillState = szKillString;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CClusterMissile::Save(CObjectSerialiser* pcFile)
{ 
	ReturnOnFalse(mcMissile1.Save(pcFile));
	ReturnOnFalse(mcMissile2.Save(pcFile));
	ReturnOnFalse(pcFile->WritePointer(mpWorld));
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CClusterMissile::Load(CObjectDeserialiser* pcFile) 
{ 
	ReturnOnFalse(mcMissile1.Load(pcFile));
	ReturnOnFalse(mcMissile2.Load(pcFile));
	ReturnOnFalse(pcFile->ReadPointer(mpWorld.This()));
	return TRUE; 
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CClusterLauncher> CClusterLauncher::Init(void)
{
	return Ptr<CClusterLauncher>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterLauncher::KillData(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterLauncher::Class(void)
{
	CObject::Class();
	Pointer(mpMissile.This());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CGameWorld> CGameWorld::Init(void)
{
	maTickables = OMalloc(CArrayObject);
	maTickables->Init(128);

	return Ptr<CGameWorld>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::KillData(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::Class(void)
{
	CObject::Class();
	Pointer(maTickables.This());
	Pointer(mpPlayer1.This());
	Pointer(mpPlayer2.This());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::AddPlayer(Ptr<CPlayerVehicle> pPlayer)
{
	if (pPlayer.IsNull())
	{
		return;
	}

	if (mpPlayer1.IsNull())
	{
		mpPlayer1 = pPlayer;
	}
	else if (mpPlayer2.IsNull())
	{
		mpPlayer2 = pPlayer;
	}
	else
	{
		return;
	}

	maTickables->Add(pPlayer);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::AddTickable(CPointer& pTickable)
{
	if (pTickable.IsNotNull())
	{
		maTickables->Add(pTickable);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::RemoveTickable(CPointer& pTickable)
{
	if (pTickable.IsNotNull())
	{
		maTickables->Remove(pTickable);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CGameWorld::Save(CObjectSerialiser* pcFile)
{
	ReturnOnFalse(pcFile->WritePointer(maTickables));
	ReturnOnFalse(pcFile->WritePointer(mpPlayer1));
	ReturnOnFalse(pcFile->WritePointer(mpPlayer2));
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CGameWorld::Load(CObjectDeserialiser* pcFile)
{
	ReturnOnFalse(pcFile->ReadPointer(maTickables.This()));
	ReturnOnFalse(pcFile->ReadPointer(mpPlayer1.This()));
	ReturnOnFalse(pcFile->ReadPointer(mpPlayer2.This()));
	return TRUE; 
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CArrayObject> CGameWorld::GetTickables(void)
{
	return maTickables;
}

