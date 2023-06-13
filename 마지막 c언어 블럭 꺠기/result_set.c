#include <stdio.h>
#include <mysql.h>
#include "MyVariable.h"

#define DB_HOST "127.0.0.1" // ip
#define DB_USER "root"		// username
#define DB_PASS "abc123"	// userpassword
#define DB_NAME "test"		// tablename
#define DB_PORT 3306		// mySQLport

void result_set(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;

	// �ʱ�ȭ
	mysql_init(&con);

	// ����
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// ���� ����
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
	
	gotoxy(5, 10);
	printf("�����Ͱ� ���������� �ԷµǾ����ϴ�.\n");

	if (g_nlastGrade > g_nBestGrade) {									// ���������� �ְ� ����(g_nBestGrade)���� ���ο� ����(g_nlastGrade)�� ������ Ȯ���մϴ�.
		ScreenPrint(10, 13, "-------BEST SCORE !!-------");				// ȭ�鿡 �޽����� ����մϴ�.
		g_nlastGrade = 0;												// ���ο� �ְ� ������ ����� ��, ������ ����(g_nlastGrade)�� 0���� �ʱ�ȭ�մϴ�.
	}

	resultValue == 1;

	// ���� ����
	mysql_close(connection);
	return;
}