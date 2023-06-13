#include "structure.h"

STAGE_INFO  g_StageInfo[3] = {		 // STAGE_INFO의 구조체 배열을 초기화하는 코드입니다.
	{  30,   1 * 100 * 1000  , 140 }, // { 벽돌의 개수, 남은 시간, 공의 속도 }
	{  50,   2 * 100 * 1000 ,  100 },
	{ 100,   3 * 100 * 1000 ,   60 } };

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
GAME_STATE	g_nGameState = INIT;    // 기본 진행상태
// int			g_nIsSuccess = 0;		// 
int			g_nGrade = 0;			// 점수
int			g_nBestGrade = 0;		// 최고점수
int			g_nlastGrade = 0;		// 
int			g_nStageCount = 1;		// 스테이지 판단
clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime; // 게임에서 남은시간을 계산할때 쓰이는 
int			g_nTotalGrade = 0;		// 총점
int			g_nBlockCount = 0;		// 맞춘 벽돌
char		user_name[200];			// 유저 이름	
char		user_password[100];		// 유저 패스워드
char		login_name[100];		// 로그인
int			logging;				// 로그인 판단 여부
int			resultValue = 0;		// 게임 종료 판단
char		userScore[100];			// 유저의 스코어
int			newSignCheck;			// 회원가입인지 확인해주는 변수