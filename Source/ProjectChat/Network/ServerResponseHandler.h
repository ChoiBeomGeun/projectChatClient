// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"

#include <functional>
#include <unordered_map>

class UIChatController;
class PROJECTCHAT_API ServerResponseHandler
{
	using HandleFunc = std::function<void(ServerResponseHandler&, const FString&)>;
public:
	ServerResponseHandler();
	~ServerResponseHandler();

	void HandleServerResponse(const FString& buffer);

	void OnResponseLogin(const FString& res);
	void OnResponseRoomList(const FString& res);
	void OnResponseRoomEnter(const FString& res);
	void OnResponseChat(const FString& res);

	void SetController(UIChatController* controller)
	{
		Controller = controller;
	}

private:

	TPair<FString, HandleFunc>* FindCommand(const FString & command);

	UIChatController* Controller;
	TArray<TPair<FString, HandleFunc>> CommandArrayList;
};
