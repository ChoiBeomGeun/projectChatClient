// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIChatController.h"
#include "Blueprint/UserWidget.h"
#include "ViewWidget.generated.h"

class UUIChatController;
/**
 * 
 */
UCLASS()
class PROJECTCHAT_API UViewWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetController(UUIChatController* controller)
	{
		ChatController = controller;
	}
protected:
	UUIChatController* ChatController = nullptr;
};
