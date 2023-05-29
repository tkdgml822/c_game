#define _CRT_SECURE_NO_WARNINGS
#include "MyVariable.h"
#include <stdio.h>
#include <mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

// ȭ�� ǥ��
void Render() {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result;
	MYSQL_ROW row;

	char string[100];			// ���ڿ�
	
	ScreenClear();				// ���� ����

	switch (g_nGameState) {		// ���� ���� ����
	case INIT:					// �ʱ� ���� 
		if (g_nStage == 0)		// ù��° ���� ���
			InitScreen();		// ���� �Ұ� �������̽�
		break;					// Ż��

	case READY:					// �غ����
		ReadyScreen();			// �غ���� �������̽�
		sprintf_s(string, sizeof(string), "%d", g_nStage + 1); // ������ ���ڿ��� ��ȯ (��������)
		ScreenPrint(13, 7, string);	// �ٲ� ���ڿ� ȭ�� ���
		break;					// Ż��
	case RUNNING:				// �۵� ��
		RunningScreen();		// �۵� �� �϶� �������̽�

		sprintf_s(string, sizeof(string), "�������� : %d", g_nStage + 1);	// �������� ���ڿ��� ����(���� ��������)
		ScreenPrint(45, 2, string);											// ����� ���ڿ� ȭ�� ���

		sprintf_s(string, sizeof(string), "���� : %d ", g_sBall.nHP);		// �������� ���ڿ��� ����(���� ü��)
		ScreenPrint(45, 4, string);											// ����� ���ڿ� ȭ�� ���

		sprintf_s(string, sizeof(string), "���� : %d ", g_nGrade);			// �������� ���ڿ��� ����(����)
		ScreenPrint(45, 6, string);											// ����� ���ڿ� ȭ�� ���

		sprintf_s(string, sizeof(string), "���� �ð� : %d �� %d ��", g_RemainTime / 60, g_RemainTime % 60);// �ð��� ���ڿ��� ����(�� ��)
		ScreenPrint(45, 8, string);											// ����� ���ڿ� ȭ�� ���

		sprintf_s(string, sizeof(string), "BEST SCORE : %d", g_nBestGrade);	// �������� ���ڿ��� ����(�ְ�����)
		ScreenPrint(45, 10, string);										// ����� ���ڿ� ȭ�� ���


		for (int i = 0; i < g_StageInfo[g_nStage].nBlockCount; i++) {		// ���� ������ŭ �ݺ�
			if (g_sBlock[i].nLife == 1)										// ���� ü���� 1�϶�
				ScreenPrint(g_sBlock[i].nX, g_sBlock[i].nY, "��");			// �ݺ��Ǵ� ����ŭ ȭ�� ���
		}

		for (int i = 0; i < 3; i++)											// ������� ����ŭ �ݺ�(3��)
		{
			SetColor(14);													// ����� ���� �����
			ScreenPrint(g_sBar.nX[i], g_sBar.nY, "��");						// ����� ���
		}
		SetColor(14);														// ���� ���� �����
		ScreenPrint(g_sBall.nX, g_sBall.nY, "��");							// �����
		SetColor(7);														// �� �ٽ� �����·�
		break;																// Ż��
	case SUCCESS:															// ���� �Ͻ� 
		SuccessScreen();													// ���� �������̽� ���
		sprintf_s(string, sizeof(string), "%d Stage", g_nStage + 1);		// ������ ������������ ���ڿ��� ���� 
		ScreenPrint(19, 12, string);										// ����� ���ڿ� ���
		sprintf_s(string, sizeof(string), "����: %d", g_nGrade);			// ������ ���� ���ڿ��� ����
		ScreenPrint(25, 16, string);										// ����� ���ڿ� ���
		break;																// Ż��
	case FAILED:															// ���н�
		FailureScreen();													// ���� �������̽� ������
		sprintf_s(string, sizeof(string), "%d Stage!", g_nStage + 1);		// ������ ������������ ���ڿ��� ����
		ScreenPrint(16, 4, string);											// ����� ���ڿ� ���
		break;																// Ż��

	// ���
	case RESULT:
		ResultScreen();														// ��� ȭ��
		sprintf_s(string, sizeof(string), "%d", g_nGrade);					// �� ����(g_nGrade) string �������ٰ� ����
		ScreenPrint(25, 11, string);										// ����� ���ڿ� ���
		g_nlastGrade = g_nGrade;											// ���� ���� ������ �������ٰ� ����
		// �ű� ȸ���� ���
		result_set();
		

		resultValue = 1;			// ��� ��
		break;
	}
	ScreenFlipping();	// ���� ��� ���� �ܼ� â ���ۿ� ������ ����� �ܼ� â ���۸� �����ư��� ȭ�鿡 �����ش�.(ȭ���� ��ü�ϴ� ����)
}