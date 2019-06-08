// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HostUser;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ConnectionFraction;

	UPROPERTY(BlueprintReadOnly)
		bool Selected = false;

	void Setup(class ULANMenuWidget* InParent, uint32 InIndex);

private:

	UPROPERTY(meta = (BindWidget))
		class UButton* RowButton;

	UPROPERTY()
		class ULANMenuWidget* Parent;

	uint32 Index;

	UFUNCTION()
		void OnClicked();
};
