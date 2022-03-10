﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerResponseHandler.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <string>


#include "../UI/UIChatController.h"
#include <codecvt>
#include <Windows.h>
#include "ProjectChat/Network/CommandSet.h"

void UServerResponseHandler::RegisterCommands()
{
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::LoginSuccess, HandleFunc(&UServerResponseHandler::OnResponseLogin)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::RoomListItem, HandleFunc(&UServerResponseHandler::OnResponseRoomList)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::EnterRoom, HandleFunc(&UServerResponseHandler::OnResponseRoomEnter)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::ExitRoom, HandleFunc(&UServerResponseHandler::OnResponseExit)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::UserListItem, HandleFunc(&UServerResponseHandler::OnResponseUserList)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::EnterRoomOtherUser, HandleFunc(&UServerResponseHandler::OnResponseRoomEnterOtherUser)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::InviteRequest, HandleFunc(&UServerResponseHandler::OnResponseInviteRequest)));
}

void UServerResponseHandler::HandleServerResponse(const FString& buffer)
{
	// 귓속말과 다른 상대가 방에 들어왔다는 서버 커맨드를 제외하고 출력한다.
	if (buffer.Contains(CommandTable::EnterRoomOtherUser) == false
		&& buffer.Contains(CommandTable::Whisper) == false
		&& buffer.Contains(CommandTable::UserListItem) == false
		&& buffer.Contains(CommandTable::InviteRequest) == false
		&& Controller->IsUserInChatRoom())
	{
		OnResponseChat(const_cast<FString&>(buffer));
	}
	else
	{

		//ServerCommand
		if (buffer.StartsWith("/") == true)
		{
			TPair<FString, UServerResponseHandler::HandleFunc>* find = FindCommand(buffer);
			if (find != nullptr)
			{
				if (find->Value) find->Value(*this, buffer);
			}
			else
			{
				Controller->CreateNotifyMessage(buffer);
			}

		}
	}

}

void UServerResponseHandler::OnResponseLogin(const FString& res)
{
	Controller->RemoveLoginUI();
	Controller->SetMainUI(true);
	Controller->PlayMainAppearAnim();
	Controller->RequestSendRoomList();
	Controller->RequestUserList();
}

void UServerResponseHandler::OnResponseRoomList(const FString& res)
{
	FString findText = TEXT("방 이름 :");
	int startIndex = res.Find(findText) + GetNum(findText);
	int endIndex = res.Find(",");
	FString roomTitle = res.Mid(startIndex, endIndex - startIndex) + "\n";

	startIndex = res.Find("(") + 1;
	endIndex = res.Find(")");

	FString userCount = res.Mid(startIndex, endIndex - startIndex);

	Controller->AddRoomListItem(roomTitle + userCount);
}

void UServerResponseHandler::OnResponseRoomEnter(const FString& res)
{
	Controller->SetMainUI(false);
	Controller->SetChatUI(true);

	int startIndex = res.Find("[") + 1;
	int endIndex = res.Find("]");
	FString roomTitle = res.Mid(startIndex, endIndex - startIndex);

	Controller->SetChatUITitle(roomTitle);
}

void UServerResponseHandler::OnResponseChat(FString& res)
{
	//escape server command
	if (res.StartsWith("/"))
		return;


	int newLineCount = AddNewLineToLargeString(res, 30);

	Controller->AddChatListItem(res, newLineCount);
}

void UServerResponseHandler::OnResponseExit(const FString& res)
{
	Controller->RequestSendRoomList();
	Controller->SetMainUI(true);
	Controller->SetChatUI(false);

}

void UServerResponseHandler::OnResponseWhisper(const FString& res)
{
	Controller->CreateNotifyMessage(res);
}

void UServerResponseHandler::OnResponseUserList(const FString& res)
{
	FString userInfo = res.Mid(res.Find("["), res.Find("]"));

	Controller->AddUserListItem(userInfo);
}

void UServerResponseHandler::OnResponseRoomEnterOtherUser(const FString& res)
{
	int startIndex = res.Find("[") + 1;
	int endIndex = res.Find("]");
	FString roomTitle = res.Mid(startIndex, endIndex - startIndex);
	//FString roomTitle = res.Mid(res.Find("["), res.Find("]"));
	if (Controller->IsUserInChatRoom()) Controller->SetChatUITitle(roomTitle);
}

void UServerResponseHandler::OnResponseInviteRequest(const FString& res)
{
	int startIndex = res.Find("[") + 1;
	int endIndex = res.Find("]");
	FString roomNumber = res.Mid(startIndex, endIndex - startIndex);

	Controller->CreateInviteMessage(res, FCString::Atoi(*roomNumber));
}

int UServerResponseHandler::AddNewLineToLargeString(FString& command, int newLineCount)
{
	return 1;
	int curCount = 0;
	int lineCount = 1;
	for (int i = 0; i < GetNum(command); i++, curCount++)
	{
		if (curCount == newLineCount)
		{
			lineCount++;
			command.InsertAt(i, '\n');
			curCount = 0;
		}
	}
	return lineCount;
}

TPair<FString, UServerResponseHandler::HandleFunc>* UServerResponseHandler::FindCommand(const FString& command)
{
	for (int i = 0; i < CommandArrayList.size(); i++)
	{
		if (command.Contains(CommandArrayList[i].Key) == true)
		{
			return &CommandArrayList[i];
		}
	}

	return nullptr;

}
