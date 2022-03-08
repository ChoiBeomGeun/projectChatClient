// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatListWidget.h"
#include "ChatListDataObject.h"
#include "Components/TextBlock.h"
void UChatListWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto* data = Cast<UChatListDataObject>(ListItemObject);
	if (data)
	{
		ListTextBlock->SetText(FText::FromString(data->value));
	}
}
