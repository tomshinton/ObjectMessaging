// ObjectMessaging - Tom Shinton 2020

#pragma once

#include "ObjectMessaging/Public/Listener/ObjectMessagingListenerInterface.h"

#include <Runtime/CoreUObject/Public/UObject/WeakInterfacePtr.h>

//-----------------------------------------------------------------------------------------------

namespace ObjectMessagingFunctions
{
	template<typename TEvent>
	static void SendMessage(const TWeakInterfacePtr<IObjectMessagingListenerInterface>& InRecipient, const TEvent& InEvent)
	{
		InRecipient->GetListener().InvokeNewEvent<TEvent>(InEvent);
	};
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------