#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"


int UserData(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = { 0 };

	// �ʱ�ȭ
	mysql_init(&con);

	// ����
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);

	if (connection == NULL) {
		fprintf(stderr, "error: %s\n", mysql_error(&con));
		printf("%s", mysql_error(&con));

		return 0;
	}

	mysql_query(connection, "select * from user");
	result = mysql_store_result(connection);

	printf("==========================\n");
	printf("   �̸�            ����\n");
	printf("==========================\n");

	while ((row = mysql_fetch_row(result)) != NULL) { // null�� �ƴҶ� ���� �о�Ͷ�
		printf("   %s              %s\n", row[0], row[1]);
	}
	printf("==========================\n");

	printf("�� ��� �ƹ� Ű�� �Է�");
	_getch();

	return 1;
}