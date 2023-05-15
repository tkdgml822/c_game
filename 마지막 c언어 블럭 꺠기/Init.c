#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "MyVariable.h"
#include <mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"

void Init() {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = { 0 };


	if (g_nStage == -1) {	//	���������� -1 �ϰ��

		g_nStage = 0;		//	���������� 0���� �ٲ� 

	}
	
	// �ʱ�ȭ
	mysql_init(&con);


	// mysql ����
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);

	if (connection == NULL) {
		gotoxy(50, 1); fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();

		return 0;
	}

	mysql_query(connection, "select user_score from user order by user_score desc limit 1;");

	result = mysql_store_result(connection);

	if ((row = mysql_fetch_row(result)) != NULL) {
		g_nBestGrade = atoi(row[0]); // ����� ������ ��ȯ�Ͽ� ������ ����
		printf("���� ���� ����: %d\n", g_nBestGrade);
		_getch();
	}

	//// database�� �߰��Ǹ� ���� ����
	//FILE* file = fopen("score.dat", "rt");
	//if (file == 0) { g_nBestGrade = 0; }
	//else {
	//	fscanf(file, "%d", &g_nBestGrade);
	//	fclose(file);
	//}


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
	g_sBar.MoveTime = 0.05;									// ������� �ӵ� 1�� ����
	g_sBar.OldTime = clock();								// ���� �ð� OldTime�� ���

	g_nBlockCount = 0;										// ���� �ε��� �� 0
}