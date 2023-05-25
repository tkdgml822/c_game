#include "MyVariable.h"
#include "functions.h"
#include <mysql.h>

#define DB_HOST "127.0.0.1" // ip
#define DB_USER "root"		// username
#define DB_PASS "abc123"	// userpassword
#define DB_NAME "test"		// tablename
#define DB_PORT 3306		// mySQLport

// 메뉴를 고르는 함수
int SettingMenu(void) {
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

	int choice;  // 메뉴 선택 변수 
	char sql[200]; // 쿼리를 받는 변수
	char user_name[200]; // 아이디 받는 변수
	char user_password[200]; // 비밀번호를 받는 변수
	
	// 기본 화면
	init_interFace();
	
	// 메뉴
	printf("점수 확인  : 0");
	printf("신규 가입 : 1");
	printf("로그인 : 2"); // 미구현
	scanf("%d", &choice);

	// 신규 가입시 1 반환
	if (choice == 1) {
		return 1;
	}
	// 0을 입력시 점수 확인
	else if (choice == 0) {
		while(1) {
			printf("아이디 :");
			scanf("%s", user_name);

			sprintf(sql, "select user_score from user where user_name = '%s';", user_name);
		
			// 쿼리 보내기 및 오류
			if (mysql_query(connection, sql)) {
				fprintf(stderr, "error: %s\n", mysql_error(connection));
				_getch();
				return;
			}

			// 결과 가져오기
			result = mysql_use_result(connection);

			// 중복되는 유저 이름 있는지 확인
			if ((row = mysql_fetch_row(result)) == NULL) {
				printf("없는 값 입니다. 다시 입력해주세요");
			}
			else {
				printf("아이디 : %s 현재 점수: %s", user_name, row[0]);
				break;
			}
		}
	}
	// 로그인 기능
	else if (choice == 2) {
		while (1) {
			gotoxy(8, 10);
			printf("아이디 :");
			scanf("%s", user_name);
			getchar();
			gotoxy(8, 11);
			printf("비밀번호 :");
			scanf("%s", user_password);

			// ID와 비밀번호가 일치하는지 확인하는 쿼리를 실행합니다.
			sprintf(sql, "SELECT user_name, user_password FROM user WHERE user_name = '%s' and user_password = '%s';", user_name, user_password);

			// 퀴리 보내기 및 오류
			if (mysql_query(connection, sql)) {
				fprintf(stderr, "error: %s\n", mysql_error(connection));
				printf("로그인 오류! 아이디, 비밀번호를 다시 입력 해주세요!");
				continue;
			}
			else {
				// 결과
				result = mysql_store_result(connection);
				row = mysql_fetch_row(result);
				printf("%s님! 환영합니다!", row[0]);
				
				_getch();

				break;
			}

		}

	}
	else {
		return;
	}

	// 접속 종료
	mysql_close(connection);
}