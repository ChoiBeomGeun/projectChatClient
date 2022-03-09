// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UIChatController.h"
#include "UObject/NoExportTypes.h"
#include "RoomListDataObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCHAT_API URoomListDataObject : public UObject
{
	GENERATED_BODY()

public:
	FString value;
	int Index;
	UIChatController* ChatController;
};
