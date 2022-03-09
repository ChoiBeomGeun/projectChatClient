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

	BackBtn->OnClicked.RemoveAll(this);
	BackBtn->OnClicked.AddDynamic(this, &UChatRoomWidget::OnClickBackBtn);

	UChatListView->OnEntryWidgetGenerated().AddLambda([](UUserWidget& uw)
		{
			auto* textBlock = Cast<UTextBlock>(uw.GetWidgetFromName(FName(TEXT("ListTextBlock"))));
			//textBlock->SetText(FText::AsNumber(50.f));
		});

	UChatListView->ClearListItems();
}

void UChatRoomWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if(ChatController->IsUserInChatRoom()) ChatController->RequestExitRoom();
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

	AddChatListItem(msg, 1,true);
}

void UChatRoomWidget::OnClickBackBtn()
{
	ChatController->RequestExitRoom();
}

void UChatRoomWidget::SetRoomName(const FString& roomName)
{
	RoomNameTextBlock->SetText(FText::FromString(roomName));
}

void UChatRoomWidget::AddChatListItem(const FString& res, int newLineCount,bool isClientMsg)
{
	UChatListDataObject* data = NewObject<UChatListDataObject>();
	data->value = res;
	data->lineCount = newLineCount;
	data->IsClientMsg = isClientMsg;
	data->IsChatMsg = true;
	UChatListView->AddItem(data);
	UChatListView->RequestScrollItemIntoView(data);
	UChatListView->ScrollIndexIntoView(UChatListView->GetNumItems() - 1);
}
