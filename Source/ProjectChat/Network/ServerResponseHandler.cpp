// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerResponseHandler.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include <string>


#include "../UI/UIChatController.h"
#include <codecvt>
#include <Windows.h>

ServerResponseHandler::ServerResponseHandler()
{

	CommandMap.Add(TEXT("------------------------로그인에 성공하셨습니다!"), HandleFunc(&ServerResponseHandler::OnResponseLogin));
}

ServerResponseHandler::~ServerResponseHandler()
{
}

void ServerResponseHandler::HandleServerResponse(const FString& buffer)
{

		

	auto find = CommandMap.Find(buffer);

	if (find == nullptr)
		return;
	(*find)(*this, buffer);
}

void ServerResponseHandler::OnResponseLogin(const FString& res)
{

	Controller->HideLoginUI();
	Controller->CreateMainView();

}
	