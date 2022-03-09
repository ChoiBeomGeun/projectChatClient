// Fill out your copyright notice in the Description page of Project Settings.
#include "UIChatController.h"
#include "ViewWidget.h"
#include "NotifyMessageWidget.h"
#include "../Network/SocketManager.h"
#include "../UI/LoginUI.h"
#include "../UI/MainScreenUIWidget.h"
#include "../UI/ChatRoomWidget.h"
#include "ProjectChat/Core/ProjectChatGameInstance.h"

UUIChatController::UUIChatController()
{
	LoginView = nullptr;
	MainView = nullptr;
	ChatView = nullptr;
}

UUIChatController::~UUIChatController()
{
}

void UUIChatController::SetWorld(UWorld* world)
{
	CachedWorld = world;
}

void UUIChatController::SetName(const FString* name)
{

}

//=================================================================================================
// @brief 로그인 뷰 생성
//=================================================================================================
void UUIChatController::CreateLoginView()
{
	if (LoginView != nullptr)
	{
		return;
	}
	UBlueprintGeneratedClass* loginBluePrint = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/LoginUI.LoginUI_C'"));

	UClass* chatWidget;
	chatWidget = Cast<UClass>(loginBluePrint);

	auto widget = CreateWidget(CachedWorld, chatWidget);

	ULoginUI* loginUI = Cast<ULoginUI>(widget);

	if (loginUI != nullptr)
	{
		loginUI->SetController(this);
		loginUI->AddToViewport();
	}
	LoginView = loginUI;
}
//=================================================================================================
// @brief 메인 뷰 생성
//=================================================================================================
void UUIChatController::CreateMainView()
{
	if (MainView != nullptr)
	{
		return;
	}
	UBlueprintGeneratedClass* loginBluePrint = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/MainScreen.MainScreen_C'"));

	UClass* uClass;
	uClass = Cast<UClass>(loginBluePrint);

	auto widget = CreateWidget(CachedWorld, uClass);

	UMainScreenUIWidget* mainUI = Cast<UMainScreenUIWidget>(widget);

	if (mainUI != nullptr)
	{
		mainUI->SetController(this);
		mainUI->AddToViewport(15);
		mainUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	MainView = mainUI;

}
//=================================================================================================
// @brief 채팅 뷰 생성
//=================================================================================================
void UUIChatController::CreateChatView()
{
	if (ChatView != nullptr)
	{
		return;
	}
	UBlueprintGeneratedClass* loginBluePrint = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/ChatRoom.ChatRoom_C'"));

	UClass* uClass;
	uClass = Cast<UClass>(loginBluePrint);

	auto widget = CreateWidget(CachedWorld, uClass);

	UChatRoomWidget* chatUI = Cast<UChatRoomWidget>(widget);

	if (chatUI != nullptr)
	{
		chatUI->SetController(this);
		chatUI->AddToViewport();
	}

	ChatView = chatUI;

	SetChatUI(false);

}
//=================================================================================================
// @brief 클라이언트 알림 메시지 생성
//=================================================================================================

void UUIChatController::CreateNotifyMessage(const FString& msg)
{
	UBlueprintGeneratedClass* notifyBlueprint = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/NotifyMessage.NotifyMessage_C'"));
	UClass* message;
	message = Cast<UClass>(notifyBlueprint);

	auto widget = CreateWidget(CachedWorld, message);
	UNotifyMessageWidget* messageWidget = Cast<UNotifyMessageWidget>(widget);
	if (messageWidget != NULL)
	{
		messageWidget->SetText(msg);
		MainView->AddMessageItem(widget);
		//UPanelWidget::AddChild(messageWidget);
		MainView->AddLogListItem(msg);
	}

}

void UUIChatController::CreateRoomList()
{

}

void UUIChatController::RemoveLoginUI()
{
	LoginView->RemoveFromParent();
}

void UUIChatController::SetMainUI(bool isActive)
{
	if (isActive == true)
	{
		MainView->SetChatCanvas(true);
		MainView->SetRoomCreateCanvas(false);
		MainView->SetUserListCanvas(true);
	}
	else
	{
		MainView->SetChatCanvas(false);
		MainView->SetRoomCreateCanvas(false);
	}
}

void UUIChatController::SetChatUI(bool isActive)
{
	if (isActive == true)
	{
		ChatView->SetVisibility(ESlateVisibility::Visible);
		IsUserIn = true;
	}
	else
	{
		IsUserIn = false;
		ChatView->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UUIChatController::SetChatUITitle(const FString& title)
{
	ChatView->SetRoomName(title);
}

void UUIChatController::SetWhisperUser(const FString& name)
{
	MainView->SetWhisperUser(name);
}

//=================================================================================================
// @brief 룸 리스트 아이템 추가
//=================================================================================================
void UUIChatController::AddRoomListItem(const FString& name)
{
	MainView->AddRoomListItem(name);
}

//=================================================================================================
// @brief 채팅 리스트 아이템 추가
//=================================================================================================
void UUIChatController::AddChatListItem(const FString& name, int newLineCount)
{
	ChatView->AddChatListItem(name, newLineCount);
}
//=================================================================================================
// @brief 유저 리스트 아이템 추가
//=================================================================================================
void UUIChatController::AddUserListItem(const FString& name)
{
	MainView->AddUserListItem(name);
}
//=================================================================================================
// @brief 로그인 패킷 요청
//=================================================================================================
void UUIChatController::RequestSendLogin(const FString& name)
{
	GetPacketmanager()->SendLogin(name);

}
//=================================================================================================
// @brief 서버 연결 패킷 요청
//=================================================================================================
void UUIChatController::RequestConnectServer(int port, TFunction<void(void)> onSuccessAction, TFunction<void(void)> onFailAction)
{
	GetPacketmanager()->ConnectServer(port, onSuccessAction, onFailAction);
}
//=================================================================================================
// @brief 방 목록 패킷 요청
//=================================================================================================
void UUIChatController::RequestSendRoomList()
{
	MainView->ClearRoomList();
	GetPacketmanager()->SendRoomList();
}
//=================================================================================================
// @brief 방 생성 요청
//=================================================================================================
void UUIChatController::RequestCreateRoom(const FString& roomName, int32 maxUserCount)
{
	GetPacketmanager()->SendCreateRoom(roomName, maxUserCount);
}
//=================================================================================================
// @brief 메시지 전송 패킷 요청
//=================================================================================================
void UUIChatController::RequestChat(const FString& msg)
{
	GetPacketmanager()->SendChat(msg);
}

//=================================================================================================
// @brief 메시지 전송 패킷 요청
//=================================================================================================
void UUIChatController::RequestExitRoom()
{
	SetChatUI(false);
	GetPacketmanager()->SendExitRoom();
}
//=================================================================================================
// @brief 방 입장 패킷 요청
//=================================================================================================
void UUIChatController::RequestEnterRoom(int index)
{
	GetPacketmanager()->SendEnterRoom(index);
}
//=================================================================================================
// @brief 유저 리스트 패킷 요청
//=================================================================================================
void UUIChatController::RequestUserList()
{
	GetPacketmanager()->SendUserList();
}

void UUIChatController::RequestWhisper(const FString& msg, const FString& name)
{
	GetPacketmanager()->SendWhispher(msg, name);
}

//=================================================================================================
// @brief 유저가 채팅방에 접속했는지 체크
//=================================================================================================

bool UUIChatController::IsUserInChatRoom()
{
	return IsUserIn;
}

USocketManager* UUIChatController::GetPacketmanager()
{
	auto gameInstance = CachedWorld->GetGameInstance();
	UProjectChatGameInstance* GameInstanceRef = Cast<UProjectChatGameInstance>(gameInstance);
	return GameInstanceRef->GetPacketManager();
}






