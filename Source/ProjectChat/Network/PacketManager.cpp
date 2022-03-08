// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketManager.h"

#include "ServerResponseHandler.h"
#include "SocketActor.h"

PacketManager::PacketManager()
{
}

PacketManager::~PacketManager()
{
}

void PacketManager::SetServerResponseHandler(ServerResponseHandler* handler)
{
	ResponseHandler = handler;
}

void PacketManager::SetConnectedSocket(ASocketActor* socket)
{
	CurrentSocket = socket;
}

void PacketManager::ConnectServer(int port, std::function<void(void)> onSuccessAction, std::function<void(void)> onFailAction)
{
	CurrentSocket->ConnectServer(port,onSuccessAction,onFailAction);
}

void PacketManager::SendRoomList()
{
	FString command = TEXT("/rl\r\n");

	CurrentSocket->Send(command);
}

void PacketManager::SendLogin(const FString& name)
{

	FString command = FString::Printf(TEXT("/l %s\r\n"), *name);
	//TEXT("/l %s")
	CurrentSocket->Send(command);
}


void PacketManager::SendCreateRoom(const FString& roomName,int32 maxUserCount)
{
	FString command = FString::Printf(TEXT("/cr %s %d\r\n"), *roomName,maxUserCount);
	//TEXT("/l %s")
	CurrentSocket->Send(command);
}

void PacketManager::SendChat(const FString& msg)
{
	//TEXT("/l %s")
	CurrentSocket->Send(msg);
}

void PacketManager::HandleRecv(const FString & buffer)
{

	ResponseHandler->HandleServerResponse(buffer);




}

TArray<FString> PacketManager::SplitString(char* target, const char* delimiter)
{
	char* context = NULL;
	char* token = strtok_s(target, delimiter, &context);
	TArray<FString> splitStrings;

	while (token != NULL)
	{
		splitStrings.Add(token);
		token = strtok_s(NULL, delimiter, &context);
	}
	return splitStrings;
}
