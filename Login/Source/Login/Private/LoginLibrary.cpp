// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginLibrary.h"
#include "LoginProxy.h"
FString ULoginLibrary::ipaddress = "192.168.31.252";
int ULoginLibrary::portnumber = 6999;
int ULoginLibrary::state = 0;

void ULoginLibrary::setipaddress(FString ip, int port)
{
	ULoginLibrary::ipaddress = ip;
	ULoginLibrary::portnumber = port;
	ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber);
}
bool ULoginLibrary::isconnected()
{
	return ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber)->isconnected();
}
void ULoginLibrary::singup(const FString& msg)
{
	const TCHAR* arr = msg.GetCharArray().GetData();
	ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber)->send((uint8)ULoginProxy::CMDPlayer::SINGUP, (uint8*)TCHAR_TO_UTF8(arr), FCString::Strlen(arr));
}
void ULoginLibrary::singin(const FString& msg)
{
	const TCHAR* arr = msg.GetCharArray().GetData();
	ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber)->send((uint8)ULoginProxy::CMDPlayer::LOGIN, (uint8*)TCHAR_TO_UTF8(arr), FCString::Strlen(arr));
}
void ULoginLibrary::matchrequest(int halfroomnumber)
{
	ULoginLibrary::state = 1;
	uint8 buffer[4] = { 0 };
	FMemory::Memcpy(buffer, &halfroomnumber, 4);
	ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber)->send((uint8)ULoginProxy::CMDPlayer::MATCHREQUEST, buffer, 4);
}
void ULoginLibrary::createroomquest()
{
	ULoginLibrary::state = 2;
	uint8 buffer[4] = { 0 };
	ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber)->send((uint8)ULoginProxy::CMDPlayer::CREATEROOM, buffer, 4);
}
void ULoginLibrary::joinroomquest(int roomid)
{
	ULoginLibrary::state = 3;
	uint8 buffer[4] = { 0 };
	FMemory::Memcpy(buffer, &roomid, 4);
	ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber)->send((uint8)ULoginProxy::CMDPlayer::JOINROOM, buffer, 4);
}
void ULoginLibrary::startgame(int roomid)
{
	uint8 buffer[4] = { 0 };
	FMemory::Memcpy(buffer, &roomid, 4);
	ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber)->send((uint8)ULoginProxy::CMDPlayer::STARTGAME, buffer, 4);
}
void ULoginLibrary::reconnectlogin(const FString& msg)
{
	const TCHAR* arr = msg.GetCharArray().GetData();
	ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber)->send((uint8)ULoginProxy::CMDPlayer::RECONNECTLOGIN, (uint8*)TCHAR_TO_UTF8(arr), FCString::Strlen(arr));
}
void ULoginLibrary::reconnect(int halfroomnumber)
{
	ULoginProxy* lp = ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber);
	uint8 buffer[12] = { 0 };
	FMemory::Memcpy(buffer, &lp->selfid, 4);
	FMemory::Memcpy(buffer + 4, &lp->roomid, 4);
	FMemory::Memcpy(buffer + 8, &halfroomnumber, 4);
	lp->send((uint8)ULoginProxy::CMDPlayer::RECONNECT, buffer, 12);
}
void ULoginLibrary::reconnectv1(bool owner)
{
	int iowner = owner ? 1 : 0;
	ULoginProxy* lp = ULoginProxy::LoginProxy(ULoginLibrary::ipaddress, ULoginLibrary::portnumber);
	uint8 buffer[12] = { 0 };
	FMemory::Memcpy(buffer, &lp->selfid, 4);
	FMemory::Memcpy(buffer + 4, &lp->roomid, 4);
	FMemory::Memcpy(buffer + 8, &iowner, 4);
	lp->send((uint8)ULoginProxy::CMDPlayer::RECONNECTV1, buffer, 12);
}