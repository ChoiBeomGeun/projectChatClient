// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectChatGameInstance.h"

#include <string>

#include "ProjectChatGameModeBase.h"
#include  "Runtime/Networking/Public/Networking.h"
#include "../UI/UIChatController.h"
#include "../Network/SocketManager.h"
#include "../UI/ServerResponseHandler.h"
#include "Kismet/GameplayStatics.h"

void UProjectChatGameInstance::OnStart()
{
	Super::OnStart();

}

void UProjectChatGameInstance::SetPacketManager(USocketManager* packetManager)
{
	Controller = NewObject<UUIChatController>();
	Controller->SetWorld(GetWorld());
	Controller->CreateMainView();
	Controller->CreateLoginView();
	Controller->CreateChatView();

	UServerResponseHandler* responseHandler = NewObject<UServerResponseHandler>();
	responseHandler->RegisterCommands();
	responseHandler->SetController(Controller);
	SocketManager = packetManager;
	SocketManager->SetServerResponseHandler(responseHandler);

}

USocketManager* UProjectChatGameInstance::GetPacketManager()
{
	return SocketManager;
}
