#include <stdio.h>
#include "macros.h"
#include "GameSystemCore.h"
#include "GameRuleManager.h"
#include "NetworkingManager.h"
//#pragma warning(disable:4996)

bool IsGaming = true; //���� �� ����
__int8 CorrectAnswer[4] = {-1,-1,-1,-1}; //�ʱ� ���� NumSet, ������ 0�� ���Ҽ� �ֱ� ������ �ʱ�ȭ���� -1�� ������. 4byte
QDATA QuestionData[20];
ADATA AnswerData[20];
int TurnCount = 0;


int debug(void) {

	CorrectAnswer[0] = 5;
	CorrectAnswer[1] = 8;
	CorrectAnswer[2] = 2;
	CorrectAnswer[3] = 4; 

	QuestionData[0].numset[0] = 1;
	QuestionData[0].numset[1] = 2;
	QuestionData[0].numset[2] = 3;
	QuestionData[0].numset[3] = 4; //1��Ʈ����ũ 1��

	QuestionData[1].numset[0] = 1;
	QuestionData[1].numset[1] = 3;
	QuestionData[1].numset[2] = 6;
	QuestionData[1].numset[3] = 7; //2��Ʈ����ũ 1��


	interpretQuestionData(QuestionData, AnswerData);

	printf("��Ʈ����ũ: %d, ��: %d, �ƿ� ����: %d, ���� ���� ����: %d", AnswerData[TurnCount].Strike, AnswerData[TurnCount].Ball, AnswerData[TurnCount].isOut, AnswerData[TurnCount].isWinner);
	
	
	int a;
	printf("�Է�:");
	scanf_s("%d", &a);
	char test1[BUFSIZE] = "asdf";

	if (a == 0) {
		runServerNetworkingService(4000);
	}
	if (a != 0) {
		runClientNetworkingService("127.0.0.1", 4000); //localhost ip address
		SendData(false, ChattingDatatype, &test1);
	}
	
	
	return 0;

}