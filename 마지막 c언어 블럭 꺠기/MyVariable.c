#include "structure.h"

STAGE_INFO  g_StageInfo[3] = {		 // STAGE_INFO의 구조체 배열을 초기화하는 코드입니다.
	{  30,   1 * 100 * 1000  , 140 }, // { 벽돌의 개수, 남은 시간, 공의 속도 }
	{  50,   2 * 100 * 1000 ,  100 },
	{ 100,   3 * 100 * 1000 ,   60 }};

BAR  g_sBar;  // 막대기 구조체 선언
BALL g_sBall; // 공 구조체 선언

int g_nStage = -1;		// g_nStage변수는 3개의 맵을 알려주는 변수 main함수가 돌아가면 0으로 초기화되면 스테이지를 클리어 할때마다 1씩 늘어남

// 벽과 충돌하게 되면 방향 상태
int g_StateTable[4][6] = {
   {  3,  2, -1, -1, -1,  4 },
   { -1,  5,  4, -1, -1, -1 },
   { -1, -1,  1,  0,  5, -1 },
   { -1, -1, -1, -1,  2,  1 }
};
int			g_BlockState[6] = { 3, 2, 1, 0, 5, 4 }; // 블럭이 부딪혔을 때, 공의 방향을 변경하는데 사용되는 배열이다.
BLOCK		g_sBlock[200]; // 블럭 200개 선언
GAME_STATE	g_nGameState = INIT;
int			g_nIsSuccess = 0;
int			g_nGrade = 0;			// 점수
int			g_nBestGrade = 0;		// 최고점수
int			g_nlastGrade = 0;
int			g_nStageCount = 1;
clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime;
int			g_nTotalGrade = 0;		// 총점
int			g_nBlockCount = 0;		// 맞춘 벽돌