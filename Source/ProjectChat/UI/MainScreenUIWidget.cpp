// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreenUIWidget.h"

#include "CountBoxWidget.h"
#include "RoomListDataObject.h"
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


	ChatCanvas->SetVisibility(ESlateVisibility::Collapsed);
	RoomCreateCanvas->SetVisibility(ESlateVisibility::Collapsed);

	URoomListView->OnEntryWidgetGenerated().AddLambda([](UUserWidget& uw)
	{
		auto* textBlock = Cast<UTextBlock>(uw.GetWidgetFromName(FName(TEXT("ListTextBlock"))));
		textBlock->SetText(FText::AsNumber(50.f));
	});

	URoomListView->ClearListItems();
}


void UMainScreenUIWidget::AddRoomListItem(const FString& res)
{
	URoomListDataObject* data = NewObject<URoomListDataObject>();
	data->value = res;

	URoomListView->AddItem(data);
}

void UMainScreenUIWidget::SetRoomListItems()
{
	TArray<URoomListDataObject*> Datas;
	for (int i = 0; i < 10; i++)
	{
		URoomListDataObject * data = NewObject<URoomListDataObject>();

		data->value = FString::Printf(TEXT("text%d"), i);
		Datas.Add(data);
	}


	URoomListView = Cast<UListView>(GetWidgetFromName(FName(TEXT("ListViewTest"))));
	URoomListView->OnEntryWidgetGenerated().AddLambda([](UUserWidget& uw)
		{
			auto* textBlock = Cast<UTextBlock>(uw.GetWidgetFromName(FName(TEXT("ListTextBlock"))));
			textBlock->SetText(FText::AsNumber(50.f));
		});

	URoomListView->ClearListItems();
	URoomListView->SetListItems(Datas);

}

void UMainScreenUIWidget::ShowChatCanvas()
{
	ChatCanvas->SetVisibility(ESlateVisibility::Visible);
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


