// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "RoomListWidget.generated.h"

class UButton;
class UTextBlock;
UCLASS()
class PROJECTCHAT_API URoomListWidget : public UViewWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ListTextBlock = nullptr;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* RoomButton = nullptr;
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	void OnClickRoom();
private:
	int Index;
};
