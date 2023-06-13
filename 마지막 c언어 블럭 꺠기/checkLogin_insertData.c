#include "MyVariable.h"
#include <mysql.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

void checkLogin_insertData(void) {
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
	 
	// �ְ� ������ �����ִ� ���� ���
	sprintf(sql, "select user_score from user order by user_score desc limit 1;");

	// ���� ������
	if (mysql_query(connection, sql)) { // ������ 0 ��ȯ
		fprintf(stderr, "error : %s\n", mysql_error(&con));
		_getch();
	};

	// ���� ���� ��� �� ���
	result = mysql_store_result(connection);

	init_interFace();
	
	if ((row = mysql_fetch_row(result)) != NULL) {
		gotoxy(6, 8);
		printf("��ŷ 1���� ����: %d\n", g_nBestGrade); // ���� ���� ���� ���
	}

	// ���� ������ �����ְ� �����͸� ���� ���� �����
	userBestScore();
	gotoxy(6, 10);
	printf("���� ������ %d�Դϴ�.\n", g_nlastGrade);
	gotoxy(6, 11);
	printf("�����͸� �����Ͻðڽ��ϱ�? (Y/N) : ");
	_getch();

	// ���� ���� ���
	char answer;
	scanf(" %c", &answer);

	if (answer == 'Y' || answer == 'y') {
		// �����͸� �����մϴ�.
		sprintf(sql, "update user set user_score= %d where user_name = '%s';", g_nlastGrade, login_name);
		if (mysql_query(connection, sql)) {
			fprintf(stderr, "error : %s\n", mysql_error(&con));
			_getch();
			mysql_close(connection);
			return;
		}
		gotoxy(6, 14);
		printf("������ �Է� ����!");

		mysql_close(connection);
		return;
	}
	else {
		gotoxy(6, 14);
		printf("������ ������ ����ϼ̽��ϴ�.");
	}

	mysql_close(connection);
	return;
}