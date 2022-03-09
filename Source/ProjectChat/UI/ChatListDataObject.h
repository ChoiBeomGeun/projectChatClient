// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatRoomWidget.h"
#include "UObject/NoExportTypes.h"
#include "ChatListDataObject.generated.h"

/**
 * 
 */
class UUIChatController;
UCLASS()
class PROJECTCHAT_API UChatListDataObject : public UObject
{
	GENERATED_BODY()


public:
	FString value;
	int lineCount;
	bool IsClientMsg = false;
	bool IsChatMsg = false;
	UUIChatController* Controller;
};
