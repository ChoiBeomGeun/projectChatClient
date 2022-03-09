// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomListWidget.h"

#include "RoomListDataObject.h"
#include "Components/TextBlock.h"
void URoomListWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	auto* data = Cast<URoomListDataObject>(ListItemObject);
	if (data)
	{
		ListTextBlock->SetText(FText::FromString(data->value));
		Index = data->Index;
		SetController(data->ChatController);
	
		RoomButton->OnClicked.RemoveAll(this);
		RoomButton->OnClicked.AddDynamic(this, &URoomListWidget::OnClickRoom);
	}
}

void URoomListWidget::OnClickRoom()
{
	ChatController->RequestEnterRoom(Index);

}
