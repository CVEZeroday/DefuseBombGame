#include <stdio.h>
#include "GameRuleManager.h"

extern bool IsGaming;
extern __int8 CorrectAnswer[4];
extern int TurnCount;

int interpretQuestionData(QDATA * Qdata, ADATA * Adata) { //Qdata�� Adata�� �����͸� �Է����� ����

	/*
	* Qdata���� ó���Ͽ� Adata�� �亯 ���
	*
	* return���� 0�̸� ���� ����
	* return���� 1�̸� ���� �������� �ƴ�
	*/

	if (!IsGaming)
		return 1; //���� ���� �߿��� �۵�
	//TODO: ���� ó�� 

	int StrikeCount = 0;
	int BallCount = 0;

	// CorrectAnswer�� Qdata[TurnCount] ��
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (Qdata[TurnCount].numset[i] == CorrectAnswer[j]) { //CorrectAnswer���� Qdata->numset���� ��ġ�� ���� ������
				if (Qdata[TurnCount].numset[i] == CorrectAnswer[i])
					StrikeCount++; //��ġ���� ������ (Strike)
				else
					BallCount++; //��ġ�� �ٸ��� (Ball)
			}
		}
	}
	

	if (StrikeCount == 0 && BallCount == 0) { // 0S 0B�̸� �ƿ�ó��
		Adata[TurnCount].isOut = true;
		Adata[TurnCount].isWinner = false;
	}
	else if (StrikeCount == 4) { // 4S 0B�̸� �¸�ó��
		Adata[TurnCount].isOut = false;
		Adata[TurnCount].isWinner = true;
	}
	else { // �Ϲ��� ��Ȳ ó��
		Adata[TurnCount].isOut = false;
		Adata[TurnCount].isWinner = false;
	}
	Adata[TurnCount].Strike = StrikeCount;
	Adata[TurnCount].Ball = BallCount; //Adata �ϼ�
	return 0;
}