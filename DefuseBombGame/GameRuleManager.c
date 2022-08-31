#include <stdio.h>
#include "GameRuleManager.h"

extern bool IsGaming;
extern __int8 CorrectAnswer[4];
extern int TurnCount;

int interpretQuestionData(QDATA * Qdata, ADATA * Adata) { //Qdata와 Adata의 포인터를 입력으로 받음

	/*
	* Qdata값을 처리하여 Adata로 답변 출력
	*
	* return값이 0이면 정상 실행
	* return값이 1이면 게임 실행중이 아님
	*/

	if (!IsGaming)
		return 1; //게임 실행 중에만 작동
	//TODO: 예외 처리 

	int StrikeCount = 0;
	int BallCount = 0;

	// CorrectAnswer와 Qdata[TurnCount] 비교
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (Qdata[TurnCount].numset[i] == CorrectAnswer[j]) { //CorrectAnswer값과 Qdata->numset값에 겹치는 값이 있으면
				if (Qdata[TurnCount].numset[i] == CorrectAnswer[i])
					StrikeCount++; //위치까지 같으면 (Strike)
				else
					BallCount++; //위치는 다르면 (Ball)
			}
		}
	}
	

	if (StrikeCount == 0 && BallCount == 0) { // 0S 0B이면 아웃처리
		Adata[TurnCount].isOut = true;
		Adata[TurnCount].isWinner = false;
	}
	else if (StrikeCount == 4) { // 4S 0B이면 승리처리
		Adata[TurnCount].isOut = false;
		Adata[TurnCount].isWinner = true;
	}
	else { // 일반적 상황 처리
		Adata[TurnCount].isOut = false;
		Adata[TurnCount].isWinner = false;
	}
	Adata[TurnCount].Strike = StrikeCount;
	Adata[TurnCount].Ball = BallCount; //Adata 완성
	return 0;
}