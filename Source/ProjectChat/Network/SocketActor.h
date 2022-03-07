// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SocketActor.generated.h"

class PacketManager;
UCLASS()
class PROJECTCHAT_API ASocketActor : public AActor
{
	GENERATED_BODY()

public:
	FSocket* Socket;
	// Sets default values for this actor's properties
	ASocketActor();
	void SetPacketManager(PacketManager* packetManager);
	void ConnectServer(int port, std::function<void(void)> successAction, std::function<void(void)> onFailAction);

public:	
	// Called every frame 
	virtual void Tick(float DeltaTime) override;

	void Send(const FString& string);
	TArray<FString> SplitString(wchar_t* target, const wchar_t* delimiter);
private:
	PacketManager * Packetmanager;
	uint8 Buffer[2048] = { 0 };
	bool IsConnected = false;
};
