#include <stdio.h>
#include <WinSock2.h>
#include "macros.h"
#include "NetworkingManager.h"
#pragma comment(lib, "ws2_32.lib") //LNK2019 �ذ�!!!!!!! (��������� �� 2�ð�)
#define _WINSOCK_DEPRECATED_NO_WARNINGS

int runClientNetworkingService(char sAddr[15], int port) {
	
	WSADATA wsaData;
	SOCKET clientSock;
	SOCKADDR_IN serverAddr;

	static NetworkBUF NetworkBUF;
	
	extern bool IsConnected;
	static int nRcv = 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("Load WinSock 2.2 DLL Error");

	clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSock == INVALID_SOCKET)
		ErrorHandling("Socket Error");

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(sAddr); // �Է� ip address char[15]���� �Է°����� ip address ���·� ����
	serverAddr.sin_port = htons(port);

	if (connect(clientSock, (void*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		ErrorHandling("Connection Error");
	else {
		IsConnected = true;
		//���� ������ GNM���� �ѱ��
		printf("Connection Complete!");
	}

	NetworkBUF.PacketType = QuestionDatatype;

	while (IsConnected) { // �����ڵ�

		//recv
		nRcv = recv(clientSock, (char*)&NetworkBUF, sizeof(NetworkBUF)-1, 0);
		if (nRcv == SOCKET_ERROR) {
			ErrorHandling("Receive Error");
			break;
		}

		//received ���� ó��

		if (NetworkBUF.PacketType == QuestionDatatype) {
			//#TODO QuestionData ó��
		}
		else if (NetworkBUF.PacketType == AnswerDatatype) {
			//#TODO AnswerData ó��
		}
		else if (NetworkBUF.PacketType == ChattingDatatype) {
			//#TODO ChattingData ó��
			printf("%s", NetworkBUF.PacketData.chattingData);
		}
		else if (NetworkBUF.PacketType == SHUTDOWN) {
			break;
		}

		//received ���� ó�� end
		

		//������ ����
		if (SendPack == 0) { // __int8 SendPack, -1: �⺻��, 0: Ŭ���̾�Ʈ, 1: ����
			NetworkBUF.PacketType = PackTypetmp;
			if ((PackTypetmp == QuestionDatatype) || (PackTypetmp == AnswerDatatype)) {
				NetworkBUF.PacketData.int8[0] = (__int8)(*DataPtmp)[0];
				NetworkBUF.PacketData.int8[1] = (__int8)(*DataPtmp)[1];
				NetworkBUF.PacketData.int8[2] = (__int8)(*DataPtmp)[2];
				NetworkBUF.PacketData.int8[3] = (__int8)(*DataPtmp)[3];
			}
			else if (PackTypetmp == ChattingDatatype) {
				strcpy_s(*NetworkBUF.PacketData.chattingData, BUFSIZE, DataPtmp);
			}

			if (send(clientSock, (char*)&NetworkBUF, sizeof(NetworkBUF) - 1, 0) == SOCKET_ERROR) {
				ErrorHandling("Send Error");
				break;
			}
			SendPack = -1;
			PackTypetmp = 0;
			DataPtmp = 0;
		}
		//������ ���� end

	}

	closesocket(clientSock);
	WSACleanup();
	
	//���� ����

	return 0;
}