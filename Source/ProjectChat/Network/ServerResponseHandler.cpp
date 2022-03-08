// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerResponseHandler.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <string>


#include "../UI/UIChatController.h"
#include <codecvt>
#include <Windows.h>
#include "CommandSet.h"
#include "PacketManager.h"

ServerResponseHandler::ServerResponseHandler()
{
	CommandArrayList.Add(TPair<FString, HandleFunc >(CommandTable::LoginSuccess, HandleFunc(&ServerResponseHandler::OnResponseLogin)));
	CommandArrayList.Add(TPair<FString, HandleFunc >(CommandTable::RoomListItem, HandleFunc(&ServerResponseHandler::OnResponseRoomList)));
	CommandArrayList.Add(TPair<FString, HandleFunc >(CommandTable::EnterRoom, HandleFunc(&ServerResponseHandler::OnResponseRoomEnter)));
}

ServerResponseHandler::~ServerResponseHandler()
{
}

void ServerResponseHandler::HandleServerResponse(const FString& buffer)
{
	if(Controller->IsUserInChatRoom())
	{
		OnResponseChat(buffer);
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
				find->Value(*this, buffer);
			}
		}
	}

}

void ServerResponseHandler::OnResponseLogin(const FString& res)
{
	Controller->RemoveLoginUI();
	Controller->SetMainUI(true);
	Controller->RequestSendRoomList();
}

void ServerResponseHandler::OnResponseRoomList(const FString& res)
{


}

void ServerResponseHandler::OnResponseRoomEnter(const FString& res)
{
	Controller->SetMainUI(false);
	Controller->SetChatUI(true);
	 
	FString roomTitle = res.Mid(res.Find("["), res.Find("]"));


	Controller->SetChatUITitle(roomTitle);
}

void ServerResponseHandler::OnResponseChat(const FString& res)
{
	//escape server command
	if (res.StartsWith("/"))
		return;

	Controller->AddChatListItem(res);
}

TPair<FString, ServerResponseHandler::HandleFunc> * ServerResponseHandler::FindCommand(const FString& command)
{
	for(int i=0 ; i < CommandArrayList.Num(); i++)
	{
		if(command.Contains(CommandArrayList[i].Key) == true)
		{
			return &CommandArrayList[i];
		}
	}

	return nullptr;

}
	