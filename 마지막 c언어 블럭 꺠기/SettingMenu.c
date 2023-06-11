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

	int choice;  // 메뉴 선택
	
	// 기본 화면
	init_interFace();

	// 메뉴
	while (1) {
		gotoxy(13, 10);
		printf("점수 확인 : 0");
		gotoxy(13, 11);
		printf("신규 가입 : 1");
		gotoxy(13, 12);
		printf("로그인    : 2");
		gotoxy(13, 13);
		printf("선택      : ");
		scanf("%d", &choice);

		if (choice > 3) {
			printf("다시 입력해주세요");
			continue;
		}
		else {
			break;
		}
	}

	// 신규 가입시 1 반환
	if (choice == 1) {
		mysql_close(connection);
		return 1;
	}
	// 0을 입력시 점수 확인
	else if (choice == 0) {
		score_check(); // 점수 확인

		init_interFace();
		gotoxy(13, 11);
		printf("신규 가입 : 1");
		gotoxy(13, 12);
		printf("로그인    : 2");
		gotoxy(13, 13);
		printf("선택      : ");
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
	// 로그인 기능
	else if (choice == 2) {
		login();
		mysql_close(connection);
		return;
	}



	// 접속 종료
	mysql_close(connection);

	return;
}