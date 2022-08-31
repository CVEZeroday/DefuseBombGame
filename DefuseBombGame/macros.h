#pragma once
#include <stdbool.h>

#define BLACK 0;
#define DARKBLUE 1;
#define DARKGREEN 2;
#define DARKSKYBLUE 3;
#define DARKRED 4;
#define DARKPURPLE 5;
#define DARKYELLOW 6;
#define GRAY 7;
#define DARKGRAY 8;
#define BLUE 9;
#define GREEN 10;
#define SKYBLUE 11;
#define RED 12;
#define PURPLE 13;
#define YELLOW 14;
#define WHITE 15; //색상 코드

//네트워크버퍼 패킷타입
typedef enum PacketType {
	QuestionDatatype = 0,
	AnswerDatatype,
	ChattingDatatype,
	SHUTDOWN
} PacketType;

typedef struct question_data {
	__int8 numset[4];
} QDATA;
/*
* 질문 구조체
* numset은 __int8 4바이트 배열, 각각 0~9
* 4byte
*/

typedef struct answer_data {
	__int8 Strike;
	__int8 Ball;
	bool isWinner;
	bool isOut;
} ADATA;
/*
* 답변 구조체
* IsOut: 아웃인지 여부
* Strike: 스트라이크 수
* Ball: 볼 수
* IsWinner: 승리 여부
* 4byte
*/