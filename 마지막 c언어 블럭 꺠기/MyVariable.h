#pragma once
#include "structure.h"

extern STAGE_INFO  g_StageInfo[3];	 // STAGE_INFO�� ����ü �迭�� �ʱ�ȭ�ϴ� �ڵ��Դϴ�.
extern BAR  g_sBar;  // ����� ����ü ����
extern BALL g_sBall; // �� ����ü ����

extern int g_nStage;		// g_nStage������ 3���� ���� �˷��ִ� ���� main�Լ��� ���ư��� 0���� �ʱ�ȭ�Ǹ� ���������� Ŭ���� �Ҷ����� 1�� �þ
// ���� �浹�ϰ� �Ǹ� ���� ����
extern int g_StateTable[4][6];
extern int			g_BlockState[6]; // ���� �ε����� ��, ���� ������ �����ϴµ� ���Ǵ� �迭�̴�.
extern BLOCK		g_sBlock[200]; // �� 200�� ����
extern GAME_STATE	g_nGameState;
extern int			g_nIsSuccess;
extern int			g_nGrade;			// ����
extern int			g_nBestGrade;		// �ְ�����
extern int			g_nlastGrade;
extern int			g_nStageCount;
extern clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime;
extern int			g_nTotalGrade;		// ����
extern int			g_nBlockCount;		// ���� ����