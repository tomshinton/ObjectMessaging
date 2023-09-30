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
	TSharedPtr<FBindingBase> Bind(const TFunction<void(const TEvent&)>& InCallback)
	{
		TSharedPtr<FBindingBase> NewBinding = MakeShareable(new FBinding<TEvent>(InCallback));
		Bindings.Add(NewBinding);
		return NewBinding;
	}

	void Unbind(TSharedPtr<FBindingBase> InBinding)
	{
		Bindings.Remove(InBinding);
	}

	template<typename TEvent>
	void InvokeNewEvent(const TEvent& InEvent)
	{
		for (int32 Index = 0; Index < Bindings.Num(); ++Index)
		{
			if (Bindings.IsValidIndex(Index))
			{
				TSharedPtr<FBindingBase> Binding = Bindings[Index];
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
	}

private:

	TArray<TSharedPtr<FBindingBase>> Bindings;
};

//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------