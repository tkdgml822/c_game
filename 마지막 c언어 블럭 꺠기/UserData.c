#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void UserDate_show_data(void) {
	gotoxy(0,  0); printf("�âââââââââââââââââââââââââââââââââââââââââ�");
	gotoxy(0,  1); printf("��                                        ��");
	gotoxy(0,  2); printf("��                                        ��");
	gotoxy(0,  3); printf("��                                        ��");
	gotoxy(0,  4); printf("��                                        ��");
	gotoxy(0,  5); printf("��                                        ��");
	gotoxy(0,  6); printf("��                                        ��");
	gotoxy(0,  7); printf("��                                        ��");
	gotoxy(0,  8); printf("��                                        ��");
	gotoxy(0,  9); printf("��                                        ��");
	gotoxy(0, 10); printf("��                                        ��");
	gotoxy(0, 11); printf("��                                        ��");
	gotoxy(0, 12); printf("��                                        ��");
	gotoxy(0, 13); printf("��                                        ��");
	gotoxy(0, 14); printf("��                                        ��");
	gotoxy(0, 15); printf("��                                        ��");
	gotoxy(0, 16); printf("��                                        ��");
	gotoxy(0, 17); printf("��                                        ��");
	gotoxy(0, 18); printf("��                                        ��");
	gotoxy(0, 19); printf("��                                        ��");
	gotoxy(0, 20); printf("��                                        ��");
	gotoxy(0, 21); printf("��                                        ��");
	gotoxy(0, 22); printf("��                                        ��");
	gotoxy(0, 23); printf("�âââââââââââââââââââââââââââââââââââââââââ�");
}

int UserData(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = { 0 };
	int i = 3;

	UserDate_show_data(); // ȭ�� ���
	
	mysql_init(&con); // �ʱ�ȭ

	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0); // ����

	if (connection == NULL) {
		gotoxy(50, 1); fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();

		return 0;
	}

	mysql_query(connection, "select * from user order by user_score desc limit 10;");
	result = mysql_store_result(connection);

	gotoxy(0, 1); printf("��       Name               score         ��");
	gotoxy(0, 2); printf("�� ====================================== ��");
	while ((row = mysql_fetch_row(result)) != NULL) { // null�� �ƴҶ� ���� �о�Ͷ�
		gotoxy(8, i); printf("%s                %s\n", row[1], row[3]);
		i += 2;
	}

	gotoxy(14, 21);
	printf("�ƹ� Ű�� �Է�");
	_getch();

	mysql_close(connection);

	return 1;
}