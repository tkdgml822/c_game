#pragma once
#include "structure.h"

extern STAGE_INFO  g_StageInfo[3];		// STAGE_INFO의 구조체 배열을 초기화하는 코드입니다.
extern BAR  g_sBar;						// 막대기 구조체 선언
extern BALL g_sBall;					// 공 구조체 선언

extern int			g_nStage;			// g_nStage변수는 3개의 맵을 알려주는 변수 main함수가 돌아가면 0으로 초기화되면 스테이지를 클리어 할때마다 1씩 늘어남
extern int			g_StateTable[4][6];	// 벽과 충돌하게 되면 방향 상태
extern int			g_BlockState[6];	// 블럭이 부딪혔을 때, 공의 방향을 변경하는데 사용되는 배열이다.
extern BLOCK		g_sBlock[200];		// 블럭 200개 선언
extern GAME_STATE	g_nGameState;		// 스테이지
extern int			g_nIsSuccess;		
extern int			g_nGrade;			// 점수
extern int			g_nBestGrade;		// 최고점수
extern int			g_nlastGrade;		// 마지막 점수
extern int			g_nStageCount;		// 스테이지 카운터
extern clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime;
extern int			g_nTotalGrade;		// 총점
extern int			g_nBlockCount;		// 맞춘 벽돌