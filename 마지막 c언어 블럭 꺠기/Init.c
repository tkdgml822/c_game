#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "MyVariable.h"

void Init() {
	if (g_nStage == -1) {	//	���������� -1 �ϰ��

		g_nStage = 0;		//	���������� 0���� �ٲ� 

	}

	// ������ ��� ���� ���� �����͸� �о��.
	// ������ �÷����ϸ鼭 ����� �ְ� ������ �����ϰ� �ִ� ���Ϸ� ����
	//  ������ �������� �ʴ� ��� (��, ������ ������ �÷������� ���� ���) g_nBestGrade ������ 0���� �ʱ�ȭ�մϴ�.
	// �׷��� ���� ��� ���Ͽ��� �о���� �ְ� ������ g_nBestGrade ������ �����մϴ�.
	FILE* file = fopen("score.dat", "rt");
	if (file == 0) { g_nBestGrade = 0; }
	else {
		fscanf(file, "%d", &g_nBestGrade);
		fclose(file);
	}


	SetBlock(g_StageInfo[g_nStage].nBlockCount);			// ���������� ���� ������ŭ ���� �������ش�.

	// �� �ʱ�ȭ
	g_sBall.nX = 19;										// ���� x�� ���� 19�� ����
	g_sBall.nHP = 3;										// ���� ü�� 3���� ����
	g_sBall.nY = 20;										// ���� Y�� 20���� ����
	g_sBall.nDirect = TOP;									// �⺻ ���� ���� ���� TOP���� ����
	g_sBall.OldTime = clock();								// ���� �ð� OldTime�� ���
	g_sBall.nReady = 1;										// �غ� �Ϸ� ����
	g_sBall.MoveTime = g_StageInfo[g_nStage].ball_MoveTime; // ���������� ���� �ӵ� ����

	// Note: ����� �ʱ�ȭ
	g_sBar.nY = g_sBall.nY + 1;								// ����� y�� ���� �ٷ� ������ �ʱ�ȭ 
	g_sBar.nX[0] = g_sBall.nX - 2;							// ����� ���� ��x �� -2�� ����
	g_sBar.nX[1] = g_sBall.nX;								// ����� �߰� x �� ��ġ�� �Ȱ��� ����
	g_sBar.nX[2] = g_sBall.nX + 2;							// ���� ������ ��x �� +2�� ����
	g_sBar.MoveTime = 1;									// ������� �ӵ� 1�� ����
	g_sBar.OldTime = clock();								// ���� �ð� OldTime�� ���

	g_nBlockCount = 0;										// ���� �ε��� �� 0
}