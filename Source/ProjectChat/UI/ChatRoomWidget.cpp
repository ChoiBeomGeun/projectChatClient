// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatRoomWidget.h"

#include "ChatListDataObject.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/EditableTextBox.h"
void UChatRoomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SendBtn->OnClicked.RemoveAll(this);
	SendBtn->OnClicked.AddDynamic(this, &UChatRoomWidget::OnClickSendMessage);

	UChatListView->OnEntryWidgetGenerated().AddLambda([](UUserWidget& uw)
		{
			auto* textBlock = Cast<UTextBlock>(uw.GetWidgetFromName(FName(TEXT("ListTextBlock"))));
			//textBlock->SetText(FText::AsNumber(50.f));
		});

	UChatListView->ClearListItems();
}

void UChatRoomWidget::OnClickSendMessage()
{
	FString msg = ChatTextBox->GetText().ToString();
	if(msg.IsEmpty())
	{
		ChatController->CreateNotifyMessage(TEXT("내용을 입력하세요!"));
		return;
	}
	msg = msg.Replace(L"/", L"") +"\r\n";
	ChatController->RequestChat(msg);
	ChatTextBox->SetText(FText::GetEmpty());

}

void UChatRoomWidget::SetRoomName(const FString& roomName)
{
	RoomNameTextBlock->SetText(FText::FromString(roomName));
}

void UChatRoomWidget::AddChatListItem(const FString& res)
{
	UChatListDataObject* data = NewObject<UChatListDataObject>();
	data->value = res;

	UChatListView->AddItem(data);
	UChatListView->ScrollIndexIntoView(UChatListView->GetNumItems() - 1);
}
