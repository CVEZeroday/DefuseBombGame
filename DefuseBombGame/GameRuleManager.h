#pragma once

#include "macros.h" // 색상코드, bool 타입, 구조체

int interpretQuestionData(QDATA *Qdata, ADATA *Adata);
/*
* Qdata값을 처리하여 Adata로 답변 출력
* 
* return값이 0이면 정상 실행
* return값이 1이면 게임 실행중이 아님
*/