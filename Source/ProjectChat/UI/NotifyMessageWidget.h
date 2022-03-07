// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NotifyMessageWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class PROJECTCHAT_API UNotifyMessageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetText(const FString& msg) const  { TextBlock->SetText(FText::FromString(msg)); }


private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
	
};
