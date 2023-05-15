#define _CRT_SECURE_NO_WARNINGS
#include "MyVariable.h"
#include <stdio.h>
#include <mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"

// ȭ�� ǥ��
void Render() {
	char string[100];			// ���ڿ�
	MYSQL con = { 0 };
	MYSQL* connection = NULL;

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

	case RESULT:															// ���
		ResultScreen();														// ��� ȭ��
		sprintf_s(string, sizeof(string), "%d", g_nGrade);					// ����������(����) ���ڿ��� ����
		ScreenPrint(25, 11, string);										// ����� ���ڿ� ���
		g_nlastGrade = g_nGrade;											// ���� ���� ������ �������ٰ� ����

		MYSQL con = { 0 };
		MYSQL* connection = NULL;

		mysql_init(&con);

		connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);
		if (connection == NULL) {
			fprintf(stderr, "error: %s\n", mysql_error(&con));
			_getch();
			return;
		}

		char query[200];
		sprintf(query, "UPDATE user SET user_score = %d WHERE user_name = '%s' AND user_password = '%s';", g_nlastGrade, user_name, user_password);
		if (mysql_query(connection, query)) {
			fprintf(stderr, "error: %s\n", mysql_error(connection));
			_getch();
			return;
		}

		printf("�����Ͱ� ���������� �ԷµǾ����ϴ�.\n");

		if (g_nlastGrade > g_nBestGrade) {									// ���������� �ְ� ����(g_nBestGrade)���� ���ο� ����(g_nlastGrade)�� ������ Ȯ���մϴ�.
			ScreenPrint(10, 13, "-------BEST SCORE !!-------");				// ȭ�鿡 �޽����� ����մϴ�.
			g_nlastGrade = 0;												// ���ο� �ְ� ������ ����� ��, ������ ����(g_nlastGrade)�� 0���� �ʱ�ȭ�մϴ�.
		}

		mysql_close(connection);
		break;																// Ż��																// Ż��
	}
	ScreenFlipping();														// ���� ��� ���� �ܼ� â ���ۿ� ������ ����� �ܼ� â ���۸� �����ư��� ȭ�鿡 �����ش�.(ȭ���� ��ü�ϴ� ����)
}