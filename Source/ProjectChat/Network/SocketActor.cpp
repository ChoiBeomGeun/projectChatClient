// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketActor.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Packetmanager.h"
#include <codecvt>
#include <Windows.h>
#include <wchar.h>
// Sets default values
ASocketActor::ASocketActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;

}

void ASocketActor::SetPacketManager(PacketManager* packetManager)
{
	Packetmanager = packetManager;
}

void ASocketActor::ConnectServer(int port, std::function<void(void)> successAction, std::function<void(void)> onFailAction)
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));

	IsConnected = Socket->Connect(*addr);


	if(IsConnected == true)
	{
		int newSize;
		Socket->SetReceiveBufferSize(2048, newSize);
		successAction();
	}
	else
	{
		onFailAction();
	}

}

// Called every frame
void ASocketActor::Tick(float DeltaTime)
{
	if (IsConnected == false)
	{
		return;
	}

	uint32 pendingSize = 0;

	if (Socket->HasPendingData(pendingSize))
	{
		int recvByte = 0;
		bool isReceived = Socket->Recv(Buffer + recvByte, BUFFER_SIZE-RecvBytes, recvByte);

		if (isReceived)
		{
			RecvBytes += recvByte;

			char* str = reinterpret_cast<char*>(Buffer);
			wchar_t* pStr;
			int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
			pStr = new WCHAR[strSize];
			MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);

			std::string strValue = std::string(str);

			if(strValue.find("\r\n"	) == false)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));
			}
			else
			{
				if(pStr == nullptr)
				{
					InitBuffer();
					return;
				}
				else
				{
					TArray<FString> splitResult = SplitString(pStr, L"\r\n");
					for (int i = 0; i < splitResult.Num(); i++)
					{
						Packetmanager->HandleRecv(splitResult[i]);
					}
					delete pStr;
					InitBuffer();
				}
			}
		}

	}
}

void ASocketActor::Send(const FString& string)
{
	wchar_t* strUnicode = const_cast<wchar_t*>(ToCStr(string));
	char* strMultibyte = new char[GetNum(string)];
	int len = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strMultibyte, len, NULL, NULL);
	int sendBytes = 0;

	if (strMultibyte == nullptr)
	{
		InitBuffer();
		return;
	}
	else
	{
		if (Socket->Send(reinterpret_cast<uint8*>(strMultibyte), len, sendBytes))
		{

		}

		delete strMultibyte;
	}
}
TArray<FString> ASocketActor::SplitString(wchar_t* target, const wchar_t* delimiter)
{
	wchar_t* token = wcstok(target, delimiter);

	TArray<FString> splitStrings;

	while (token != NULL)
	{
		splitStrings.Add(token);
		token = wcstok(NULL, delimiter);
	}
	return splitStrings;
}
void ASocketActor::InitBuffer()
{
	memset(Buffer, 0, 2048);
	RecvBytes = 0;
}

