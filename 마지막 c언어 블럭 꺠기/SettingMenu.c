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

	int choice;  // �޴� ���� ���� 
	char sql[200]; // ������ �޴� ����
	char user_name[200]; // ���̵� �޴� ����
	char user_password[200]; // ��й�ȣ�� �޴� ����
	
	// �⺻ ȭ��
	init_interFace();
	
	// �޴�
	printf("���� Ȯ��  : 0");
	printf("�ű� ���� : 1");
	printf("�α��� : 2"); // �̱���
	scanf("%d", &choice);

	// �ű� ���Խ� 1 ��ȯ
	if (choice == 1) {
		return 1;
	}
	// 0�� �Է½� ���� Ȯ��
	else if (choice == 0) {
		while(1) {
			printf("���̵� :");
			scanf("%s", user_name);

			sprintf(sql, "select user_score from user where user_name = '%s';", user_name);
		
			// ���� ������ �� ����
			if (mysql_query(connection, sql)) {
				fprintf(stderr, "error: %s\n", mysql_error(connection));
				_getch();
				return;
			}

			// ��� ��������
			result = mysql_use_result(connection);

			// �ߺ��Ǵ� ���� �̸� �ִ��� Ȯ��
			if ((row = mysql_fetch_row(result)) == NULL) {
				printf("���� �� �Դϴ�. �ٽ� �Է����ּ���");
			}
			else {
				printf("���̵� : %s ���� ����: %s", user_name, row[0]);
				break;
			}
		}
	}
	// �α��� ���
	else if (choice == 2) {
		while (1) {
			gotoxy(8, 10);
			printf("���̵� :");
			scanf("%s", user_name);
			getchar();
			gotoxy(8, 11);
			printf("��й�ȣ :");
			scanf("%s", user_password);

			// ID�� ��й�ȣ�� ��ġ�ϴ��� Ȯ���ϴ� ������ �����մϴ�.
			sprintf(sql, "SELECT user_name, user_password FROM user WHERE user_name = '%s' and user_password = '%s';", user_name, user_password);

			// ���� ������ �� ����
			if (mysql_query(connection, sql)) {
				fprintf(stderr, "error: %s\n", mysql_error(connection));
				printf("�α��� ����! ���̵�, ��й�ȣ�� �ٽ� �Է� ���ּ���!");
				continue;
			}
			else {
				// ���
				result = mysql_store_result(connection);
				row = mysql_fetch_row(result);
				printf("%s��! ȯ���մϴ�!", row[0]);
				
				_getch();

				break;
			}

		}

	}
	else {
		return;
	}

	// ���� ����
	mysql_close(connection);
}