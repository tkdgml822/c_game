#include <mysql.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define Db_USER "root"
#define DB_PSSS "abc123"
#define DB_NAME "test"

void InputData(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = { 0 };

	mysql_init(&con);

	connection = mysql_real_connect(&con, DB_HOST, Db_USER, DB_PSSS, DB_NAME, 3306, NULL, 0);
	
	if (connection == NULL) {
		gotoxy(50, 1); fprintf(stderr, "error: %s\n", mysql_error(&con));
	}
	
	char user_name[100];
	char user_password[100];
	printf("�̸� �Է�: ");
	scnaf("%s", user_name);
	printf("��й�ȣ �Է�: ");
	scanf("%s", user_password);


	mysql_query(connection, "insert into user(user_name, user_password, user_score) values('Sin', 'A1234', 600);");
}