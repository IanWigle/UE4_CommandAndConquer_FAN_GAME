// Fill out your copyright notice in the Description page of Project Settings.


#include "LANMenuWidget.h"

#include "UObject/ConstructorHelpers.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

#include "ServerRow.h"

ULANMenuWidget::ULANMenuWidget(const FObjectInitializer &ObjectInitializer)
{
//	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT());
	//if (!ensure(ServerRowBPClass.Class != nullptr)) return;
	//ServerRowClass = ServerRowBPClass.Class;
}

void ULANMenuWidget::SetServerList(TArray<FServerData> ServerNames)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	ServerList->ClearChildren();

	uint32 i = 0;
	for (const FServerData& ServerData : ServerNames)
	{
		UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass);
		if (!ensure(Row != nullptr)) return;

		Row->ServerName->SetText(FText::FromString(ServerData.Name));
		Row->HostUser->SetText(FText::FromString(ServerData.HostUsername));
		FString FractionText = FString::Printf(TEXT("%d%d"), ServerData.CurrentPlayers, ServerData.MaxPlayers);
		Row->ConnectionFraction->SetText(FText::FromString(FractionText));
		Row->Setup(this, i);
		i++;

		ServerList->AddChild(Row);
	}
}

void ULANMenuWidget::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren();
}

bool ULANMenuWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &ULANMenuWidget::OpenHostMenu);

	if (!ensure(JoinButton != nullptr)) return false;
	JoinButton->OnClicked.AddDynamic(this, &ULANMenuWidget::OpenJoinMenu);

	if (!ensure(BackButton != nullptr)) return false;


	return true;
}

void ULANMenuWidget::HostServer()
{
	if (m_MenuInterface != nullptr)
	{
		FString ServerName = ServerHostName->Text.ToString();
		FString TeamNum = TeamHost->Text.ToString();
		m_MenuInterface->Host(ServerName, TeamNum);
	}
}

void ULANMenuWidget::JoinServer()
{
	if (SelectedIndex.IsSet() && m_MenuInterface != nullptr)
	{
		FString TeamNum = TeamJoin->Text.ToString();
		UE_LOG(LogTemp, Warning, TEXT("Selected index %d"), SelectedIndex.GetValue());
		m_MenuInterface->Join(SelectedIndex.GetValue(), TeamNum);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set."));
	}
}

void ULANMenuWidget::OpenHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(HostMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(HostMenu);
}

void ULANMenuWidget::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(JoinMenu);
	if (m_MenuInterface != nullptr)
	{
		m_MenuInterface->RefreshServerList();
	}
}

void ULANMenuWidget::BackPressed()
{
}

void ULANMenuWidget::UpdateChildren()
{
	for (int32 i = 0; i < ServerList->GetChildrenCount(); i++)
	{
		auto Row = Cast<UServerRow>(ServerList->GetChildAt(i));
		if (Row != nullptr)
		{
			Row->Selected = (SelectedIndex.IsSet() && SelectedIndex.GetValue() == i);
		}
	}
}
