#include "MyVariable.h"
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

// 유저의 정보를 입력받는 함수
void InputData(void) {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* res;
	MYSQL_ROW row;

	// 초기
	mysql_init(&con);

	// 연결
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	// 연결 확인
	if (connection == NULL) {
		fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();
	}

	// 쿼리를 받을 char형 문자열
	char select[300];    
	char insert[200];


	// 기본화면
	init_interFace();

	// 중복 이름(ID) 체크

	while (1) {
		// 유저 이름 입력
		gotoxy(8, 4);
		printf("이름 입력: ");
		scanf("%s", user_name); // gets(user_name);
		getchar();

		// 쿼리 담기
		sprintf(select, "select user_name from user where user_name = '%s';", user_name);

		// 쿼리 보내기 및 오류
		if (mysql_query(connection, select)) {
			fprintf(stderr, "error: %s\n", mysql_error(connection));
			_getch();
			return;
		}

		// 결과 가져오기
		res = mysql_use_result(connection);

		// 중복되는 유저 이름 있는지 확인
		if ((row = mysql_fetch_row(res)) == NULL) {
			printf("사용 가능한 이름(ID) 이름입니다!");
			break;
		}
		else {
			printf("다시 입력 해주세요");
		}
	}

	// 비밀번호 입력
	gotoxy(8, 8);
	printf("비밀번호 입력: ");
	gets(user_password);
	getchar();  // 개행 문자 제거

	// 데이터베이스 ID, Password 입력
	sprintf(insert, "insert into user(user_name, user_password) values('%s', '%s');", user_name, user_password);

	// 입력 실패
	if (mysql_query(connection, insert)) {
		fprintf(stderr, "error: %s\n", mysql_error(connection));
		_getch();
		return;
	}

	// 입력 성공 문구
	gotoxy(4, 20); printf("데이터가 성공적으로 입력되었습니다.\n");
	gotoxy(11, 22); printf("아무 키나 입력");
	_getch();

	// 화면 클리어
	system("cls");

	// 접속 종료
	mysql_close(connection);
}
