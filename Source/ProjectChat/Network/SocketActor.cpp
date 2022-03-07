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
	Super::BeginPlay();

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

	uint32 DataSize = 0;
	int32 DataLen = 0;
	//uint8 Buffer[2048] = { 0 };

	if (Socket->HasPendingData(DataSize))
	{

		if (Socket->Recv(Buffer, sizeof(Buffer) - 1, DataLen))
		{
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
		

				TArray<FString> splitResult= SplitString(pStr, L"\r\n");
				for (int i = 0; i < splitResult.Num(); i++)
				{
					Packetmanager->HandleRecv(splitResult[i]);
				}

				memset(Buffer, 0, 2048);
			}
		}

	}
}

void ASocketActor::Send(const FString& string)
{
	char* result = TCHAR_TO_ANSI(*string);
	int sendBytes = 0;
	if (Socket->Send(reinterpret_cast<uint8*>(result),string.Len() ,sendBytes))
	{

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


