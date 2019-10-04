// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperFunctions.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimNode_StateMachine.h"
#include "Engine.h"
#include "Units/Buildings/Global/TiberiumRefinery.h"

float UHelperFunctions::TimeRemainingInAnimationFromStateMachine(class ACharacter* a_character, FName a_StateMachineName, FName a_StateName)
{
	if (a_character)
	{
		FAnimNode_StateMachine* stateMachine = a_character->GetMesh()->GetAnimInstance()->GetStateMachineInstanceFromName(a_StateMachineName);

		if (stateMachine)
		{
			if (stateMachine->GetCurrentStateName() == a_StateName)
			{
				int32 stateMachineIndex = a_character->GetMesh()->GetAnimInstance()->GetStateMachineIndex(a_StateMachineName);
				int32 currentStateIndex = stateMachine->GetCurrentState();
				if (stateMachine->GetCurrentStateName() == a_StateName)
				{
					float timeRemaining = a_character->GetMesh()->GetAnimInstance()->GetRelevantAnimTimeRemaining(stateMachineIndex, currentStateIndex);
					return timeRemaining;
				}
				return -1;
			}
			return -1;
		}
	}
        
    return -1;
}

AActor* UHelperFunctions::GetClosestRefinery(class ACharacter* a_character, class UWorld* world)
{
	TArray<AActor*> OutActors;
	TSubclassOf<ATiberiumRefinery> Filter;
	UGameplayStatics::GetAllActorsOfClass(world, Filter, OutActors);

	int ClosestRefineryIndex = 0;
	float LowestDistance = 0.0f;
	
	if (OutActors.Num() > 0)
	{
		LowestDistance = FVector::Distance(a_character->GetActorLocation(), OutActors[0]->GetActorLocation());

		for (int i = 0; i < OutActors.Num(); i++)
		{
			float distance = FVector::Distance(a_character->GetActorLocation(), OutActors[i]->GetActorLocation());
			if (distance <= LowestDistance)
			{
				LowestDistance = distance;
				ClosestRefineryIndex = i;
			}
		}

		return OutActors[ClosestRefineryIndex];
	}

	return nullptr;
}

bool UHelperFunctions::IsInEditor(class UWorld* world)
{
	return world->IsPlayInEditor();
}

void UHelperFunctions::AttachActorToSkeletalMeshSocket(FName socketName, AActor * attachingActor, USkeletalMeshComponent * mesh, FAttachmentTransformRules attachRule)
{
	if (attachingActor && mesh)
	{
		if (mesh->DoesSocketExist(socketName))
		{
			attachingActor->AttachToComponent(mesh, attachRule, socketName);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 4.0f, FColor::Red, "Attaching Actor or Skeletal Mesh not passed in properly");
		}
	}
}

void UHelperFunctions::AttachComponentToSkeletalMeshSocket(FName socketName, UPrimitiveComponent * attachingComponent, USkeletalMeshComponent * mesh, FAttachmentTransformRules attachRule)
{
	if (attachingComponent && mesh)
	{
		if (mesh->DoesSocketExist(socketName))
		{
			attachingComponent->AttachToComponent(mesh, attachRule, socketName);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 4.0f, FColor::Red, "Attaching Actor or Skeletal Mesh not passed in properly");
	}
}

void AttachActorToStaticMeshSocket(FName socketName, AActor* attachingActor, UStaticMeshComponent* mesh, FAttachmentTransformRules attachRule)
{
	if (attachingActor && mesh)
	{
		if (mesh->DoesSocketExist(socketName))
		{
			attachingActor->AttachToComponent(mesh, attachRule, socketName);
		}
		else
			GEngine->AddOnScreenDebugMessage(1, 4.0f, FColor::Red, "Socket To Attach to Component does not exist!");
	}
	else
		GEngine->AddOnScreenDebugMessage(1, 4.0f, FColor::Red, "Attaching Component or Mesh is not valid");
}

void AttachComponentToStaticMeshSocket(FName socketName, UPrimitiveComponent* attachingComponent, UStaticMeshComponent* mesh, FAttachmentTransformRules attachRule)
{
	if (attachingComponent && mesh)
	{
		if (mesh->DoesSocketExist(socketName))
		{
			attachingComponent->AttachToComponent(mesh, attachRule, socketName);
		}
		else
			GEngine->AddOnScreenDebugMessage(1, 4.0f, FColor::Red, "Socket To Attach to Component does not exist!");
	}
	else
		GEngine->AddOnScreenDebugMessage(1, 4.0f, FColor::Red, "Attaching Component or Mesh is not valid");
}
