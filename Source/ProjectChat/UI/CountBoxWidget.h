// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountBoxWidget.generated.h"

class UButton;
class UTextBlock;
UCLASS()
class PROJECTCHAT_API UCountBoxWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClickPlus();

	UFUNCTION()
	void OnClickMinus();

public:
	FString GetValue();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* PlusBtn;

	UPROPERTY(meta = (BindWidget))
	UButton* MinusBtn;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ValueTextBlock;

	UPROPERTY(EditAnywhere, Category = "CountBox")
	int32 MaxCount;

	UPROPERTY(EditAnywhere, Category = "CountBox")
	int32 MinCount;

	int value = 0;
};
