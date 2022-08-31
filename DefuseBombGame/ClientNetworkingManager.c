#include <stdio.h>
#include <WinSock2.h>
#include "macros.h"
#include "NetworkingManager.h"
#pragma comment(lib, "ws2_32.lib") //LNK2019 해결!!!!!!! (사라져버린 내 2시간)
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
	serverAddr.sin_addr.s_addr = inet_addr(sAddr); // 입력 ip address char[15]값을 입력가능한 ip address 형태로 변경
	serverAddr.sin_port = htons(port);

	if (connect(clientSock, (void*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		ErrorHandling("Connection Error");
	else {
		IsConnected = true;
		//접속 성공시 GNM으로 넘기기
		printf("Connection Complete!");
	}

	NetworkBUF.PacketType = QuestionDatatype;

	while (IsConnected) { // 실행코드

		//recv
		nRcv = recv(clientSock, (char*)&NetworkBUF, sizeof(NetworkBUF)-1, 0);
		if (nRcv == SOCKET_ERROR) {
			ErrorHandling("Receive Error");
			break;
		}

		//received 내용 처리

		if (NetworkBUF.PacketType == QuestionDatatype) {
			//#TODO QuestionData 처리
		}
		else if (NetworkBUF.PacketType == AnswerDatatype) {
			//#TODO AnswerData 처리
		}
		else if (NetworkBUF.PacketType == ChattingDatatype) {
			//#TODO ChattingData 처리
			printf("%s", NetworkBUF.PacketData.chattingData);
		}
		else if (NetworkBUF.PacketType == SHUTDOWN) {
			break;
		}

		//received 내용 처리 end
		

		//데이터 전송
		if (SendPack == 0) { // __int8 SendPack, -1: 기본값, 0: 클라이언트, 1: 서버
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
		//데이터 전송 end

	}

	closesocket(clientSock);
	WSACleanup();
	
	//연결 종료

	return 0;
}