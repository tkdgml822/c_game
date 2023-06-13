#include <stdio.h>
#include <mysql.h>
#include "MyVariable.h"

#define DB_HOST "127.0.0.1" // ip
#define DB_USER "root"		// username
#define DB_PASS "abc123"	// userpassword
#define DB_NAME "test"		// tablename
#define DB_PORT 3306		// mySQLport

void result_set(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;

	// 초기화
	mysql_init(&con);

	// 연결
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// 연결 오류
	if (connection == NULL) {
		fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();
		return;
	}
	
	char query[200];

	sprintf(query, "UPDATE user SET user_score = %d WHERE user_name = '%s' AND user_password = '%s';", g_nlastGrade, user_name, user_password);
	if (mysql_query(connection, query)) {
		fprintf(stderr, "error: %s\n", mysql_error(connection));
		_getch();
		return;
	}
	
	gotoxy(5, 10);
	printf("데이터가 성공적으로 입력되었습니다.\n");

	if (g_nlastGrade > g_nBestGrade) {									// 이전까지의 최고 점수(g_nBestGrade)보다 새로운 점수(g_nlastGrade)가 높은지 확인합니다.
		ScreenPrint(10, 13, "-------BEST SCORE !!-------");				// 화면에 메시지를 출력합니다.
		g_nlastGrade = 0;												// 새로운 최고 점수를 기록한 후, 마지막 점수(g_nlastGrade)를 0으로 초기화합니다.
	}

	resultValue == 1;

	// 연결 끊기
	mysql_close(connection);
	return;
}