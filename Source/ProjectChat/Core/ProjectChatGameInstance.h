// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectChatGameInstance.generated.h"

/**
 * 
 */
class PacketManager;
class UIChatController;
class ASocketActor;
UCLASS()
class PROJECTCHAT_API UProjectChatGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void OnStart() override;

private:
	UIChatController* Controller = nullptr;
	PacketManager* Packetmanager = nullptr;
	ASocketActor* SocketActor;
};
