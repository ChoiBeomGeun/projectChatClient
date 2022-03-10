// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <unordered_map>
#include "UObject/NoExportTypes.h"


class UUIChatController;
/**
 * 
 */

class PROJECTCHAT_API UServerResponseHandler 
{

	using HandleFunc = TFunction<void(UServerResponseHandler&, const FString&)>;
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
	void OnResponseInviteRequest(const FString& res);

	void SetController(UUIChatController* controller)
	{
		Controller = controller;
	}

private:

	int AddNewLineToLargeString(FString& command, int newLineCount);
	TPair<FString, HandleFunc>* FindCommand(const FString& command);

	UUIChatController* Controller;
	std::vector<TPair<FString, HandleFunc>> CommandArrayList;
};
