#include "MyVariable.h"
#include <mysql.h>
#include <stdio.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

void checkLogin_insertData(void) {
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
	 
	// 최고 점수를 보여주는 퀴리 담기
	sprintf(sql, "select user_score from user order by user_score desc limit 1;");

	// 쿼리 보내기
	if (mysql_query(connection, sql)) { // 성공시 0 반환
		fprintf(stderr, "error : %s\n", mysql_error(&con));
		_getch();
	};

	// 보낸 쿼리 결과 값 담기
	result = mysql_store_result(connection);

	RunningScreen();
	
	if ((row = mysql_fetch_row(result)) != NULL) {
		printf("현재 가장 높은 점수: %d\n", g_nBestGrade); // 가장 높은 점수 출력
	}

	// 나의 점수를 보여주고 데이터를 갱신 여부 물어보기
		// userBestScore();
	printf("나의 점수는 %d입니다.\n", g_nlastGrade);
	printf("데이터를 갱신하시겠습니까? (Y/N)\n");
	_getch();

	// 갱신 여부 대답
	char answer;
	scanf(" %c", &answer);

	if (answer == 'Y' || answer == 'y') {
		// 데이터를 갱신합니다.
		sprintf(sql, "update user set user_score= %d where user_name = '%s';", g_nlastGrade, login_name);
		if (mysql_query(connection, sql)) {
			fprintf(stderr, "error : %s\n", mysql_error(&con));
			_getch();
			mysql_close(connection);
			return;
		}
		printf("데이터 입력 성공!");

		mysql_close(connection);
		return;
	}
	else {
		printf("데이터 갱신을 취소하셨습니다.");
	}

	mysql_close(connection);
	return;
}