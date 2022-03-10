// Fill out your copyright notice in the Description page of Project Settings.


#include "InviteWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UInviteWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OkButton->OnClicked.RemoveAll(this);
	OkButton->OnClicked.AddDynamic(this, &UInviteWidget::OnClickOk);

}

void UInviteWidget::OnClickOk()
{
	ChatController->RequestEnterRoom(InviteRoomNumber);
	RemoveFromViewport();
}

void UInviteWidget::SetTextBox(const FString& msg)
{
	DesTextBlock->SetText(FText::FromString(msg));
}
