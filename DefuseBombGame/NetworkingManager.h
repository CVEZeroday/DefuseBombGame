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

//��Ʈ��ũ���ۿ� ���� ��Ŷ ������ ����ü
typedef struct PacketData {
	__int8 int8[4];
	/*
	* QuestionData���� ���� ��Ʈ�� ���
	* AnswerData������ ������� ��Ʈ����ũ, ��, �¸����� (1�Ǵ� 0), �ƿ����� (1�Ǵ� 0)���� ���
	* ChattingData������ ������� ����
	* SHUTDOWN������ ������� ����
	*/
	char chattingData[BUFSIZE]; //512����Ʈ ä�ù���, ChattingData ���� ����
} PacketData;
//4byte

//��Ʈ��ũ ����
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
