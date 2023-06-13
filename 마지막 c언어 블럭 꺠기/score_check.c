#include <stdio.h>
#include <mysql.h>
#include "MyVariable.h"

#define DB_HOST "127.0.0.1" // ip
#define DB_USER "root"		// username
#define DB_PASS "abc123"	// userpassword
#define DB_NAME "test"		// tablename
#define DB_PORT 3306		// mySQLport

//유저가 점수를 확인하는 함수입니다.
void score_check(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result;
	MYSQL_ROW row;

	char sql[200];

	// MySQL 연결 초기화
	mysql_init(&con);

	// MySQL 서버에 연결
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// 연결 오류 처리
	if (connection == NULL) {
		fprintf(stderr, "MySQL 연결 오류: %s\n", mysql_error(&con));
		_getch();
		return;
	}

	while (1) {
		init_interFace();
		gotoxy(13, 11);
		printf("아이디 :");
		scanf("%s", user_name);

		sprintf(sql, "select user_score from user where user_name = '%s';", user_name);

		// 쿼리 보내기 및 오류
		if (mysql_query(connection, sql)) {
			fprintf(stderr, "error: %s\n", mysql_error(connection));
			_getch();
			break;
		}

		// 결과 가져오기
		result = mysql_use_result(connection);

		// 중복되는 유저 이름 있는지 확인
		if ((row = mysql_fetch_row(result)) == NULL) {
			printf("없는 값 입니다. 다시 입력해주세요");
		}
		else {
			gotoxy(4, 14);
			printf("아이디 : %s 현재 점수: %s", user_name, row[0]);
			Sleep(2000);
			break;
		}
	}

	mysql_close(connection);
}