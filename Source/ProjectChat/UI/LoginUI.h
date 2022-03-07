// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewWidget.h"
#include "LoginUI.generated.h"

/**
 * 
 */
class UEditableTextBox;
class UButton;
UCLASS()
class PROJECTCHAT_API ULoginUI : public UViewWidget
{
	GENERATED_BODY()

public:
	
	virtual void NativeConstruct() override;


	UFUNCTION()
	void OnClickLoginBtn();

private:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* TextBox;

	UPROPERTY(meta = (BindWidget))
	UButton * LoginButton;
};
