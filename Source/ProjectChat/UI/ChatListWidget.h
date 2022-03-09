// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ChatListWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
UCLASS()
class PROJECTCHAT_API UChatListWidget : public UViewWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ListTextBlock = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* InvisibleButton = nullptr;

private:
	UFUNCTION()
	void OnClickBtn();
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	FString InfoString;
};
