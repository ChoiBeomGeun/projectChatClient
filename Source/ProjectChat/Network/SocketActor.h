// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame 
	virtual void Tick(float DeltaTime) override;

	void Send(const FString& string);
	TArray<FString> SplitString(wchar_t* target, const wchar_t* delimiter);
private:
	PacketManager * Packetmanager;
	uint8 Buffer[2048] = { 0 };
};
