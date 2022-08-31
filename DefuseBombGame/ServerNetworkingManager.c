#include <stdio.h>
#include <WinSock2.h>
#include "macros.h"
#include "NetworkingManager.h"
#pragma comment(lib, "ws2_32.lib") //LNK2019 해결!!!!!!! (사라져버린 내 2시간)

int runServerNetworkingService(int port) {


	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;

	static NetworkBUF NetworkBUF;

	extern bool IsConnected;
	static int nRcv = 0;
	static int fromLen = 0;

	int PlayerNum = 2;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) // ws2_32.dll 파일 초기화 WSAStartup()
		ErrorHandling("Load WinSock 2.2 DLL Error"); // USAGE : int WSAStartup( WORD wVersionRequested, LPWSADATA lpWSAData );


	serverSock = socket(PF_INET, SOCK_STREAM, 0);
	if (serverSock == INVALID_SOCKET)
		ErrorHandling("Socket Error");
	

	//serverAddr 구조체 정의
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN)); // serverAddr 구조체 메모리 할당
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serverSock, (void*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) // int bind(소켓, SOCKADDR_IN의 구조체 포인터, 두번째 인자 구조체 길이);
		ErrorHandling("Bind Error");


	if (listen(serverSock, PlayerNum) == SOCKET_ERROR) // 접속시도 listen
		ErrorHandling("Listen Error");

	//printf("ServerIsOn");

	fromLen = sizeof(clientAddr);

	clientSock = accept(serverSock, (void*)&clientAddr, &fromLen);
	if (clientSock == INVALID_SOCKET)
		ErrorHandling("Accept Error");
	else {
		IsConnected = true;
		//client 접속시 GNM으로 넘기기
		printf("Connection Complete!");
	}

	closesocket(serverSock); // 소켓 닫기

	while (IsConnected) { //
		/*
		* #TODO: SendData()함수와 while (IsConnected)부분 연결
		* HOW TO : SendData()함수에서 특정 변수값을 수정하면 여기 while(IsConnected)부분에서 if문으로 감지, send() 실행 후 변수값 초기화
		* #TODO: recv()를 통해 받은 NetworkBUF를 어떻게 GSC.c로 올릴지, 어떻게 저장하여 GRM으로 넘어가게 할지 구현
		* HOW TO : GSC.h에서 불러온 게임데이터 변수에 값 대입
		*/
		
		if (recv(clientSock, (char*)&NetworkBUF, sizeof(NetworkBUF) - 1, 0) == SOCKET_ERROR) {
			//NetworkBUF 변수에 recv내용 저장, recv()함수의 리턴값은 받은 NetworkBUF의 길이
			ErrorHandling("Receive Error");
			break;
		}
		
		//received 내용 처리

		if (NetworkBUF.PacketType == QuestionDatatype) {
			//#TODO QuestionData 처리
			printf("debug");
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

		if (SendPack == 1) { // __int8 SendPack, -1: 기본값, 0: 클라이언트, 1: 서버
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

	//연결 종료

	return 0;
}
