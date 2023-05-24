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
	MYSQL_RES* res;
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
	
	// �⺻ ȭ��
	init_interFace();
	
	// �޴�
	printf("���� Ȯ��  : 0");
	printf("�ű� ���� : 1");
	printf("�α��� : 3"); // �̱���
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
			res = mysql_use_result(connection);

			// �ߺ��Ǵ� ���� �̸� �ִ��� Ȯ��
			if ((row = mysql_fetch_row(res)) == NULL) {
				printf("���� �� �Դϴ�. �ٽ� �Է����ּ���");
			}
			else {
				printf("���̵� : %s ���� ����: %s", user_name, row[0]);
				break;
			}
		}
	}
	else {
		// main������ ��
		return;
	}

	// ���� ����
	mysql_close(connection);
}