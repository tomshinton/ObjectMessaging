// ObjectMessaging - Tom Shinton 2020

#pragma once

#include <Runtime/CoreUObject/Public/UObject/Interface.h>
#include "ObjectMessaging/Public/Listener/ObjectMessagingListener.h"

#include "ObjectMessagingListenerInterface.generated.h"

//-----------------------------------------------------------------------------------------------

UINTERFACE(MinimalAPI)
class UObjectMessagingListenerInterface : public UInterface
{
	GENERATED_BODY()
};

//-----------------------------------------------------------------------------------------------

class IObjectMessagingListenerInterface
{
	GENERATED_BODY()

public:

	OBJECTMESSAGING_API virtual FObjectMessagingListener& GetListener() = 0;
};

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------