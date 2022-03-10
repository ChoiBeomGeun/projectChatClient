// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketManager.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "../Network/ServerResponseHandler.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

#include <codecvt>
#include <Windows.h>
#include <wchar.h>

USocketManager::USocketManager()
{
}

USocketManager::~USocketManager()
{
	Socket->Close();
	IsConnected = false;
}

void USocketManager::SetServerResponseHandler(UServerResponseHandler* handler)
{
	ResponseHandler = handler;
}

void USocketManager::ConnectServer(int port, TFunction<void(void)> onSuccessAction, TFunction<void(void)> onFailAction)
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	IsConnected = Socket->Connect(*addr);

	if (IsConnected == true)
	{
		int newSize;
		Socket->SetReceiveBufferSize(BUFFER_SIZE, newSize);
		onSuccessAction();
	}
	else
	{
		Socket = nullptr;
		onFailAction();
	}

}

void USocketManager::Send(const FString& string)
{
	wchar_t* strUnicode = const_cast<wchar_t*>(ToCStr(string));
	char* strMultibyte = new char[GetNum(string)];

	int len = WideCharToMBT(strMultibyte, strUnicode);
	int sendBytes = 0;
	if (strMultibyte == nullptr)
	{
		InitBuffer();
		return;
	}
	else
	{
		uint8 sendBuffer[BUFFER_SIZE];
		int32 convBytes = StringToBytes(strMultibyte, sendBuffer, BUFFER_SIZE);
		if (Socket->Send(reinterpret_cast<uint8*>(strMultibyte), len, sendBytes))
		{

		}

		delete strMultibyte;
	}
}

void USocketManager::Tick()
{
	uint32 pendingSize = 0;
	if (IsConnected == false || !(Socket->HasPendingData(pendingSize)))
	{
		return;
	}

	int curRecvBytes = 0;
	bool isReceived = Socket->Recv(Buffer + RecvBytes, BUFFER_SIZE - RecvBytes, curRecvBytes);

	if (isReceived)
	{
		RecvBytes += curRecvBytes;


		wchar_t* pStr = MBTtoWideChar(Buffer);

		const FString& bufferToString = pStr;

		if (pStr != nullptr)
		{
			TArray<FString> lines;

			bufferToString.ParseIntoArray(lines, TEXT("\r\n"));

			for (const FString& line : lines)
			{
				HandleRecv(line);
			}

			delete pStr;
			InitBuffer();
		}
		else
		{
			InitBuffer();
		}


	}
	
}

void USocketManager::SendRoomList()
{
	FString command = TEXT("/rl\r\n");
	Send(command);
}

void USocketManager::SendLogin(const FString& name)
{
	FString command = FString::Printf(TEXT("/l %s\r\n"), *name);
	Send(command);
}


void USocketManager::SendCreateRoom(const FString& roomName, int32 maxUserCount)
{
	FString command = FString::Printf(TEXT("/cr %s %d\r\n"), *roomName, maxUserCount);
	Send(command);
}

void USocketManager::SendChat(const FString& msg)
{
	Send(msg);
}

void USocketManager::SendExitRoom()
{
	FString command = FString(TEXT("/exit\r\n"));
	Send(command);
}

void USocketManager::SendEnterRoom(int index)
{
	FString command = FString::Printf(TEXT("/er %d\r\n"), index);
	Send(command);
}


void USocketManager::SendUserList()
{
	FString command = FString(TEXT("/ul\r\n"));
	Send(command);
}

void USocketManager::SendWhispher(const FString& msg, const FString& name)
{
	FString command = FString::Printf(TEXT("/w %s %s\r\n"), *name, *msg);
	Send(command);
}

void USocketManager::SendInvite(const FString& name)
{
	FString command = FString::Printf(TEXT("/i %s \r\n"), *name);
	Send(command);
}


void USocketManager::HandleRecv(const FString& buffer)
{
	ResponseHandler->HandleServerResponse(buffer);
}

wchar_t* USocketManager::MBTtoWideChar(uint8* from)
{
	char* cFrom = reinterpret_cast<char*>(from);
	int strSize = MultiByteToWideChar(CP_ACP, 0, cFrom, -1, NULL, NULL);
	wchar_t* to = new WCHAR[strSize];
	MultiByteToWideChar(CP_ACP, 0, cFrom, strlen(cFrom) + 1, to, strSize);
	return to;
}

int USocketManager::WideCharToMBT(char* to, wchar_t* from)
{
	int len = WideCharToMultiByte(CP_ACP, 0, from, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, from, -1, to, len, NULL, NULL);
	return len;
}

void USocketManager::InitBuffer()
{
	memset(Buffer, 0, BUFFER_SIZE);
	RecvBytes = 0;
}