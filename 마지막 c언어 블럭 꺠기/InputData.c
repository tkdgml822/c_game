#include "MyVariable.h"
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

// ������ ������ �Է¹޴� �Լ�
void InputData(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* res;
	MYSQL_ROW row;

	// �ʱ�
	mysql_init(&con);

	// ����
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// ���� Ȯ��
	if (connection == NULL) {
		fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();
	}

	// ������ ���� char�� ���ڿ�
	char select[300];    
	char insert[200];


	// �⺻ȭ��
	init_interFace();

	// �ߺ� �̸�(ID) üũ

	while (1) {
		// ���� �̸� �Է�
		gotoxy(8, 4);
		printf("�̸� �Է�: ");
		scanf("%s", user_name); // gets(user_name);
		getchar();

		// ���� ���
		sprintf(select, "select user_name from user where user_name = '%s';", user_name);

		// ���� ������ �� ����
		if (mysql_query(connection, select)) {
			fprintf(stderr, "error: %s\n", mysql_error(connection));
			_getch();
			return;
		}

		// ��� ��������
		res = mysql_use_result(connection);

		// �ߺ��Ǵ� ���� �̸� �ִ��� Ȯ��
		if ((row = mysql_fetch_row(res)) == NULL) {
			printf("��� ������ �̸�(ID) �̸��Դϴ�!");
			break;
		}
		else {
			printf("�ٽ� �Է� ���ּ���");
		}
	}

	// ��й�ȣ �Է�
	gotoxy(8, 8);
	printf("��й�ȣ �Է�: ");
	gets(user_password);
	getchar();  // ���� ���� ����

	// �����ͺ��̽� ID, Password �Է�
	sprintf(insert, "insert into user(user_name, user_password) values('%s', '%s');", user_name, user_password);

	// �Է� ����
	if (mysql_query(connection, insert)) {
		fprintf(stderr, "error: %s\n", mysql_error(connection));
		_getch();
		return;
	}

	// �Է� ���� ����
	gotoxy(4, 20); printf("�����Ͱ� ���������� �ԷµǾ����ϴ�.\n");
	gotoxy(11, 22); printf("�ƹ� Ű�� �Է�");
	_getch();

	// ȭ�� Ŭ����
	system("cls");

	// ���� ����
	mysql_close(connection);
}
