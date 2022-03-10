// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreenUIWidget.h"

#include "ChatListDataObject.h"
#include "CountBoxWidget.h"
#include "RoomListDataObject.h"
#include "RoomListWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableTextBox.h"
#include "Engine/Canvas.h"

void UMainScreenUIWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UMainScreenUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RefreshButton->OnClicked.RemoveAll(this);
	RefreshButton->OnClicked.AddDynamic(this, &UMainScreenUIWidget::OnClickRefreshBtn);

	PlusButton->OnClicked.RemoveAll(this);
	PlusButton->OnClicked.AddDynamic(this, &UMainScreenUIWidget::ToggleCreateRoom);

	SpawnBtn->OnClicked.RemoveAll(this);
	SpawnBtn->OnClicked.AddDynamic(this, &UMainScreenUIWidget::OnClickSpawnRoomBtn);

	UserRefreshButton->OnClicked.RemoveAll(this);
	UserRefreshButton->OnClicked.AddDynamic(this, &UMainScreenUIWidget::OnClickUserRefreshBtn);

	WhisperButton->OnClicked.RemoveAll(this);
	WhisperButton->OnClicked.AddDynamic(this, &UMainScreenUIWidget::OnClickWhisper);

	ExitButton->OnClicked.RemoveAll(this);
	ExitButton->OnClicked.AddDynamic(this, &UMainScreenUIWidget::OnClickExit);

	LogButton->OnClicked.RemoveAll(this);
	LogButton->OnClicked.AddDynamic(this, &UMainScreenUIWidget::ToggleLog);

	if (InviteButton != nullptr)
	{
		InviteButton->OnClicked.RemoveAll(this);
		InviteButton->OnClicked.AddDynamic(this, &UMainScreenUIWidget::OnClickInvite);
	}
	ChatCanvas->SetVisibility(ESlateVisibility::Collapsed);
	RoomCreateCanvas->SetVisibility(ESlateVisibility::Collapsed);
	UserListCanvas->SetVisibility(ESlateVisibility::Collapsed);

	URoomListView->OnEntryWidgetGenerated().AddLambda([](UUserWidget& uw)
	{
		auto* textBlock = Cast<UTextBlock>(uw.GetWidgetFromName(FName(TEXT("ListTextBlock"))));
		/*textBlock->SetText(FText::AsNumber(50.f));*/
	});

	URoomListView->ClearListItems();
}

void UMainScreenUIWidget::PlayApeearAnim()
{
	PlayAnimation(inAnim);
}

//=================================================================================================
// @brief 룸 리스트 아이템 추가
//=================================================================================================
void UMainScreenUIWidget::AddRoomListItem(const FString& res)
{
	URoomListDataObject* data = NewObject<URoomListDataObject>();
	data->value = res;
	data->Index = URoomListView->GetNumItems();
	data->ChatController = ChatController;
	URoomListView->AddItem(data);

	EmptyRoomListDes->SetVisibility(ESlateVisibility::Collapsed);
}
//=================================================================================================
// @brief 유저 리스트 아이템 추가
//=================================================================================================
void UMainScreenUIWidget::AddUserListItem(const FString& res)
{
	UChatListDataObject* data = NewObject<UChatListDataObject>();
	data->value = res;
	data->lineCount = 1;
	data->Controller = ChatController;
	UUserListView->AddItem(data);
	UUserListView->RequestScrollItemIntoView(data);
	UUserListView->ScrollIndexIntoView(UUserListView->GetNumItems() - 1);
}

//=================================================================================================
// @brief 로그 리스트 아이템 추가
//=================================================================================================
void UMainScreenUIWidget::AddLogListItem(const FString& res)
{
	UChatListDataObject* data = NewObject<UChatListDataObject>();
	data->value = res;
	data->lineCount = 1;
	data->Controller = ChatController;
	ULogListView->AddItem(data);
	ULogListView->RequestScrollItemIntoView(data);
	ULogListView->ScrollIndexIntoView(ULogListView->GetNumItems() - 1);
}
//=================================================================================================
// @brief 귓속말 상대 지정
//=================================================================================================
void UMainScreenUIWidget::SetWhisperUser(const FString& res)
{
	WhisperTextBox->SetHintText(FText::FromString(res));
}

void UMainScreenUIWidget::SetUserListCanvas(bool isActive)
{
	if (isActive)
	{
		UserListCanvas->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UserListCanvas->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainScreenUIWidget::SetChatCanvas(bool isActive)
{
	if (isActive)
	{
		ChatCanvas->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ChatCanvas->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainScreenUIWidget::SetRoomCreateCanvas(bool isActive)
{
	if (isActive)
	{
		RoomCreateCanvas->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		RoomCreateCanvas->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainScreenUIWidget::SetLogCanvas(bool isActive)
{
	if (isActive)
	{
		LogListCanvas->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		LogListCanvas->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainScreenUIWidget::SetEmptyRoomDes(bool isVisible)
{
	if(isVisible)
	{
		EmptyRoomListDes->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		EmptyRoomListDes->SetVisibility(ESlateVisibility::Collapsed);
	}

}
//=================================================================================================
// @brief 룸 리스트 아이템 정리
//=================================================================================================
void UMainScreenUIWidget::ClearRoomList()
{
	URoomListView->ClearListItems();
	EmptyRoomListDes->SetVisibility(ESlateVisibility::Visible);
}
//=================================================================================================
// @brief 방 생성 오브젝트 껐다 키는 함수
//=================================================================================================
void UMainScreenUIWidget::ToggleCreateRoom()
{
	if(RoomCreateCanvas->Visibility == ESlateVisibility::Visible)
	{
		RoomCreateCanvas->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		RoomCreateCanvas->SetVisibility(ESlateVisibility::Visible);
	}

}

void UMainScreenUIWidget::OnClickExit()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UMainScreenUIWidget::ToggleLog()
{
	if (LogListCanvas->Visibility == ESlateVisibility::Visible)
	{
		LogListCanvas->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		LogListCanvas->SetVisibility(ESlateVisibility::Visible);
	}
}


void UMainScreenUIWidget::OnClickRefreshBtn()
{
	ChatController->RequestSendRoomList();
}

void UMainScreenUIWidget::OnClickSpawnRoomBtn()
{

	FString roomName = RoomNameTextBox->GetText().ToString();

	if(roomName.IsEmpty())
	{
		ChatController->CreateNotifyMessage(TEXT("방이름을 입력하세요!"));
		return;
	}
	FString countString = CountBoxWidget->GetValue();
	int32 maxUserValue = FCString::Atoi(ToCStr(countString));
	ChatController->RequestCreateRoom(roomName, maxUserValue);
}

void UMainScreenUIWidget::OnClickUserRefreshBtn()
{
	UUserListView->ClearListItems();
	ChatController->RequestUserList();
}

void UMainScreenUIWidget::OnClickWhisper()
{
	if (WhisperTextBox->HintText.IsEmpty())
	{
		ChatController->CreateNotifyMessage(TEXT("상대방을 선택하세요!"));
		return;
	}

	if(WhisperTextBox->GetText().IsEmpty())
	{
		ChatController->CreateNotifyMessage(TEXT("내용을 입력하세요!"));
		return;
	}
	
	ChatController->RequestWhisper(WhisperTextBox->GetText().ToString(), WhisperTextBox->HintText.ToString());
}

void UMainScreenUIWidget::OnClickInvite()
{

	ChatController->RequestInvite(WhisperTextBox->HintText.ToString());
}

