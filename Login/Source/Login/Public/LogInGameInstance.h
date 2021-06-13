// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LogInGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LOGIN_API ULogInGameInstance : public UGameInstance
{
	GENERATED_BODY()
		UPROPERTY()
		class ULoginProxy* lp;
	FName ipadress;
	bool b_playercontrollerdisconnect = true;
	virtual void Init()override;
};
