// ObjectMessaging - Tom Shinton 2020

#include "ObjectMessaging/Public/ObjectMessaging.h"

#define LOCTEXT_NAMESPACE "FObjectMessagingModule"

//-----------------------------------------------------------------------------------------------

DEFINE_LOG_CATEGORY_STATIC(ObjectMessagingModuleLog, Log, Log)

//-----------------------------------------------------------------------------------------------

void FObjectMessagingModule::StartupModule()
{
	UE_LOG(ObjectMessagingModuleLog, Log, TEXT("Spinning up ObjectMessaging Plugin"));
}

//-----------------------------------------------------------------------------------------------

void FObjectMessagingModule::ShutdownModule()
{
	UE_LOG(ObjectMessagingModuleLog, Log, TEXT("Shutting down ObjectMessaging Plugin"));
}

//-----------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE

//-----------------------------------------------------------------------------------------------

IMPLEMENT_MODULE(FObjectMessagingModule, ObjectMessaging)

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------