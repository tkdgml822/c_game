#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

#define DB_HOST "127.0.0.1"
#define Db_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"

char user_name[200];
char user_password[100];



void InputData(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;

	mysql_init(&con);

	connection = mysql_real_connect(&con, DB_HOST, Db_USER, DB_PASS, DB_NAME, 3306, NULL, 0);
	
	if (connection == NULL) {
		//gotoxy(50, 1);
		fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();
	}


	UserDate_show_data();

	gotoxy(8, 4);
	printf("�̸� �Է�: ");
	scanf("%s", user_name);
	gotoxy(8, 8);
	printf("��й�ȣ �Է�: ");
	scanf("%s", user_password);

	char query[200];
	sprintf(query, "insert into user(user_name, user_password) values('%s', '%s');", user_name, user_password);
	if (mysql_query(connection, query)) {
		fprintf(stderr, "error: %s\n", mysql_error(connection));
		_getch();
		return;
	}
	
	printf("�����Ͱ� ���������� �ԷµǾ����ϴ�.\n");
	printf("�ƹ� Ű�� �Է�");
	_getch();

	mysql_close(connection);
}