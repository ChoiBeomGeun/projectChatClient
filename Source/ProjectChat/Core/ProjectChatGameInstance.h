// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectChatGameInstance.generated.h"

/**
 * 
 */
class USocketManager;
class UUIChatController;
class ASocketActor;
UCLASS()
class PROJECTCHAT_API UProjectChatGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void OnStart() override;
public:
	void SetPacketManager(USocketManager* packetManager);
	USocketManager* GetPacketManager();
private:
	UUIChatController* Controller = nullptr;
	USocketManager* SocketManager = nullptr;
};
