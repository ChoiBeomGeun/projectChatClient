// Fill out your copyright notice in the Description page of Project Settings.
#include "UIChatController.h"
#include "ViewWidget.h"
#include "NotifyMessageWidget.h"
#include "../Network/PacketManager.h"
#include "../UI/LoginUI.h"
#include "../UI/MainScreenUIWidget.h"
#include "../UI/ChatRoomWidget.h"

UIChatController::UIChatController()
{
	LoginView = nullptr;
	MainView = nullptr;
	ChatView = nullptr;
}

UIChatController::~UIChatController()
{
}

void UIChatController::SetPacketManager(PacketManager* packetManager)
{
	Packetmanager = packetManager;
}

void UIChatController::SetWorld( UWorld* world)
{
	CachedWorld =  world;
}

void UIChatController::SetName(const FString* name)
{

}

//=================================================================================================
// @brief �α��� �� ����
//=================================================================================================
void UIChatController::CreateLoginView()
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
void UIChatController::CreateMainView()
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
		mainUI->AddToViewport();
	}

	MainView = mainUI;

}
//=================================================================================================
// @brief ä�� �� ����
//=================================================================================================
void UIChatController::CreateChatView()
{
	if(ChatView != nullptr)
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

void UIChatController::CreateNotifyMessage(const FString& msg)
{
	UBlueprintGeneratedClass* notifyBlueprint = LoadObject<UBlueprintGeneratedClass>(nullptr, TEXT("WidgetBlueprint'/Game/Blueprints/NotifyMessage.NotifyMessage_C'"));
	UClass* message;
	message = Cast<UClass>(notifyBlueprint);

	auto widget = CreateWidget(CachedWorld, message);
	UNotifyMessageWidget * messageWidget = Cast<UNotifyMessageWidget>(widget);
	if (messageWidget != NULL)
	{
		messageWidget->SetText(msg);
		MainView->AddMessageItem(widget);
		//UPanelWidget::AddChild(messageWidget);
	}

}

void UIChatController::CreateRoomList()
{

}

void UIChatController::RemoveLoginUI()
{
	LoginView->RemoveFromParent();
}

void UIChatController::SetMainUI(bool isActive)
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

void UIChatController::SetChatUI(bool isActive)
{
	if(isActive == true)
	{
		ChatView->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ChatView->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UIChatController::SetChatUITitle(const FString& title)
{
	ChatView->SetRoomName(title);
}

//=================================================================================================
// @brief �� ����Ʈ ������ �߰�
//=================================================================================================
void UIChatController::AddRoomListItem(const FString& name)
{
	MainView->AddRoomListItem(name);
}

//=================================================================================================
// @brief ä�� ����Ʈ ������ �߰�
//=================================================================================================
void UIChatController::AddChatListItem(const FString& name,int newLineCount)
{
	ChatView->AddChatListItem(name, newLineCount);
}
//=================================================================================================
// @brief ���� ����Ʈ ������ �߰�
//=================================================================================================
void UIChatController::AddUserListItem(const FString& name)
{
	MainView->AddUserListItem(name);
}
//=================================================================================================
// @brief �α��� ��Ŷ ��û
//=================================================================================================
void UIChatController::RequestSendLogin(const FString& name)
{
	Packetmanager->SendLogin(name);
	
}
//=================================================================================================
// @brief ���� ���� ��Ŷ ��û
//=================================================================================================
void UIChatController::RequestConnectServer(int port,std::function<void(void)> onSuccessAction, std::function<void(void)> onFailAction)
{
	Packetmanager->ConnectServer(port, onSuccessAction,onFailAction);
}
//=================================================================================================
// @brief �� ��� ��Ŷ ��û
//=================================================================================================
void UIChatController::RequestSendRoomList()
{
	MainView->ClearRoomList();
	Packetmanager->SendRoomList();
}
//=================================================================================================
// @brief �� ���� ��û
//=================================================================================================
void UIChatController::RequestCreateRoom(const FString& roomName, int32 maxUserCount)
{
	Packetmanager->SendCreateRoom(roomName, maxUserCount);
}
//=================================================================================================
// @brief �޽��� ���� ��Ŷ ��û
//=================================================================================================
void UIChatController::RequestChat(const FString& msg)
{
	Packetmanager->SendChat(msg);
}

//=================================================================================================
// @brief �޽��� ���� ��Ŷ ��û
//=================================================================================================
void UIChatController::RequestExitRoom()
{
	SetChatUI(false);
	Packetmanager->SendExitRoom();
}
//=================================================================================================
// @brief �� ���� ��Ŷ ��û
//=================================================================================================
void UIChatController::RequestEnterRoom(int index)
{
	Packetmanager->SendEnterRoom(index);
}
//=================================================================================================
// @brief ���� ����Ʈ ��Ŷ ��û
//=================================================================================================
void UIChatController::RequestUserList()
{
	Packetmanager->SendUserList();
}

void UIChatController::RequestWhisper(const FString& msg, const FString& name)
{
	Packetmanager->SendWhispher(msg, name);
}

//=================================================================================================
// @brief ������ ä�ù濡 �����ߴ��� üũ
//=================================================================================================

bool UIChatController::IsUserInChatRoom()
{
	return ChatView->Visibility == ESlateVisibility::Visible;
}






