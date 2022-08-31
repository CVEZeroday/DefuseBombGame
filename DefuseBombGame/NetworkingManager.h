#pragma once
#include <WinSock2.h>
#include "macros.h"

#define BUFSIZE 512

//NetworkingManager.c

void SendData(bool isServer, PacketType PackType, char (*DataP)[BUFSIZE]);
void ErrorHandling(char* message);

//extern char NetworkBUF[BUFSIZE];
extern __int8 SendPack;
extern PacketType PackTypetmp;
extern char (*DataPtmp)[BUFSIZE];
extern bool IsConnected;

//네트워크버퍼에 담을 패킷 데이터 구조체
typedef struct PacketData {
	__int8 int8[4];
	/*
	* QuestionData에서 숫자 세트로 사용
	* AnswerData에서는 순서대로 스트라이크, 볼, 승리여부 (1또는 0), 아웃여부 (1또는 0)으로 사용
	* ChattingData에서는 사용하지 않음
	* SHUTDOWN에서는 사용하지 않음
	*/
	char chattingData[BUFSIZE]; //512바이트 채팅버퍼, ChattingData 전용 버퍼
} PacketData;
//4byte

//네트워크 버퍼
typedef struct NetworkBUFFER {
	PacketType PacketType;
	PacketData PacketData;
} NetworkBUF;
//8byte


//ServerNetworkingManager.c

int runServerNetworkingService(int port);
extern int PlayerNum;

//ClientNetworkingManager.c

int runClientNetworkingService(char sAddr[15], int port);
