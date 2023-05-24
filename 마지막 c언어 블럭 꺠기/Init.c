#include <stdio.h>
#include <mysql.h>
#include <stdlib.h>
#include "MyVariable.h"

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"
#define DB_PORT 3306

void Init() {
	MYSQL con = { 0 };
	MYSQL* connection = NULL;
	MYSQL_RES* result = NULL;
	MYSQL_ROW row = { 0 };
	char sql[200];


	if (g_nStage == -1) {	//	스테이지가 -1 일경우
		g_nStage = 0;		//	스테이지를 0으로 바꿈 
	}

	// 초기화
	mysql_init(&con);

	// mysql 연결
	connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);

	if (connection == NULL) {
		gotoxy(50, 1); fprintf(stderr, "error: %s\n", mysql_error(&con));
		_getch();

		return 0;
	}

	sprintf(sql, "select user_score from user order by user_score desc limit 1;");
	mysql_query(connection, sql);

	result = mysql_store_result(connection);

	if ((row = mysql_fetch_row(result)) != NULL) {
		g_nBestGrade = atoi(row[0]); // 결과를 정수로 변환하여 변수에 저장
		init_interFace();
		gotoxy(8, 10);
		printf("현재 가장 높은 점수: %d\n", g_nBestGrade); // 가장 높은 점수 출력
	}

	SetBlock(g_StageInfo[g_nStage].nBlockCount);			// 스테이지별 블럭의 갯수만큼 블럭을 세팅해준다.

	// 공 초기화
	g_sBall.nX = 19;										// 공의 x축 방향 19로 지정
	g_sBall.nHP = 3;										// 공의 체력 3으로 지정
	g_sBall.nY = 20;										// 공의 Y축 20으로 지정
	g_sBall.nDirect = TOP;									// 기본 값을 위쪽 방향 TOP으로 지정
	g_sBall.OldTime = clock();								// 현재 시간 OldTime에 담기
	g_sBall.nReady = 1;										// 준비 완료 상태
	g_sBall.MoveTime = g_StageInfo[g_nStage].ball_MoveTime; // 스테이지별 공의 속도 지정

	// Note: 막대기 초기화
	g_sBar.nY = g_sBall.nY + 1;								// 막대기 y축 공의 바로 밑으로 초기화 
	g_sBar.nX[0] = g_sBall.nX - 2;							// 막대기 왼쪽 공x 축 -2로 지정
	g_sBar.nX[1] = g_sBall.nX;								// 막대기 중간 x 공 위치랑 똑같이 지정
	g_sBar.nX[2] = g_sBall.nX + 2;							// 막대 오른쪽 공x 축 +2로 지정
	g_sBar.MoveTime = 0.05;									// 막대기의 속도 1로 지정
	g_sBar.OldTime = clock();								// 현재 시간 OldTime에 담기

	g_nBlockCount = 0;										// 블럭이 부딪힌 수 0
	gotoxy(8, 11);
	printf("초기화 성공! 아무키나 입력");
	_getch();

	mysql_close(connection);
}