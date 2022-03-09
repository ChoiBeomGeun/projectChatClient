// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectChat/Network/SocketManager.h"
#include "UObject/NoExportTypes.h"
#include "UIChatController.generated.h"

class ASocketActor;
class ULoginUI;
class UMainScreenUIWidget;
class UChatRoomWidget;
UCLASS()
class PROJECTCHAT_API UUIChatController : public UObject
{
	GENERATED_BODY()
public:

	UUIChatController();
	~UUIChatController();
	void SetPacketManager(USocketManager packetManager);
	void SetWorld(UWorld* world);
	void SetName(const FString* name);

	void CreateLoginView();
	void CreateMainView();
	void CreateChatView();
	void CreateNotifyMessage(const FString& msg);
	void CreateRoomList();

	void RemoveLoginUI();
	void SetMainUI(bool isActive);
	void SetChatUI(bool isActive);
	void SetChatUITitle(const FString& title);
	void SetWhisperUser(const FString& name);

	void AddRoomListItem(const FString& name);
	void AddChatListItem(const FString& name, int newLineCount);
	void AddUserListItem(const FString& name);



	void RequestSendLogin(const FString& name);
	void RequestConnectServer(int port, TFunction<void(void)> onSuccessAction, TFunction<void(void)> onFailAction);
	void RequestSendRoomList();
	void RequestCreateRoom(const FString& roomName, int32 maxUserCount);
	void RequestChat(const FString& msg);
	void RequestExitRoom();
	void RequestEnterRoom(int index);
	void RequestUserList();
	void RequestWhisper(const FString& msg, const FString& name);

	bool IsUserInChatRoom();
private:

	USocketManager* GetPacketmanager();
	bool IsUserIn = false;
	UWorld* CachedWorld;
	FString playerName;
private:

	ULoginUI* LoginView = nullptr;
	UMainScreenUIWidget* MainView = nullptr;
	UChatRoomWidget* ChatView = nullptr;
};
