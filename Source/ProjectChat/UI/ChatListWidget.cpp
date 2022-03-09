// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatListWidget.h"
#include "ChatListDataObject.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UChatListWidget::OnClickBtn()
{
	int startIndex = InfoString.Find("(") + 1;
	int endIndex = InfoString.Find(")");

	FString userName = InfoString.Mid(startIndex, endIndex- startIndex);
	ChatController->SetWhisperUser(userName);
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

		if(data->IsChatMsg)
		{
			if(data->IsClientMsg)
			{
				ListTextBlock->SetJustification(ETextJustify::Right);
			}
			else
			{
				ListTextBlock->SetJustification(ETextJustify::Left);
			}
		}
		//UCanvasPanelSlot* canvas = Cast<UCanvasPanelSlot>(ListTextBlock->Slot);
		//FVector2D curSize = canvas->GetSize();
		//curSize.Y = (curSize.Y * data->lineCount);
		//canvas->SetSize(curSize);
	}
}
