#include "MyVariable.h"
#include <mysql.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

void userBestScore(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result;
	MYSQL_ROW row;

	// �ʱ�ȭ
	mysql_init(&con);

	// ����
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// ���� Ȯ��
	if (connection == NULL) {
		fprintf(stderr, "error : %s\n", mysql_error(&con));
		_getch();
	}

	char sql[200];

	// ���� �ְ� ���� �����ֱ�  
	sprintf(sql, "select user_score from user where user_name = '%s';", login_name);

	// ���� ������
	if (mysql_query(connection, sql)) { // ������ 0 ��ȯ
		fprintf(stderr, "error : %s\n", mysql_error(&con));
		_getch();
	};

	// ���� ���� ��� �� ���
	result = mysql_store_result(connection);

	if ((row = mysql_fetch_row(result)) != NULL) {
		printf("���� %s�� ������� ���� : %s\n",login_name, row[0]);
	}

	mysql_close(connection);
	return;
}