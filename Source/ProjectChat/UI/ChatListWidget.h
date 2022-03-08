// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "ChatListWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class PROJECTCHAT_API UChatListWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ListTextBlock = nullptr;

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
