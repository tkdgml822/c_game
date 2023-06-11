#include "MyVariable.h"
#include "functions.h"
#include <mysql.h>

#define DB_HOST "127.0.0.1" // ip
#define DB_USER "root"		// username
#define DB_PASS "abc123"	// userpassword
#define DB_NAME "test"		// tablename
#define DB_PORT 3306		// mySQLport

// �޴��� ���� �Լ�
int SettingMenu(void) {
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

	int choice;  // �޴� ����
	
	// �⺻ ȭ��
	init_interFace();

	// �޴�
	while (1) {
		gotoxy(13, 10);
		printf("���� Ȯ�� : 0");
		gotoxy(13, 11);
		printf("�ű� ���� : 1");
		gotoxy(13, 12);
		printf("�α���    : 2");
		gotoxy(13, 13);
		printf("����      : ");
		scanf("%d", &choice);

		if (choice > 3) {
			printf("�ٽ� �Է����ּ���");
			continue;
		}
		else {
			break;
		}
	}

	// �ű� ���Խ� 1 ��ȯ
	if (choice == 1) {
		mysql_close(connection);
		return 1;
	}
	// 0�� �Է½� ���� Ȯ��
	else if (choice == 0) {
		score_check(); // ���� Ȯ��

		init_interFace();
		gotoxy(13, 11);
		printf("�ű� ���� : 1");
		gotoxy(13, 12);
		printf("�α���    : 2");
		gotoxy(13, 13);
		printf("����      : ");
		scanf("%d", &choice);

		if (choice == 1) {
			mysql_close(connection);
			return 1;
		}
		else if (choice == 0) {
			login();
			mysql_close(connection);
			return;
		}

		return;
	}
	// �α��� ���
	else if (choice == 2) {
		login();
		mysql_close(connection);
		return;
	}



	// ���� ����
	mysql_close(connection);

	return;
}