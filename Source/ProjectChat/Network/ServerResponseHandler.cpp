// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerResponseHandler.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <string>


#include "../UI/UIChatController.h"
#include <codecvt>
#include <Windows.h>
#include "CommandSet.h"
#include "PacketManager.h"

void ServerResponseHandler::RegisterCommands()
{

	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::LoginSuccess, HandleFunc(&ServerResponseHandler::OnResponseLogin)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::RoomListItem, HandleFunc(&ServerResponseHandler::OnResponseRoomList)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::EnterRoom, HandleFunc(&ServerResponseHandler::OnResponseRoomEnter)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::ExitRoom, HandleFunc(&ServerResponseHandler::OnResponseExit)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::UserListItem, HandleFunc(&ServerResponseHandler::OnResponseUserList)));
	CommandArrayList.emplace_back(TPair<FString, HandleFunc >(CommandTable::EnterRoomOtherUser, HandleFunc(&ServerResponseHandler::OnResponseRoomEnterOtherUser)));
}

void ServerResponseHandler::HandleServerResponse(const FString& buffer)
{
	// 귓속말과 다른 상대가 방에 들어왔다는 서버 커맨드를 제외하고 출력한다.
	if(buffer.Contains(CommandTable::EnterRoomOtherUser) == false && buffer.Contains(CommandTable::Whisper) == false && Controller->IsUserInChatRoom())
	{
		OnResponseChat(const_cast<FString&>(buffer));
	}
	else
	{

		//ServerCommand
		if (buffer.StartsWith("/") == false)
		{

		}
		else
		{
			TPair<FString, ServerResponseHandler::HandleFunc>* find = FindCommand(buffer);
			if (find != nullptr)
			{
				if(find->Value) find->Value(*this, buffer);
			}
			else
			{
				Controller->CreateNotifyMessage(buffer);
			}
	
		}
	}

}

void ServerResponseHandler::OnResponseLogin(const FString& res)
{
	Controller->RemoveLoginUI();
	Controller->SetMainUI(true);
	Controller->RequestSendRoomList();
	Controller->RequestUserList();
}

void ServerResponseHandler::OnResponseRoomList(const FString& res)
{
	FString roomInfo = res.Mid(res.Find("["), res.Find("]"));

	Controller->AddRoomListItem(roomInfo);
}

void ServerResponseHandler::OnResponseRoomEnter(const FString& res)
{
	Controller->SetMainUI(false);
	Controller->SetChatUI(true);

	int startIndex = res.Find("[") + 1;
	int endIndex = res.Find("]");
	FString roomTitle = res.Mid(startIndex, endIndex - startIndex);

	Controller->SetChatUITitle(roomTitle);
}

void ServerResponseHandler::OnResponseChat(FString& res)
{
	//escape server command
	if (res.StartsWith("/"))
		return;


	int newLineCount = AddNewLineToLargeString(res,30);

	Controller->AddChatListItem(res, newLineCount);
}

void ServerResponseHandler::OnResponseExit(const FString& res)
{
	Controller->RequestSendRoomList();
	Controller->SetMainUI(true);
	Controller->SetChatUI(false);

}

void ServerResponseHandler::OnResponseWhisper(const FString& res)
{
	Controller->CreateNotifyMessage(res);
}

void ServerResponseHandler::OnResponseUserList(const FString& res)
{
	FString userInfo = res.Mid(res.Find("["), res.Find("]"));

	Controller->AddUserListItem(userInfo);
}

void ServerResponseHandler::OnResponseRoomEnterOtherUser(const FString& res)
{
	int startIndex = res.Find("[") + 1;
	int endIndex = res.Find("]");
	FString roomTitle = res.Mid(startIndex, endIndex - startIndex);
	//FString roomTitle = res.Mid(res.Find("["), res.Find("]"));
	if(Controller->IsUserInChatRoom()) Controller->SetChatUITitle(roomTitle);
}

int ServerResponseHandler::AddNewLineToLargeString(FString& command, int newLineCount)
{
	return 1;
	int curCount = 0;
	int lineCount = 1;
	for(int i =0 ; i < GetNum(command); i++, curCount++)
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

TPair<FString, ServerResponseHandler::HandleFunc> * ServerResponseHandler::FindCommand(const FString& command)
{
	for(int i=0 ; i < CommandArrayList.size(); i++)
	{
		if(command.Contains(CommandArrayList[i].Key) == true)
		{
			return &CommandArrayList[i];
		}
	}

	return nullptr;

}
	