// No Copyright.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraAttributeInfoConfig.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "Attribute"))
	FGameplayTag AttributeTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();
	
	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
	
	bool IsValid() const
	{
		return AttributeTag.IsValid() && !AttributeName.IsEmpty();
	}
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeInfoConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttributeInfoConfig", meta = (TitleProperty = "AttributeName"))
	TArray<FAuraAttributeInfo> AttributeInfos;
	
	FAuraAttributeInfo FindAttributeInfoByTag(const FGameplayTag& InAttributeTag, bool bLogNotFound = false) const;
};
