// Fill out your copyright notice in the Description page of Project Settings.
#include "UIChatController.h"
#include "ViewWidget.h"
#include "NotifyMessageWidget.h"
#include "../Network/PacketManager.h"
#include "../UI/LoginUI.h"
#include "../UI/MainScreenUIWidget.h"



UIChatController::UIChatController()
{
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

void UIChatController::CreateLoginView()
{
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

void UIChatController::CreateMainView()
{
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

void UIChatController::HideLoginUI()
{
	LoginView->RemoveFromParent();
}

void UIChatController::RequestSendLogin(const FString& name)
{
	Packetmanager->SendLogin(name);
	
}

void UIChatController::RequestConnectServer(int port,std::function<void(void)> onSuccessAction, std::function<void(void)> onFailAction)
{
	Packetmanager->ConnectServer(port, onSuccessAction,onFailAction);
}






