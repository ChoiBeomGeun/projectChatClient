// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "ViewWidget.h"

#include "MainScreenUIWidget.generated.h"
/**
 * 
 */
class URoomListDataObject;
class UListView;
UCLASS()
class PROJECTCHAT_API UMainScreenUIWidget : public UViewWidget
{
	GENERATED_BODY()

public:
	void AddMessageItem(UWidget* widget)
	{
		MessageBox->AddChild(widget);
	}

	void SetRoomListItems(TArray<URoomListDataObject*> datas);

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MessageBox;

	UPROPERTY(meta = (BindWidget))
	UListView* URoomListView;
};
