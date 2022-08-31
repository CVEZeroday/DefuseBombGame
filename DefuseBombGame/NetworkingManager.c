#include <stdio.h>
#include <WinSock2.h>
#include "NetworkingManager.h"
#include "macros.h"

//char NetworkBUF[BUFSIZE];
__int8 SendPack = -1; // 1이면 서버측 0이면 클라이언트측
PacketType PackTypetmp;
char tmpData[BUFSIZE];
bool IsConnected = false;

int nRcv = 0;

void SendData(bool isServer, PacketType PackType, char *DataP) { 
	//SendPackto가 1이면 서버측, 2면 클라이언트측
	//QDATA 혹은 ADATA의 포인터값 입력
	if (IsConnected) {
		PackTypetmp = PackType;
		tmpData = *DataP;
		SendPack = (__int8)isServer;
		return;
	}
	else return;
}

void ErrorHandling(char* message) {
	WSACleanup();
	fputs(message, stderr);
	fputc('\n', stderr);
	//#TODO 네트워크 에러 발생시 GameSystemCore로 전송
}