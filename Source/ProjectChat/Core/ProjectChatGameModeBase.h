// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectChat/Network/SocketManager.h"
#include "ProjectChatGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCHAT_API AProjectChatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	AProjectChatGameModeBase();
	virtual void StartPlay() override;
public:
	void SetPacketManager(USocketManager* manager);

private:
	virtual void Tick(float DeltaSeconds) override;
	USocketManager* SocketManager = nullptr;
	
};
