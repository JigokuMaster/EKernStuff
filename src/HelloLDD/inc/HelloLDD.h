/*
 ============================================================================
 Name		: HelloLDD.h
 Author	  : leftup
 Copyright   : Your copyright notice
 Description : HelloLDD.h - CHelloLDD class header
 ============================================================================
 */

// This file defines the API for HelloLDD.dll

#ifndef __HELLOLDD_H__
#define __HELLOLDD_H__
#include "ekern.h"
#include "hellouserside.h"
#include "LDDCommon.h"


class DHelloLDDDriverFactory: public DLogicalDevice
{
public:
//	~DHelloLDDDriverFactory();
	DHelloLDDDriverFactory();
	virtual TInt Install();
	virtual void GetCaps(TDes8& aDes) const;
	virtual TInt Create(DLogicalChannelBase*&aChannel);
};

class DHelloLDDChannel: public DLogicalChannelBase
{
		
public:
//	DHelloLDDChannel();
//	virtual ~DHelloLDDChannel();

	//	Inherited from DObject
//	virtual TInt RequestUserHandle(DThread* aThread, TOwnerType aType);
	
	// Inherited from DLogicalChannelBase
	virtual TInt DoCreate(TInt aUnit, const TDesC8* anInfo, const TVersion& aVer);
	
	// Inherited from DLogicalChannel
	//virtual void HandleMsg(TMessageBase* aMsg);

	TInt Request(TInt aReqNo, TAny* a1, TAny* a2);
public:
	DThread* iClient;
	
};
#endif  // __HELLOLDD_H__

