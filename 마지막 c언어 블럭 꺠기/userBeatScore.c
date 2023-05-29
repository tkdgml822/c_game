#include "MyVariable.h"
#include <mysql.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

void userBestScore(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result;
	MYSQL_ROW row;

	// 초기화
	mysql_init(&con);

	// 연결
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// 연결 확인
	if (connection == NULL) {
		fprintf(stderr, "error : %s\n", mysql_error(&con));
		_getch();
	}

	char sql[200];

	// 유저 최고 점수 보여주기  
	sprintf(sql, "select user_score from user where user_name = '%s';", login_name);

	// 쿼리 보내기
	if (mysql_query(connection, sql)) { // 성공시 0 반환
		fprintf(stderr, "error : %s\n", mysql_error(&con));
		_getch();
	};

	// 보낸 쿼리 결과 값 담기
	result = mysql_store_result(connection);

	if ((row = mysql_fetch_row(result)) != NULL) {
		printf("현재 %s의 가장높은 점수 : %s\n",login_name, row[0]);
	}

	mysql_close(connection);
	return;
}