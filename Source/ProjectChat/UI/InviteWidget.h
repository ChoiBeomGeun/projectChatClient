// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewWidget.h"
#include "Blueprint/UserWidget.h"
#include "InviteWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECTCHAT_API UInviteWidget : public UViewWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DesTextBlock = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* OkButton = nullptr;

	UFUNCTION()
	void OnClickOk();

public:
	void SetTextBox(const FString& msg);

public:
	int32 InviteRoomNumber;
};

