#include <stdio.h>
#include <mysql.h>
#include "MyVariable.h"

#define DB_HOST "127.0.0.1" // ip
#define DB_USER "root"		// username
#define DB_PASS "abc123"	// userpassword
#define DB_NAME "test"		// tablename
#define DB_PORT 3306		// mySQLport

//������ ������ Ȯ���ϴ� �Լ��Դϴ�.
void score_check(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result;
	MYSQL_ROW row;

	char sql[200];

	// MySQL ���� �ʱ�ȭ
	mysql_init(&con);

	// MySQL ������ ����
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// ���� ���� ó��
	if (connection == NULL) {
		fprintf(stderr, "MySQL ���� ����: %s\n", mysql_error(&con));
		_getch();
		return;
	}

	while (1) {
		init_interFace();
		gotoxy(13, 11);
		printf("���̵� :");
		scanf("%s", user_name);

		sprintf(sql, "select user_score from user where user_name = '%s';", user_name);

		// ���� ������ �� ����
		if (mysql_query(connection, sql)) {
			fprintf(stderr, "error: %s\n", mysql_error(connection));
			_getch();
			break;
		}

		// ��� ��������
		result = mysql_use_result(connection);

		// �ߺ��Ǵ� ���� �̸� �ִ��� Ȯ��
		if ((row = mysql_fetch_row(result)) == NULL) {
			printf("���� �� �Դϴ�. �ٽ� �Է����ּ���");
		}
		else {
			gotoxy(4, 14);
			printf("���̵� : %s ���� ����: %s", user_name, row[0]);
			Sleep(2000);
			break;
		}
	}

	mysql_close(connection);
}