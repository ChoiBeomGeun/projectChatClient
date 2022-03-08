// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "CoreMinimal.h"

/**
 * 
 */
class ASocketActor;
class PacketManager;
class ULoginUI;
class UMainScreenUIWidget;
class UChatRoomWidget;
class PROJECTCHAT_API UIChatController
{
public:
	UIChatController();
	~UIChatController();
	void SetPacketManager(PacketManager* packetManager);
	void SetWorld(UWorld * world);

	void CreateLoginView();
	void CreateMainView();
	void CreateChatView();
	void CreateNotifyMessage(const FString & msg);
	void CreateRoomList();

	void RemoveLoginUI();
	void SetMainUI(bool isActive);
	void SetChatUI(bool isActive);
	void SetChatUITitle(const FString& title);

	void AddRoomListItem(const FString& name);
	void AddChatListItem(const FString& name);

	void RequestSendLogin(const FString& name);
	void RequestConnectServer(int port, std::function<void(void)> onSuccessAction, std::function<void(void)> onFailAction);
	void RequestSendRoomList();
	void RequestCreateRoom(const FString & roomName, int32 maxUserCount);
	void RequestChat(const FString& msg);

	bool IsUserInChatRoom();
private:

	UWorld* CachedWorld;

private:
	PacketManager* Packetmanager;
	//views
private:
	ULoginUI* LoginView = nullptr;
	UMainScreenUIWidget* MainView = nullptr;
	UChatRoomWidget* ChatView = nullptr;
};
