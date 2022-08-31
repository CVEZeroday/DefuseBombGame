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
#define WHITE 15; //���� �ڵ�

//��Ʈ��ũ���� ��ŶŸ��
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
* ���� ����ü
* numset�� __int8 4����Ʈ �迭, ���� 0~9
* 4byte
*/

typedef struct answer_data {
	__int8 Strike;
	__int8 Ball;
	bool isWinner;
	bool isOut;
} ADATA;
/*
* �亯 ����ü
* IsOut: �ƿ����� ����
* Strike: ��Ʈ����ũ ��
* Ball: �� ��
* IsWinner: �¸� ����
* 4byte
*/