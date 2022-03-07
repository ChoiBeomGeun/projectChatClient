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
class PROJECTCHAT_API UIChatController
{
public:
	UIChatController();
	~UIChatController();
	void SetPacketManager(PacketManager* packetManager);
	void SetWorld(UWorld * world);
	//CreateViewSection
	void CreateLoginView();
	void CreateMainView();
	void CreateNotifyMessage(const FString & msg);
	void CreateRoomList();
	void HideLoginUI();

	void RequestSendLogin(const FString& name);
	void RequestConnectServer(int port, std::function<void(void)> onSuccessAction, std::function<void(void)> onFailAction);

private:

	UWorld* CachedWorld;

private:
	PacketManager* Packetmanager;
	//views
private:
	ULoginUI* LoginView;
	UMainScreenUIWidget* MainView;
};
