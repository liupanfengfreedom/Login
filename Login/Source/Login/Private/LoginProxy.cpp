// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginProxy.h"
#include "ECSPBlueprintFunctionLibraryv1.h"
#include "Kcpclient.h"

Kcpclient* ULoginProxy::kcpclient = nullptr;
ULoginProxy::ULoginProxy()
{

}
ULoginProxy::~ULoginProxy()
{
	delete kcpclient;
}
void ULoginProxy::Activate()
{

}
ULoginProxy* ULoginProxy::LoginProxy(FString ip, int port)
{

	ULoginProxy* ret = UECSPBlueprintFunctionLibraryv1::GetUobjectsingleton<ULoginProxy>();
	if (!kcpclient)
	{
		auto tf = [=]() {
			kcpclient = new Kcpclient();
			ret->channel = kcpclient->CreateChannel(ip, port);
			ret->channel->onUserLevelReceivedCompleted = [=](const uint8* data, const uint16& size)->void {
				AsyncTask(ENamedThreads::GameThread,
					[=]()
					{
						int side;
						int dsport;
						int otherid;
						int otherside;
						int result;
						FString ipstr;
						FString selfinfor;
						switch ((ULoginProxy::CMDPlayer)data[0])
						{
						case ULoginProxy::CMDPlayer::SINGUP:

							ret->OnSingUpResult.Broadcast(0, 0, "SINGUP ok");
							if (ret->TFOnSingUpResult)
							{
								ret->TFOnSingUpResult(0, 0, "SINGUP ok");
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("SINGUP ok"));
							break;
						case ULoginProxy::CMDPlayer::LOGIN:
							ret->selfid = *(int*)(data + 1);
							selfinfor = FString(UTF8_TO_TCHAR(data + 5)).Left(size - 5);
							ret->OnSingInResult.Broadcast(0, ret->selfid, selfinfor);
							if (ret->TFOnSingInResult)
							{
								ret->TFOnSingInResult(0, ret->selfid, selfinfor);
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("LOGIN ok"));
							break;
						case ULoginProxy::CMDPlayer::CREATEROOM:
							ret->roomid = *(int*)(data + 1);
							ret->OnCreateRoomResult.Broadcast(0, ret->roomid, "");
							if (ret->TFOnCreateRoomResult)
							{
								ret->TFOnCreateRoomResult(0, ret->roomid, "");
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CREATEROOM"));
							break;
						case ULoginProxy::CMDPlayer::JOINROOM:
							ret->roomid = *(int*)(data + 1);
							ret->OnJoinRoomResult.Broadcast(0, ret->roomid, "");
							if (ret->TFOnJoinRoomResult)
							{
								ret->TFOnJoinRoomResult(0, ret->roomid, "");
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("JOINROOM"));
							break;
						case ULoginProxy::CMDPlayer::JOINROOMFAILED:
							ret->roomid = *(int*)(data + 1);
							ret->OnJoinRoomFailedResult.Broadcast(0, ret->roomid, "");
							if (ret->TFOnJoinRoomFailedResult)
							{
								ret->TFOnJoinRoomFailedResult(0, ret->roomid, "");
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("JOINROOMFAILED"));
							break;
						case ULoginProxy::CMDPlayer::STARTGAME:
							side = *(int*)(data + 1);
							dsport = *(int*)(data + 5);
							ret->roomid = *(int*)(data + 9);
							ipstr = FString(UTF8_TO_TCHAR(data + 13)).Left(size - 13);
							ret->OnStartGameResult.Broadcast(side, dsport, ipstr);
							if (ret->TFOnStartGameResult)
							{
								ret->TFOnStartGameResult(side, dsport, ipstr);
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("STARTGAME"));
							break;
						case ULoginProxy::CMDPlayer::MATCHREQUEST:
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("MATCHREQUEST ok"));
							side = *(int*)(data + 1);
							dsport = *(int*)(data + 5);
							ret->roomid = *(int*)(data + 9);
							ipstr = FString(UTF8_TO_TCHAR(data + 13)).Left(size - 13);
							ret->OnMatchrequestResult.Broadcast(side, dsport, ipstr);
							if (ret->TFOnMatchrequestResult)
							{
								ret->TFOnMatchrequestResult(side, dsport, ipstr);
							}
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ipstr);
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(side).Append(" :side"));
							GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(dsport).Append(" :dsport"));
							break;
						case ULoginProxy::CMDPlayer::OTHERPLAYERINFOR:
							otherid = *(int*)(data + 1);
							otherside = *(int*)(data + 5);
							ret->oldotherid = *(int*)(data + 9);
							ipstr = FString(UTF8_TO_TCHAR(data + 13)).Left(size - 13);
							ret->OnOtherplayerinfor.Broadcast(otherid, otherside, ipstr);
							if (ret->TFOnOtherplayerinfor)
							{
								ret->TFOnOtherplayerinfor(otherid, otherside, ipstr);
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("STARTGAME"));
							break;
						case ULoginProxy::CMDPlayer::RECONNECTLOGIN:
							ret->selfid = *(int*)(data + 1);
							ret->OnReConnectLoginResult.Broadcast(ret->selfid, 0, "");
							if (ret->TFOnReConnectLoginResult)
							{
								ret->TFOnReConnectLoginResult(ret->selfid, 0, "");
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("RECONNECTLOGIN"));
							break;
						case ULoginProxy::CMDPlayer::RECONNECT:
							ret->selfid = *(int*)(data + 1);
							result = *(int*)(data + 5);
							ret->OnReConnectResult.Broadcast(ret->selfid, result, "");
							if (ret->TFOnReConnectResult)
							{
								ret->TFOnReConnectResult(ret->selfid, result, "");
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("RECONNECT"));
							break;
						case ULoginProxy::CMDPlayer::RECONNECTV1:
							ret->selfid = *(int*)(data + 1);
							result = *(int*)(data + 5);
							ret->OnReConnectv1Result.Broadcast(ret->selfid, result, "");
							if (ret->TFOnReConnectv1Result)
							{
								ret->TFOnReConnectv1Result(ret->selfid, result, "");
							}
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("RECONNECTV1"));
							break;
						case ULoginProxy::CMDPlayer::CHECKCONNECTION:
							ret->b_connectionok = true;
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("CHECKCONNECTION"));
							break;
						default:
							break;
						}
					}
				);
			};
		};
		tf();
		FCoreDelegates::ApplicationHasEnteredForegroundDelegate.AddLambda([=]() {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("================= ApplicationHasEnteredForegroundDelegate"));
			if (ret->b_background)
			{
				ret->b_connectionok = false;
				ret->b_newchannel = false;
				ret->send((uint8)ULoginProxy::CMDPlayer::CHECKCONNECTION, (uint8*)ret, 0);
				ret->channel->isConnected = false;
				if (ret->TFOnAppEnterForeground)
				{
					ret->TFOnAppEnterForeground(0, 0, "");
				}
				Async(EAsyncExecution::ThreadPool, [=]() {
					FPlatformProcess::Sleep(1);
					if (ret->b_connectionok)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("b_connectionok"));
						ret->b_newchannel = false;
						ret->channel->isConnected = true;
					}
					else
					{
						delete kcpclient;
						tf();
						ret->b_newchannel = true;
						if (ret->TFOnReconnect)
						{
							ret->TFOnReconnect(0, 0, "");
						}
					}
				}, nullptr);
			}
			ret->b_background = false;
		});
		FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddLambda([=]() {
			ret->b_background = true;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("----------------- ApplicationWillEnterBackgroundDelegate"));
			if (ret->TFOnAppEnterBackground)
			{
				ret->TFOnAppEnterBackground(0, 0, "");
			}
		});
	}
	return ret;
}
bool ULoginProxy::isconnected()
{
	return channel->isConnected;
}
void ULoginProxy::send(const uint8 command, uint8* data, uint16 size)
{
	buffer[0] = command;
	FMemory::Memcpy(buffer + 1, data, size);
	channel->Send((const char*)buffer, size + 1);
}