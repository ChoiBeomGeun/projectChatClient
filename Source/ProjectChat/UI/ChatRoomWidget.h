// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ViewWidget.h"
#include "Components/Button.h"
#include "ChatRoomWidget.generated.h"
class UEditableTextBox;
class UButton;
class UListView;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTCHAT_API UChatRoomWidget : public UViewWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
public:
	UFUNCTION()
	void OnClickSendMessage();

	void SetRoomName(const FString & roomName);
	void AddChatListItem(const FString& res);

	UPROPERTY(meta = (BindWidget))
	UButton* SendBtn;

	UPROPERTY(meta = (BindWidget))
	UListView* UChatListView;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoomNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ChatTextBox;
};
