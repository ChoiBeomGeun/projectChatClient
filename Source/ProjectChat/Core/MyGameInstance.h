// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
class PacketManager;
class UIChatController;
class ASocketActor;
UCLASS()
class PROJECTCHAT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void OnStart() override;
public:

	UIChatController * Controller;
	PacketManager* Packetmanager;
	ASocketActor* SocketActor;
};
