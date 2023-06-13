#include "MyVariable.h"
#include <stdio.h>
#include <mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

// �α����� ����ϴ� �Լ�
void login(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = { 0 };
	char sql[200];

	// �ʱ�ȭ
	mysql_init(&con);

	// mysql ����
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// ���� ����
	if (connection == NULL) {
		fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();
		return;
	}

	// �α���
	while (1) {
		init_interFace();

		// ���̵� ��й�ȣ �ޱ�
		gotoxy(8, 10);
		printf("���̵� :");
		scanf("%s", user_name);
		getchar();	// ���� ����
		gotoxy(8, 11);
		printf("��й�ȣ :");
		scanf("%s", user_password);

		// ID�� ��й�ȣ�� ��ġ�ϴ��� Ȯ���ϴ� ������ �����մϴ�.
		sprintf(sql, "SELECT user_name, user_password FROM user WHERE user_name = '%s' and user_password = '%s';", user_name, user_password);

		// �α��� ���н� �ݺ�
		if (mysql_query(connection, sql)) { // ������ 0 ��ȯ.
			fprintf(stderr, "error: %s\n", mysql_error(connection));
			continue;
		}
		
		// ���
		result = mysql_store_result(connection);
		
		// ���
		if (result == NULL) {
			printf("�α��� ����! ���̵�, ��й�ȣ�� �ٽ� �Է� ���ּ���!");
			_getch();
		}
		else {
			row = mysql_fetch_row(result);

			if (row != NULL) {
				
				gotoxy(9, 10);
				printf("%s��! ȯ���մϴ�!", row[0]);
				sprintf(login_name, "%s", row[0]); // �α��ν� ���Ǵ� ����
				logging = 1;
				Sleep(2000); //  

				// ������ ���� ��������
				sql[0] = '\0';
				sprintf(sql, "select user_score from user where user_name = '%s';", user_name);
				if (mysql_query(connection, sql)) { // ������ 0 ��ȯ.
					fprintf(stderr, "error: %s\n", mysql_error(connection));
				}
				result = mysql_store_result(connection);
				row = mysql_fetch_row(result);

				if (row != NULL) {
					sprintf(userScore, "%s", row[0]);
				}
				else {
					// row�� NULL�� ��쿡 ���� ó��
					printf("�α��� ���� �ٽ� �Է����ּ���!");
					// ���� ��Ȳ �Ǵ� ���� ó���� �����ؾ� �մϴ�.
				}

				// ���� ����
				mysql_close(connection);
				return;

			}
		}
	}
}