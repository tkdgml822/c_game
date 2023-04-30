#include "structure.h"

STAGE_INFO  g_StageInfo[3] = {		 // STAGE_INFO�� ����ü �迭�� �ʱ�ȭ�ϴ� �ڵ��Դϴ�.
	{  30,   1 * 100 * 1000  , 140 }, // { ������ ����, ���� �ð�, ���� �ӵ� }
	{  50,   2 * 100 * 1000 ,  100 },
	{ 100,   3 * 100 * 1000 ,   60 }};

BAR  g_sBar;  // ����� ����ü ����
BALL g_sBall; // �� ����ü ����

int g_nStage = -1;		// g_nStage������ 3���� ���� �˷��ִ� ���� main�Լ��� ���ư��� 0���� �ʱ�ȭ�Ǹ� ���������� Ŭ���� �Ҷ����� 1�� �þ

// ���� �浹�ϰ� �Ǹ� ���� ����
int g_StateTable[4][6] = {
   {  3,  2, -1, -1, -1,  4 },
   { -1,  5,  4, -1, -1, -1 },
   { -1, -1,  1,  0,  5, -1 },
   { -1, -1, -1, -1,  2,  1 }
};
int			g_BlockState[6] = { 3, 2, 1, 0, 5, 4 }; // ���� �ε����� ��, ���� ������ �����ϴµ� ���Ǵ� �迭�̴�.
BLOCK		g_sBlock[200]; // �� 200�� ����
GAME_STATE	g_nGameState = INIT;
int			g_nIsSuccess = 0;
int			g_nGrade = 0;			// ����
int			g_nBestGrade = 0;		// �ְ�����
int			g_nlastGrade = 0;
int			g_nStageCount = 1;
clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime;
int			g_nTotalGrade = 0;		// ����
int			g_nBlockCount = 0;		// ���� ����