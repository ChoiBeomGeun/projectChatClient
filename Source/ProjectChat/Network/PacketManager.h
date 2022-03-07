// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "CoreMinimal.h"

#include <unordered_map>
/**
 * 
 */
class ASocketActor;
class ServerResponseHandler;
class PROJECTCHAT_API PacketManager
{
public:
	PacketManager();
	~PacketManager();

public:
	//packet section
	void SetServerResponseHandler(ServerResponseHandler * handler);
	void SetConnectedSocket(ASocketActor* socket);
	void ConnectServer(int port, std::function<void(void)> onSuccessAction, std::function<void(void)> onFailAction);
	void SendRoomList();
	void SendLogin(const FString& name);
	void HandleRecv(const FString& buffer);


private:
	TArray<FString> SplitString(char* target, const char* delimiter);
private:
	ASocketActor* CurrentSocket;
	ServerResponseHandler* ResponseHandler;
};
