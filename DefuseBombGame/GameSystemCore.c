#include <stdio.h>
#include "macros.h"
#include "GameSystemCore.h"
#include "GameRuleManager.h"
#include "NetworkingManager.h"
//#pragma warning(disable:4996)

bool IsGaming = true; //게임 중 여부
__int8 CorrectAnswer[4] = {-1,-1,-1,-1}; //초기 정답 NumSet, 답으로 0을 정할수 있기 때문에 초기화값을 -1로 설정함. 4byte
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
	QuestionData[0].numset[3] = 4; //1스트라이크 1볼

	QuestionData[1].numset[0] = 1;
	QuestionData[1].numset[1] = 3;
	QuestionData[1].numset[2] = 6;
	QuestionData[1].numset[3] = 7; //2스트라이크 1볼


	interpretQuestionData(QuestionData, AnswerData);

	printf("스트라이크: %d, 볼: %d, 아웃 여부: %d, 게임 종료 여부: %d", AnswerData[TurnCount].Strike, AnswerData[TurnCount].Ball, AnswerData[TurnCount].isOut, AnswerData[TurnCount].isWinner);
	
	
	int a;
	printf("입력:");
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