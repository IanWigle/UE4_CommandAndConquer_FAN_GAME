// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StructTypes.h"
#include "UnrealNetwork.h"
#include "Online.h"
#include <../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h>
#include "CnCGameInstance.generated.h"

/**
 * 
 */


UCLASS()
class COMMANDANDCONQUER_API UCnCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCnCGameInstance(const FObjectInitializer& ObjectInitializer);

protected:
	// LAN Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, FLobbyPlayerDetails> m_PlayerDetailMap;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float m_MasterAudioVolume;

	// Graphics
	UPROPERTY(EditAnywhere)
		bool m_bFullscreen;

	UPROPERTY(EditAnywhere)
		FString m_ShadowQuality;

	UPROPERTY(EditAnywhere)
		FString m_TextureDetail;

	UPROPERTY(EditAnywhere)
		FString m_AADetail;

	UPROPERTY(EditAnywhere)
		FString m_EffectsDetail;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FLobbyPlayerDetails GetPlayerDetails(FString playerAddress) { return *m_PlayerDetailMap.Find(playerAddress); }

#pragma region Session Handling
#pragma region Creating Sessions
	/**
	*	Function to host a game!
	*
	*	@Param		UserID			User that started the request
	*	@Param		SessionName		Name of the Session
	*	@Param		bIsLAN			Is this is LAN Game?
	*	@Param		bIsPresence		"Is the Session to create a presence Session"
	*	@Param		MaxNumPlayers	Number of Maximum allowed players on this "Session" (Server)
	*/
	bool HostLobbySession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	UFUNCTION(BlueprintCallable, Category = "Networking")
		void StartOnlineGame(FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers); 

	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	/**
	*	Function fired when a session create request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	*	Function fired when a session start request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);
#pragma endregion
#pragma region Finding Sessions
	/**
	*	Find an online session
	*
	*	@param UserId user that initiated the request
	*	@param bIsLAN are we searching LAN matches
	*	@param bIsPresence are we searching presence sessions
	*/
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void FindOnlineGames(bool bIsLAN, bool bIsPresence);

	/** Delegate for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	/** Handle to registered delegate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<int32> SessionMS;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FString> SessionOwners;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<bool> SessionCanUseCheats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<bool> SessionIsLAN;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<bool> SessionNumConnections;

	/**
	*	Delegate fired when a session search query has completed
	*
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnFindSessionsComplete(bool bWasSuccessful);
#pragma endregion
#pragma region Joining Sessions
	/**
	*	Joins a session via a search result
	*
	*	@param SessionName name of session
	*	@param SearchResult Session to join
	*
	*	@return bool true if successful, false otherwise
	*/
	bool JoinLobbySession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void JoinOnlineGame();

	/** Delegate for joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	/** Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	/**
	*	Delegate fired when a session join request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
#pragma endregion
#pragma region Destroying Sessions
	/** Delegate for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	/**
	*	Delegate fired when a destroying an online session has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
		void DestroySessionAndLeaveGame();
#pragma endregion
#pragma endregion
};
