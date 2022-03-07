// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void ULoginUI::NativeConstruct()
{
	Super::NativeConstruct();
	SetPortUI();
}



void ULoginUI::SetPortUI()
{
	TitleTextBlock->SetText(FText::FromString(L"서버 연결"));
	TextBox->SetHintText(FText::FromString(L"포트입력 (기본7777)"));
	
	LoginButton->OnClicked.RemoveAll(this);
	LoginButton->OnClicked.AddDynamic(this, &ULoginUI::OnClickSetPortBtn);

}

void ULoginUI::SetLoginUI()
{
	TitleTextBlock->SetText(FText::FromString("Login"));
	TextBox->SetHintText(FText::FromString("Input NickName"));

	LoginButton->OnClicked.RemoveAll(this);
	LoginButton->OnClicked.AddDynamic(this, &ULoginUI::OnClickLoginBtn);
}

void ULoginUI::OnClickLoginBtn()
{
	FText curText = TextBox->GetText();
	if(curText.IsEmpty() == true || GetNum(curText.ToString()) > 10)
	{
		ChatController->CreateNotifyMessage(L"입력을 확인하세요! 닉네임은 최대 10글자입니다." );
		return;
	}

	ChatController->RequestSendLogin(TextBox->GetText().ToString());
}

void ULoginUI::OnClickSetPortBtn()
{
	FText curText = TextBox->GetText();
	if (curText.IsEmpty() == true || curText.IsNumeric() == false)
	{
		FString msg = FString(TEXT("Check Input"));
		ChatController->CreateNotifyMessage(msg);
		return;
	}

	ChatController->RequestConnectServer(FCString::Atoi(*curText.ToString()), 
		[&]() {SetLoginUI(); }, 
		[&]() 
		{
			FString msg = FString(TEXT("서버 연결 실패!"));
			ChatController->CreateNotifyMessage(msg);
		});
	TextBox->SetText(FText::GetEmpty());


}
