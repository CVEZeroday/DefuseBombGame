#include <stdio.h>
#include <WinSock2.h>
#include "NetworkingManager.h"
#include "macros.h"

//char NetworkBUF[BUFSIZE];
__int8 SendPack = -1; // 1�̸� ������ 0�̸� Ŭ���̾�Ʈ��
PacketType PackTypetmp;
char tmpData[BUFSIZE];
bool IsConnected = false;

int nRcv = 0;

void SendData(bool isServer, PacketType PackType, char *DataP) { 
	//SendPackto�� 1�̸� ������, 2�� Ŭ���̾�Ʈ��
	//QDATA Ȥ�� ADATA�� �����Ͱ� �Է�
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
	//#TODO ��Ʈ��ũ ���� �߻��� GameSystemCore�� ����
}