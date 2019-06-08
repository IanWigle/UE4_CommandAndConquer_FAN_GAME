// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/MenuWidget.h"
#include "LANMenuWidget.generated.h"

/**
 * 
 */
USTRUCT()
struct FServerData
{
	GENERATED_BODY()

	FString Name;
	uint16 CurrentPlayers;
	uint16 MaxPlayers;
	FString HostUsername;
};


UCLASS()
class COMMANDANDCONQUER_API ULANMenuWidget : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	ULANMenuWidget(const FObjectInitializer &ObjectInitializer);

	void SetServerList(TArray<FServerData> ServerNames);

	void SelectIndex(uint32 Index);

protected:
	virtual bool Initialize();

private:
	TSubclassOf<class UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
		class UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* ServerHostName;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* TeamHost;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* TeamJoin;

	UPROPERTY(meta = (BindWidget))
		class UPanelWidget* ServerList;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* HostMenu;

	TOptional<uint32> SelectedIndex;

	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void JoinServer();

	UFUNCTION()
		void OpenHostMenu();

	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void BackPressed();

	void UpdateChildren();


};
