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
	void RegisterCommands();

	void HandleServerResponse(const FString& buffer);

	void OnResponseLogin(const FString& res);
	void OnResponseRoomList(const FString& res);
	void OnResponseRoomEnter(const FString& res);
	void OnResponseChat(FString& res);
	void OnResponseExit(const FString& res);
	void OnResponseWhisper(const FString& res);
	void OnResponseUserList(const FString& res);
	void OnResponseRoomEnterOtherUser(const FString& res);

	void SetController(UIChatController* controller)
	{
		Controller = controller;
	}

private:

	int AddNewLineToLargeString(FString& command,int newLineCount);
	TPair<FString, HandleFunc>* FindCommand(const FString & command);

	UIChatController* Controller;
	std::vector<TPair<FString, HandleFunc>> CommandArrayList;
};


