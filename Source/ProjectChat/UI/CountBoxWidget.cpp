// Fill out your copyright notice in the Description page of Project Settings.


#include "CountBoxWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
void UCountBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlusBtn->OnClicked.RemoveAll(this);
	PlusBtn->OnClicked.AddDynamic(this, &UCountBoxWidget::OnClickPlus);

	MinusBtn->OnClicked.RemoveAll(this);
	MinusBtn->OnClicked.AddDynamic(this, &UCountBoxWidget::OnClickMinus);
}

void UCountBoxWidget::OnClickPlus()
{
	FString string = ValueTextBlock->Text.ToString();
	if (string.IsNumeric())
	{
		int32 value = FCString::Atoi(*string);

		if (value + 1 > MaxCount) return;
		else ++value;
		ValueTextBlock->SetText(FText::FromString(FString::FromInt(value)));
	}
}

void UCountBoxWidget::OnClickMinus()
{
	FString string = ValueTextBlock->Text.ToString();
	if (string.IsNumeric())
	{
		int32 value = FCString::Atoi(*string);

		if (value - 1 < MinCount) return;
		else --value;
		ValueTextBlock->SetText(FText::FromString(FString::FromInt(value)));
	}
}

FString UCountBoxWidget::GetValue()
{
	return ValueTextBlock->Text.ToString();
}
