// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoginLibrary.generated.h"

/**
 *
 */
UCLASS()
class LOGIN_API ULoginLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		static FString ipaddress;
	static int portnumber;
public:
	static int state;
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void setipaddress(FString ip, int port);
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static bool isconnected();
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void singup(const FString& msg);
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void singin(const FString& msg);
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void matchrequest(int halfroomnumber);
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void createroomquest();
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void joinroomquest(int roomid);
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void startgame(int roomid);
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void reconnectlogin(const FString& msg);
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void reconnect(int halfroomnumber);
	UFUNCTION(BlueprintCallable, Category = "LoginLibrary")
		static void reconnectv1(bool owner);
};
