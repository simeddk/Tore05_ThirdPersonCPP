#pragma once

#include "CoreMinimal.h"

#define CheckNull(p) { if (p == nullptr) return; }
#define CheckNullResult(p, result) { if (p == nullptr) return result; }

#define CheckTrue(p) { if (p == true) return; }
#define CheckTrueResult(p, result) { if (p == true) return result; }

#define CheckFalse(p) { if (p == false) return; }
#define CheckFalseResult(p, result) { if (p == false) return result; }


class THIRDPERSONCPP_API CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutAsset, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*InPath);
		ensureMsgf(Asset.Succeeded(), TEXT("Asset Not Found"));

		*OutAsset = Asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutAsset, FString InPath)
	{
		T* Object = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
		ensureMsgf(Object, TEXT("Asset Not Found(Dynamic)"));

		*OutAsset = Object;
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> Class(*InPath);
		ensureMsgf(Class.Succeeded(), TEXT("Class Not Found"));

		*OutClass = Class.Class;
	}

	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static void CreateSceneComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = nullptr)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
		
		if (InParent)
		{
			(*OutComponent)->SetupAttachment(InParent);
			return;
		}
		
		InActor->SetRootComponent(*OutComponent);
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
	}
};