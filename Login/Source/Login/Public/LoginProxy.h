// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LoginProxy.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSinginorupDelegate, FString, msg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMatchrequestDelegate, int, side, int, port,FString, ip);

UCLASS()
class LOGIN_API ULoginProxy : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	static class Kcpclient* kcpclient;
	class CChannel* channel;

	uint8 buffer[4096] = { 0 };
	bool b_background = false;
	bool b_connectionok = false;
public:
	bool b_newchannel = false;
	int selfid;
	int roomid;
	int oldotherid;
	enum CMDPlayer {
		SINGUP,
		LOGIN,
		MATCHREQUEST,
		CREATEROOM,
		JOINROOM,
		JOINROOMFAILED,
		STARTGAME,
		OTHERPLAYERINFOR,
		EXITREQUEST,
		RECONNECTLOGIN,
		RECONNECT,
		RECONNECTV1,
		CHECKCONNECTION,
	};
	ULoginProxy();
	~ULoginProxy();
	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnMatchrequestResult;
	TFunction<void(int side, int port, FString ip)> TFOnMatchrequestResult;

	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnCreateRoomResult;
	TFunction<void(int side, int port, FString ip)> TFOnCreateRoomResult;

	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnJoinRoomResult;
	TFunction<void(int side, int port, FString ip)> TFOnJoinRoomResult;

	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnJoinRoomFailedResult;
	TFunction<void(int side, int port, FString ip)> TFOnJoinRoomFailedResult;

	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnOtherplayerinfor;
	TFunction<void(int side, int port, FString ip)> TFOnOtherplayerinfor;

	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnStartGameResult;
	TFunction<void(int side, int port, FString ip)> TFOnStartGameResult;

	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnSingUpResult;
	TFunction<void(int side, int port, FString ip)> TFOnSingUpResult;

	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnSingInResult;
	TFunction<void(int side, int port, FString ip)> TFOnSingInResult;
	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnReConnectLoginResult;
	TFunction<void(int side, int port, FString ip)> TFOnReConnectLoginResult;
	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnReConnectResult;
	TFunction<void(int side, int port, FString ip)> TFOnReConnectResult;

	UPROPERTY(BlueprintAssignable)
		FMatchrequestDelegate OnReConnectv1Result;
	TFunction<void(int side, int port, FString ip)> TFOnReConnectv1Result;


	TFunction<void(int side, int port, FString ip)> TFOnAppEnterForeground;

	TFunction<void(int side, int port, FString ip)> TFOnAppEnterBackground;

	TFunction<void(int side, int port, FString ip)> TFOnReconnect;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoginProxy", BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Login")
		static ULoginProxy* LoginProxy(FString ip, int port);
	virtual void Activate() override;
	void send(const uint8 command, uint8* data, uint16 size);
	bool isconnected();

};
