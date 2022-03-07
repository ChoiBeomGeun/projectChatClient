// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreenUIWidget.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

void UMainScreenUIWidget::SetRoomListItems(TArray<URoomListDataObject*> datas)
{
//	URoomListView = Cast<UListView>(GetWidgetFromName(FName(TEXT("ListViewTest"))));
//	URoomListView->OnEntryWidgetGenerated().AddLambda([](UUserWidget& uw)
//		{
//			auto* textBlock = Cast<UTextBlock>(uw.GetWidgetFromName(FName(TEXT("ListTextBlock"))));
//			textBlock->SetText(FText::AsNumber(50.f));
//		});
//
//	URoomListView->ClearListItems();
//	URoomListView->SetListItems(datas);
}
