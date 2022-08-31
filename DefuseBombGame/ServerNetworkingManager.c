#include <stdio.h>
#include <WinSock2.h>
#include "macros.h"
#include "NetworkingManager.h"
#pragma comment(lib, "ws2_32.lib") //LNK2019 �ذ�!!!!!!! (��������� �� 2�ð�)

int runServerNetworkingService(int port) {


	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;

	static NetworkBUF NetworkBUF;

	extern bool IsConnected;
	static int nRcv = 0;
	static int fromLen = 0;

	int PlayerNum = 2;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // ws2_32.dll ���� �ʱ�ȭ WSAStartup()
		ErrorHandling("Load WinSock 2.2 DLL Error"); // USAGE : int WSAStartup( WORD wVersionRequested, LPWSADATA lpWSAData );


	serverSock = socket(PF_INET, SOCK_STREAM, 0);
	if (serverSock == INVALID_SOCKET)
		ErrorHandling("Socket Error");
	

	//serverAddr ����ü ����
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN)); // serverAddr ����ü �޸� �Ҵ�
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serverSock, (void*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) // int bind(����, SOCKADDR_IN�� ����ü ������, �ι�° ���� ����ü ����);
		ErrorHandling("Bind Error");


	if (listen(serverSock, PlayerNum) == SOCKET_ERROR) // ���ӽõ� listen
		ErrorHandling("Listen Error");

	//printf("ServerIsOn");

	fromLen = sizeof(clientAddr);

	clientSock = accept(serverSock, (void*)&clientAddr, &fromLen);
	if (clientSock == INVALID_SOCKET)
		ErrorHandling("Accept Error");
	else {
		IsConnected = true;
		//client ���ӽ� GNM���� �ѱ��
		printf("Connection Complete!");
	}

	closesocket(serverSock); // ���� �ݱ�

	while (IsConnected) { //
		/*
		* #TODO: SendData()�Լ��� while (IsConnected)�κ� ����
		* HOW TO : SendData()�Լ����� Ư�� �������� �����ϸ� ���� while(IsConnected)�κп��� if������ ����, send() ���� �� ������ �ʱ�ȭ
		* #TODO: recv()�� ���� ���� NetworkBUF�� ��� GSC.c�� �ø���, ��� �����Ͽ� GRM���� �Ѿ�� ���� ����
		* HOW TO : GSC.h���� �ҷ��� ���ӵ����� ������ �� ����
		*/
		
		if (recv(clientSock, (char*)&NetworkBUF, sizeof(NetworkBUF) - 1, 0) == SOCKET_ERROR) {
			//NetworkBUF ������ recv���� ����, recv()�Լ��� ���ϰ��� ���� NetworkBUF�� ����
			ErrorHandling("Receive Error");
			break;
		}
		
		//received ���� ó��

		if (NetworkBUF.PacketType == QuestionDatatype) {
			//#TODO QuestionData ó��
			printf("debug");
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

		if (SendPack == 1) { // __int8 SendPack, -1: �⺻��, 0: Ŭ���̾�Ʈ, 1: ����
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
		
	}

	closesocket(clientSock);
	WSACleanup();

	//���� ����

	return 0;
}
