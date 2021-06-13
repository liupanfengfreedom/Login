// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginActor.h"
#include "Kcpclient.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALoginActor::ALoginActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALoginActor::BeginPlay()
{
	Super::BeginPlay();
	//kcpclient = new Kcpclient();
	//channel = kcpclient->CreateChannel("192.168.31.252", 6999);
	//channel->onUserLevelReceivedCompleted=[=](const uint8* data, const uint16& size)->void{
	//	int side;
	//	int dsport;
	//	FString ipstr;
	//	switch ((CMDPlayer)data[0])
 //       {
 //       case CMDPlayer::SINGUP:
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("SINGUP ok"));
	//		break;
 //       case CMDPlayer::LOGIN:
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("LOGIN ok"));
	//		break;
 //       case CMDPlayer::MATCHREQUEST:
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("MATCHREQUEST ok"));
	//		side = *(int*)(data + 1);
	//		dsport = *(int*)(data + 5);
	//		ipstr = FString(UTF8_TO_TCHAR(data+9)).Left(size-9);
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ipstr);
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(side).Append(" :side"));
	//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(dsport).Append(" :dsport"));
	//		UGameplayStatics::OpenLevel(GetWorld(), FName(ipstr+":"+FString::FromInt(dsport)));

 //           break;
 //       default:
 //           break;
 //       }
	//};

	//Async(EAsyncExecution::ThreadPool, [=]() {
	//	while (!channel->isConnected)
	//	{
	//		FPlatformProcess::Sleep(0.1f);
	//	}
	//	FString msg = "2225";
	//	TCHAR* arr = msg.GetCharArray().GetData();
	//	send((uint8)CMDPlayer::LOGIN, (uint8*)TCHAR_TO_UTF8(arr), FCString::Strlen(arr));
	//	FPlatformProcess::Sleep(2.1f);

	//}, nullptr);

}
void ALoginActor::matchbegin()
{
	FString msg = "2225";
	TCHAR* arr = msg.GetCharArray().GetData();
	send((uint8)CMDPlayer::MATCHREQUEST, (uint8*)TCHAR_TO_UTF8(arr), FCString::Strlen(arr));
}
void ALoginActor::send(const uint8 command, uint8* data,  uint16 size)
{
	buffer[0] = command;
	FMemory::Memcpy(buffer + 1, data, size);
	channel->Send((const char*)buffer,size+1);
}


// Called every frame
void ALoginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

