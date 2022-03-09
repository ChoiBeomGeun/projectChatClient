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
// @brief �α��� �� ����
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
// @brief ���� �� ����
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
// @brief ä�� �� ����
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
// @brief Ŭ���̾�Ʈ �˸� �޽��� ����
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
// @brief �� ����Ʈ ������ �߰�
//=================================================================================================
void UUIChatController::AddRoomListItem(const FString& name)
{
	MainView->AddRoomListItem(name);
}

//=================================================================================================
// @brief ä�� ����Ʈ ������ �߰�
//=================================================================================================
void UUIChatController::AddChatListItem(const FString& name, int newLineCount)
{
	ChatView->AddChatListItem(name, newLineCount);
}
//=================================================================================================
// @brief ���� ����Ʈ ������ �߰�
//=================================================================================================
void UUIChatController::AddUserListItem(const FString& name)
{
	MainView->AddUserListItem(name);
}
//=================================================================================================
// @brief �α��� ��Ŷ ��û
//=================================================================================================
void UUIChatController::RequestSendLogin(const FString& name)
{
	GetPacketmanager()->SendLogin(name);

}
//=================================================================================================
// @brief ���� ���� ��Ŷ ��û
//=================================================================================================
void UUIChatController::RequestConnectServer(int port, TFunction<void(void)> onSuccessAction, TFunction<void(void)> onFailAction)
{
	GetPacketmanager()->ConnectServer(port, onSuccessAction, onFailAction);
}
//=================================================================================================
// @brief �� ��� ��Ŷ ��û
//=================================================================================================
void UUIChatController::RequestSendRoomList()
{
	MainView->ClearRoomList();
	GetPacketmanager()->SendRoomList();
}
//=================================================================================================
// @brief �� ���� ��û
//=================================================================================================
void UUIChatController::RequestCreateRoom(const FString& roomName, int32 maxUserCount)
{
	GetPacketmanager()->SendCreateRoom(roomName, maxUserCount);
}
//=================================================================================================
// @brief �޽��� ���� ��Ŷ ��û
//=================================================================================================
void UUIChatController::RequestChat(const FString& msg)
{
	GetPacketmanager()->SendChat(msg);
}

//=================================================================================================
// @brief �޽��� ���� ��Ŷ ��û
//=================================================================================================
void UUIChatController::RequestExitRoom()
{
	SetChatUI(false);
	GetPacketmanager()->SendExitRoom();
}
//=================================================================================================
// @brief �� ���� ��Ŷ ��û
//=================================================================================================
void UUIChatController::RequestEnterRoom(int index)
{
	GetPacketmanager()->SendEnterRoom(index);
}
//=================================================================================================
// @brief ���� ����Ʈ ��Ŷ ��û
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
// @brief ������ ä�ù濡 �����ߴ��� üũ
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






