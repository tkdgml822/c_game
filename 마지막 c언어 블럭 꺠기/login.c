#include "MyVariable.h"
#include <stdio.h>
#include <mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

// 로그인을 담당하는 함수
void login(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = { 0 };
	char sql[200];

	// 초기화
	mysql_init(&con);

	// mysql 연결
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// 연결 실패
	if (connection == NULL) {
		fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();
		return;
	}

	// 로그인
	while (1) {
		init_interFace();

		// 아이디 비밀번호 받기
		gotoxy(8, 10);
		printf("아이디 :");
		scanf("%s", user_name);
		getchar();	// 버퍼 삭제
		gotoxy(8, 11);
		printf("비밀번호 :");
		scanf("%s", user_password);

		// ID와 비밀번호가 일치하는지 확인하는 쿼리를 실행합니다.
		sprintf(sql, "SELECT user_name, user_password FROM user WHERE user_name = '%s' and user_password = '%s';", user_name, user_password);

		// 로그인 실패시 반복
		if (mysql_query(connection, sql)) { // 성공시 0 반환.
			fprintf(stderr, "error: %s\n", mysql_error(connection));
			continue;
		}
		
		// 결과
		result = mysql_store_result(connection);
		
		// 결과
		if (result == NULL) {
			printf("로그인 오류! 아이디, 비밀번호를 다시 입력 해주세요!");
			_getch();
		}
		else {
			row = mysql_fetch_row(result);

			if (row != NULL) {
				
				gotoxy(9, 10);
				printf("%s님! 환영합니다!", row[0]);
				sprintf(login_name, "%s", row[0]); // 로그인시 사용되는 변수
				logging = 1;
				Sleep(2000); //  

				// 유저의 점수 가져오기
				sql[0] = '\0';
				sprintf(sql, "select user_score from user where user_name = '%s';", user_name);
				if (mysql_query(connection, sql)) { // 성공시 0 반환.
					fprintf(stderr, "error: %s\n", mysql_error(connection));
				}
				result = mysql_store_result(connection);
				row = mysql_fetch_row(result);

				if (row != NULL) {
					sprintf(userScore, "%s", row[0]);
				}
				else {
					// row가 NULL인 경우에 대한 처리
					printf("로그인 오류 다시 입력해주세요!");
					// 예외 상황 또는 오류 처리를 수행해야 합니다.
				}

				// 접속 종료
				mysql_close(connection);
				return;

			}
		}
	}
}