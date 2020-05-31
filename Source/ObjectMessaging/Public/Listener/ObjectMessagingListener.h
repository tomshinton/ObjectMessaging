// ObjectMessaging - Tom Shinton 2020

#pragma once

#include <Runtime/Core/Public/Templates/SharedPointer.h>

//-----------------------------------------------------------------------------------------------

DEFINE_LOG_CATEGORY_STATIC(ObjectMessagingListenerLog, Log, Log)

//-----------------------------------------------------------------------------------------------

class FBindingBase
{
public:

	virtual bool ShouldExecute(const UScriptStruct& InStructType) = 0;
	virtual void Execute(const void* InData) = 0;
	virtual ~FBindingBase() {};
};

//-----------------------------------------------------------------------------------------------

template<typename TEvent>
class FBinding : public FBindingBase
{
public:

	FBinding(const TFunction<void(const TEvent&)>& InCallback)
		: Callback(InCallback)
		, BindingType(TEvent::StaticStruct())
	{};

	~FBinding()
	{

	};

	bool ShouldExecute(const UScriptStruct& InStructType) override
	{
		return BindingType == &InStructType;
	}

	void Execute(const void* InData) override
	{
		if (Callback != nullptr && InData != nullptr)
		{
			if (const TEvent* TypedData = (TEvent*)InData)
			{
				Callback(*TypedData);
			}
		}
	}

private:

	TFunction<void(const TEvent&)> Callback;
	const UScriptStruct* BindingType;
};

//-----------------------------------------------------------------------------------------------

class FObjectMessagingListener
{
public:

	FObjectMessagingListener()
	{};

	~FObjectMessagingListener()
	{
		Bindings.Reset();
	};

	template<typename TEvent>
	void Bind(const TFunction<void(const TEvent&)>& InCallback)
	{
		Bindings.Add(MakeShareable(new FBinding<TEvent>(InCallback)));
	}

	template<typename TEvent>
	void InvokeNewEvent(const TEvent& InEvent)
	{
		for (TSharedPtr<FBindingBase> Binding : Bindings)
		{
			if (Binding.IsValid())
			{
				if (Binding->ShouldExecute(*TEvent::StaticStruct()))
				{
					if (const void* DataRaw = &InEvent)
					{
						Binding->Execute(DataRaw);
					}
				}
			}
			else
			{
				UE_LOG(ObjectMessagingListenerLog, Error, TEXT("Could not invoke function - binding is invalid!"));
			}
		}
	}

private:

	TArray<TSharedPtr<FBindingBase>> Bindings;
};

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------