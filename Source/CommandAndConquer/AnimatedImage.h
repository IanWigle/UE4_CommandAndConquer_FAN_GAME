// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "AnimatedImage.generated.h"

/**
 * 
 */
UCLASS()
class COMMANDANDCONQUER_API UAnimatedImage : public UImage
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Animation)
		void SetCurrentFrame(int32 frame);

	UFUNCTION(BlueprintCallable, Category = Animation)
		void Play();

	UFUNCTION(BlueprintCallable, Category = Animation)
		void Stop();

	virtual void SynchronizeProperties();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		int32 FramesPerSecond = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		int32 CurrentFrame = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
		int32 TotalFrames = 1;

	void TimerTick();

	FTimerHandle TimerHandle;
	
};
