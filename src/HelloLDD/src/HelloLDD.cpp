/*
 ============================================================================
 Name		: HelloLDD.cpp
 Author	  : leftup
 Copyright   : Your copyright notice
 Description : CHelloLDD DLL source
 ============================================================================
 */

#include "HelloLDD.h"


_LIT(KLddName,"EKernCtl");


DECLARE_STANDARD_LDD()
{	
	return new DHelloLDDDriverFactory;
}

TInt DHelloLDDDriverFactory::Install()
{
	return SetName(&KLddName);
}

void DHelloLDDDriverFactory::GetCaps(TDes8& aDes) const
{
}

TInt DHelloLDDDriverFactory::Create(DLogicalChannelBase*& aChannel)
{
	aChannel = new DHelloLDDChannel;
	return aChannel ? KErrNone : KErrNoMemory;
}

//DHelloLDDDriverFactory::~DHelloLDDDriverFactory(){}

DHelloLDDDriverFactory::DHelloLDDDriverFactory()
{
	//iParseMask = 0;
	//iVersion = TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber);
	iVersion = TVersion(1,0,1);
}

/*DHelloLDDChannel::~DHelloLDDChannel()
{
	Kern::SafeClose((DObject*&)iClient,NULL);	
}*/
/*
DHelloLDDChannel::DHelloLDDChannel()
{
	iClient=&Kern::CurrentThread();
	iClient->Open();
}
*/

//TInt DHelloLDDChannel::RequestUserHandle(DThread* aThread, TOwnerType aType)
//{
	// Make sure that only our client can get a handle
	//if (aType!=EOwnerThread || aThread!=iClient)
	//	return KErrAccessDenied;
	//return KErrNone;
//}
	
TInt DHelloLDDChannel::DoCreate(TInt aUnit, const TDesC8* aInfo,const TVersion& aVer)
{
	if(!Kern::QueryVersionSupported(TVersion(1,0,1),aVer))
		return KErrNotSupported;
	
	return KErrNone;
}

TInt DHelloLDDChannel::Request(TInt aReqNo, TAny* a1, TAny* a2)
{
	//TRPMemoryInfo *info = (TRPMemoryInfo *)a1;
	//if (!info || !info->iData || info->iLength > info->iData->Length())
	//	return KErrArgument;
	switch (aReqNo)
		{
	case 0:
		{
		Kern::Printf("EKernCtl loaded\n");
		break;
		}
	case 1:
		{
		//Kern::Printf("EKernCtl Kern::Restart(0x40000000)\n");
		Kern::Restart(0x40000000);
		break;
		}

	default:
		return KErrNotSupported;
		}
	return KErrNone;
}

