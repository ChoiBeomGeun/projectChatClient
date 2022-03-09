// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatRoomWidget.h"
#include "UObject/NoExportTypes.h"
#include "ChatListDataObject.generated.h"

/**
 * 
 */
class UIChatController;
UCLASS()
class PROJECTCHAT_API UChatListDataObject : public UObject
{
	GENERATED_BODY()


public:
	FString value;
	int lineCount;
	UIChatController* Controller;
};
