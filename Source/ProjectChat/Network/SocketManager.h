// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


/**
 * 
 */
class UServerResponseHandler;

class PROJECTCHAT_API USocketManager
{
	
	enum { BUFFER_SIZE = 2048 };
public:
	USocketManager();
	~USocketManager();

public:
	//packet section
	void SetServerResponseHandler(UServerResponseHandler* handler);

	void ConnectServer(int port, TFunction<void(void)> onSuccessAction, TFunction<void(void)> onFailAction);
	void Send(const FString& string);

	void Tick();

	void SendRoomList();
	void SendLogin(const FString& name);
	void SendCreateRoom(const FString& roomName, int32 maxUserCount);
	void SendChat(const FString& msg);
	void SendExitRoom();
	void SendEnterRoom(int index);
	void SendUserList();
	void SendWhispher(const FString& msg, const FString& name);
	void SendInvite(const FString& name);
	void HandleRecv(const FString& buffer);

	wchar_t* MBTtoWideChar(uint8* from);
	int WideCharToMBT(char* from, wchar_t* to);
private:

	void InitBuffer();
private:
	FSocket* Socket;
	bool IsConnected = false;
	uint8 Buffer[BUFFER_SIZE] = { 0 };
	int RecvBytes = 0;
	UServerResponseHandler* ResponseHandler;
};
