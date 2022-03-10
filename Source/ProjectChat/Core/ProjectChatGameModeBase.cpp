// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectChatGameModeBase.h"
#include "ProjectChatGameInstance.h"
AProjectChatGameModeBase::AProjectChatGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	
}

void AProjectChatGameModeBase::StartPlay()
{
	Super::StartPlay();

	PrimaryActorTick.SetTickFunctionEnable(true);

	auto gameInstance = GetWorld()->GetGameInstance();
	UProjectChatGameInstance * GameInstanceRef = Cast<UProjectChatGameInstance>(gameInstance);

	SocketManager = new USocketManager();
	GameInstanceRef->SetPacketManager(SocketManager);
}

void AProjectChatGameModeBase::SetPacketManager(USocketManager* manager)
{
	//PacketManager = MakeUnique<class PacketManager>(*manager);
}

void AProjectChatGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(SocketManager != nullptr) SocketManager->Tick();
}
