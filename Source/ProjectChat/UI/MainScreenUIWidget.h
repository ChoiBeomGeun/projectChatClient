// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "ViewWidget.h"

#include "MainScreenUIWidget.generated.h"
class UCountBoxWidget;
class UCanvasPanel;
class UButton;
/**
 * 
 */
class URoomListDataObject;
class UListView;
class UEditableTextBox;
UCLASS()
class PROJECTCHAT_API UMainScreenUIWidget : public UViewWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	void AddMessageItem(UWidget* widget)
	{
		MessageBox->AddChild(widget);
	}

	void AddRoomListItem(const FString& res);
	void AddUserListItem(const FString& res);
	void SetWhisperUser(const FString& res);
	void SetUserListCanvas(bool isActive);
	void SetChatCanvas(bool isActive);
	void SetRoomCreateCanvas(bool isActive);
	void SetEmptyRoomDes(bool isVisible);
	void ClearRoomList();

private:

	UFUNCTION()
	void OnClickRefreshBtn();

	UFUNCTION()
	void OnClickSpawnRoomBtn();

	UFUNCTION()
	void OnClickUserRefreshBtn();

	UFUNCTION()
	void OnClickWhisper();

	UFUNCTION()
	void ToggleCreateRoom();

private:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MessageBox;

	UPROPERTY(meta = (BindWidget))
	UListView* URoomListView;

	UPROPERTY(meta = (BindWidget))
	UListView* UUserListView;

	UPROPERTY(meta = (BindWidget))
	UButton* PlusButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SpawnBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* UserRefreshButton;

	UPROPERTY(meta = (BindWidget))
	UButton* WhisperButton;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* ChatCanvas;

	UPROPERTY(meta = (BindWidget))
	UWidget* EmptyRoomListDes;

	UPROPERTY(meta = (BindWidget))
	UWidget* RoomCreateCanvas;

	UPROPERTY(meta = (BindWidget))
	UWidget* UserListCanvas;

	UPROPERTY(meta = (BindWidget))
	UCountBoxWidget* CountBoxWidget;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* RoomNameTextBox;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* WhisperTextBox;
	
};
