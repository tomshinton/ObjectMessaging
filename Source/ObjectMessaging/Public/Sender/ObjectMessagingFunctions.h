// ObjectMessaging - Tom Shinton 2020

#pragma once

#include "ObjectMessaging/Public/Listener/ObjectMessagingListenerInterface.h"

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>

DEFINE_LOG_CATEGORY_STATIC(ObjectMessagingFunctionsLog, Log, Log)

//-----------------------------------------------------------------------------------------------

namespace ObjectMessagingFunctions
{
	template<typename TEvent>
	static void SendMessage(const TWeakInterfacePtr<IObjectMessagingListenerInterface>& InRecipient, const TEvent& InEvent)
	{
		InRecipient->GetListener().InvokeNewEvent<TEvent>(InEvent);
	};

	template<typename TEvent>
	static void SendMessage(UObject& InRecievingObject, const TEvent& InEvent)
	{
		if (IObjectMessagingListenerInterface* ObjectMessagingListenerInterface = Cast<IObjectMessagingListenerInterface>(&InRecievingObject))
		{
			ObjectMessagingListenerInterface->GetListener().InvokeNewEvent<TEvent>(InEvent);
		}
		else
		{
			UE_LOG(ObjectMessagingFunctionsLog, Warning, TEXT("%s does not implement an Object Message Listener - cannot send message"), *InRecievingObject.GetName());
		}
	}
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------