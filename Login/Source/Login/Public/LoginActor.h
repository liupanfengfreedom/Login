// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoginActor.generated.h"

UCLASS()
class LOGIN_API ALoginActor : public AActor
{
	GENERATED_BODY()
		class Kcpclient* kcpclient;
	class CChannel* channel;
	uint8 buffer[4096] = {0};
	enum CMDPlayer {
		SINGUP,
		LOGIN,
		MATCHREQUEST,
		EXITREQUEST,
	};
public:	
	// Sets default values for this actor's properties
	ALoginActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void send( uint8 command, uint8* data,  uint16 size);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void matchbegin();
};
