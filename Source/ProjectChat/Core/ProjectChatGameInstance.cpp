// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectChatGameInstance.h"

#include <string>

#include  "Runtime/Networking/Public/Networking.h"
#include "../UI/UIChatController.h"
#include "../Network/SocketActor.h"
#include "../Network/PacketManager.h"
#include "../Network/ServerResponseHandler.h"

void UProjectChatGameInstance::OnStart()
{
	Super::OnStart();

	Controller = new UIChatController();
	Packetmanager = new PacketManager();
	ServerResponseHandler* responseHandler = new ServerResponseHandler();

	Controller->SetWorld(GetWorld());
	Controller->CreateMainView();
	Controller->CreateLoginView();
	Controller->CreateChatView();

	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	SocketActor = GetWorld()->SpawnActor<ASocketActor>(Location, Rotation, SpawnInfo);

	responseHandler->SetController(Controller);
	Packetmanager->SetServerResponseHandler(responseHandler);
	Packetmanager->SetConnectedSocket(SocketActor);
	SocketActor->SetPacketManager(Packetmanager);
	Controller->SetPacketManager(Packetmanager);

	responseHandler->RegisterCommands();
}
