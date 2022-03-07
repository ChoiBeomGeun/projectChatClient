// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
void ULoginUI::NativeConstruct()
{
	Super::NativeConstruct();



	LoginButton->OnClicked.AddDynamic(this,&ULoginUI::OnClickLoginBtn);

//	InputComponent->BindAction("PressingEnter", IE_Released, this, &ULoginUI::OnClickLoginBtn);

}


void ULoginUI::OnClickLoginBtn()
{
	
	ChatController->RequestSendLogin(TextBox->GetText().ToString());
	UE_LOG(LogTemp, Log, TEXT("Send dsdsdsdsds"));
}
