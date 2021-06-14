// Fill out your copyright notice in the Description page of Project Settings.


#include "LogInGameInstance.h"
#include "LoginProxy.h"
#include "LoginLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LANPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
void ULogInGameInstance::Init()
{
	Super::Init();
	if (UKismetSystemLibrary::IsDedicatedServer(GetWorld()))
	{
		return;
	}
	ULoginLibrary::setipaddress("192.168.31.252", 6999);//"60.12.176.54"
	lp = ULoginProxy::LoginProxy("192.168.31.252", 6999);
	lp->TFOnSingInResult = [=](int side, int port, FString ip) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip+"  : TFOnSingInResult");
	};
	lp->TFOnMatchrequestResult = [=](int side, int port, FString ip) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + FString::FromInt(port) + "  : TFOnMatchrequestResult");
		ipadress = FName(ip + ":" + FString::FromInt(port));
		UGameplayStatics::OpenLevel(GetWorld(), ipadress);
	};
	lp->TFOnCreateRoomResult = [=](int side, int port, FString ip) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + "  : TFOnCreateRoomResult");
	};
	lp->TFOnJoinRoomResult = [=](int side, int port, FString ip) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + "  : TFOnJoinRoomResult");
	};
	lp->TFOnStartGameResult = [=](int side, int port, FString ip) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + "  : TFOnStartGameResult");
		ipadress = FName(ip + ":" + FString::FromInt(port));
		UGameplayStatics::OpenLevel(GetWorld(), ipadress);
	};
	lp->TFOnOtherplayerinfor = [=](int side, int port, FString ip) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + "  : TFOnOtherplayerinfor");
	};
	lp->TFOnReConnectLoginResult = [=](int side, int port, FString ip) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + "  : TFOnReConnect  Login  Result");
	};
	lp->TFOnReConnectResult = [=](int side, int port, FString ip) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + "  : TFOnReConnect Result");
		if (port == 1 && b_playercontrollerdisconnect)
		{
			//UGameplayStatics::OpenLevel(GetWorld(), ipadress);
			UGameplayStatics::OpenLevel(GetWorld(), ipadress,true,FString::FromInt(ALANPlayerController::getid()));
		}
	};
	lp->TFOnReConnectv1Result = [=](int side, int port, FString ip) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + "  : TFOnReConnect   v1   Result");
		if (port == 1 && b_playercontrollerdisconnect)
		{
			//UGameplayStatics::OpenLevel(GetWorld(), ipadress);
			UGameplayStatics::OpenLevel(GetWorld(), ipadress, true, FString::FromInt(ALANPlayerController::getid()));
		}
	};
	lp->TFOnAppEnterForeground = [=](int side, int port, FString ip) {

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ip + "  : TFOnAppEnterForeground");
		ALANPlayerController* pc = Cast<ALANPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (pc)
		{
			b_playercontrollerdisconnect = true;
			pc->checkconnection();
			pc->TFOnCheckConnectedResult = [=](uint8 msg) {
				if (msg == 0)
				{
					Async(EAsyncExecution::ThreadPool, [=]() {
						while (true)
						{
							FPlatformProcess::Sleep(0.5F);
							if (ULoginLibrary::isconnected() )
							{
								if (!lp->b_newchannel)
								{
									if (ULoginLibrary::state == 0)
									{
										ULoginLibrary::reconnectlogin("user--password");
										GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "  : ULoginLibrary::state == 0");
									}
									else if (ULoginLibrary::state == 1)
									{
										ULoginLibrary::reconnect(2);
										GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, " ULoginLibrary::state == 1");
									}
									else if (ULoginLibrary::state == 2)
									{
										ULoginLibrary::reconnectv1(true);
										GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, " ULoginLibrary::state == 2");
									}
									else if (ULoginLibrary::state == 3)
									{
										ULoginLibrary::reconnectv1(false);
										GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, " ULoginLibrary::state == 3");
									}
								}
								break;
							}
						}
						}, nullptr);
				}
				else if (msg == 1)
				{			
					b_playercontrollerdisconnect = false;
				}

			};
		}
	};
	lp->TFOnReconnect = [=](int side, int port, FString ip) {
		Async(EAsyncExecution::ThreadPool, [=]() {
			while (true) {
				FPlatformProcess::Sleep(0.5F);
				if (ULoginLibrary::isconnected())
				{
					if (ULoginLibrary::state == 0)
					{
						ULoginLibrary::reconnectlogin("user--password");
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "  : ULoginLibrary::state == 0");
					}
					else if (ULoginLibrary::state == 1)
					{
						ULoginLibrary::reconnect(2);
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, " ULoginLibrary::state == 1");
					}
					else if (ULoginLibrary::state == 2)
					{
						ULoginLibrary::reconnectv1(true);
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, " ULoginLibrary::state == 2");
					}
					else if (ULoginLibrary::state == 3)
					{
						ULoginLibrary::reconnectv1(false);
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, " ULoginLibrary::state == 3");
					}
					break;
				}
			}
			}, nullptr);

	};
}
