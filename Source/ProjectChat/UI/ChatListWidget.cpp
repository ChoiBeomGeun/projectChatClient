// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatListWidget.h"
#include "ChatListDataObject.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UChatListWidget::OnClickBtn()
{
	//FString userName = InfoString.Mid(res.Find("["), res.Find("]"));
	//ChatController->RequestWhisper()
}

void UChatListWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto* data = Cast<UChatListDataObject>(ListItemObject);
	if (data)
	{
		ListTextBlock->SetText(FText::FromString(data->value));
		InfoString = data->value;
		if (InvisibleButton != nullptr)
		{
			SetController(data->Controller);
			InvisibleButton->OnClicked.RemoveAll(this);
			InvisibleButton->OnClicked.AddDynamic(this, &UChatListWidget::OnClickBtn);
		}
		//UCanvasPanelSlot* canvas = Cast<UCanvasPanelSlot>(ListTextBlock->Slot);
		//FVector2D curSize = canvas->GetSize();
		//curSize.Y = (curSize.Y * data->lineCount);
		//canvas->SetSize(curSize);
	}
}
