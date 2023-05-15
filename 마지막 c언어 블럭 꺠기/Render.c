#define _CRT_SECURE_NO_WARNINGS
#include "MyVariable.h"
#include <stdio.h>
#include <mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "abc123"
#define DB_NAME "test"

// 화면 표시
void Render() {
	char string[100];			// 문자열
	MYSQL con = { 0 };
	MYSQL* connection = NULL;

	ScreenClear();				// 버퍼 삭제

	switch (g_nGameState) {		// 현재 게임 상태
	case INIT:					// 초기 상태 
		if (g_nStage == 0)		// 첫번째 맵일 경우
			InitScreen();		// 게임 소개 인터페이스
		break;					// 탈출

	case READY:					// 준비상태
		ReadyScreen();			// 준비상태 인터페이스
		sprintf_s(string, sizeof(string), "%d", g_nStage + 1); // 정수를 문자열로 변환 (스테이지)
		ScreenPrint(13, 7, string);	// 바뀐 문자열 화면 출력
		break;					// 탈출
	case RUNNING:				// 작동 중
		RunningScreen();		// 작동 중 일때 인터페이스

		sprintf_s(string, sizeof(string), "스테이지 : %d", g_nStage + 1);	// 정수형을 문자열로 변경(현재 스테이지)
		ScreenPrint(45, 2, string);											// 변경된 문자열 화면 출력

		sprintf_s(string, sizeof(string), "생명 : %d ", g_sBall.nHP);		// 정수형을 문자열로 변경(공의 체력)
		ScreenPrint(45, 4, string);											// 변경된 문자열 화면 출력

		sprintf_s(string, sizeof(string), "점수 : %d ", g_nGrade);			// 정수형을 문자열로 변경(점수)
		ScreenPrint(45, 6, string);											// 변경된 문자열 화면 출력

		sprintf_s(string, sizeof(string), "남은 시간 : %d 분 %d 초", g_RemainTime / 60, g_RemainTime % 60);// 시간을 문자열로 변경(분 초)
		ScreenPrint(45, 8, string);											// 변경된 문자열 화면 출력

		sprintf_s(string, sizeof(string), "BEST SCORE : %d", g_nBestGrade);	// 정수형을 문자열로 변경(최고점수)
		ScreenPrint(45, 10, string);										// 변경된 문자열 화면 출력


		for (int i = 0; i < g_StageInfo[g_nStage].nBlockCount; i++) {		// 블럭의 갯수만큼 반복
			if (g_sBlock[i].nLife == 1)										// 블럭의 체력이 1일때
				ScreenPrint(g_sBlock[i].nX, g_sBlock[i].nY, "▥");			// 반복되는 수만큼 화면 출력
		}

		for (int i = 0; i < 3; i++)											// 막대기의 블럭만큼 반복(3번)
		{
			SetColor(14);													// 막대기 색은 노란색
			ScreenPrint(g_sBar.nX[i], g_sBar.nY, "■");						// 막대기 출력
		}
		SetColor(14);														// 공의 색깔 노란색
		ScreenPrint(g_sBall.nX, g_sBall.nY, "●");							// 공출력
		SetColor(7);														// 색 다시 원상태로
		break;																// 탈출
	case SUCCESS:															// 성공 일시 
		SuccessScreen();													// 성공 인터페이스 출력
		sprintf_s(string, sizeof(string), "%d Stage", g_nStage + 1);		// 정수형 스테이지변수 문자열로 변경 
		ScreenPrint(19, 12, string);										// 변경된 문자열 출력
		sprintf_s(string, sizeof(string), "총점: %d", g_nGrade);			// 정수형 점수 문자열로 변경
		ScreenPrint(25, 16, string);										// 변경된 문자열 출력
		break;																// 탈출
	case FAILED:															// 실패시
		FailureScreen();													// 실패 인터페이스 뛰위기
		sprintf_s(string, sizeof(string), "%d Stage!", g_nStage + 1);		// 정수형 스테이지변수 문자열로 변경
		ScreenPrint(16, 4, string);											// 변경된 문자열 출력
		break;																// 탈출

	case RESULT:															// 결과
		ResultScreen();														// 결과 화면
		sprintf_s(string, sizeof(string), "%d", g_nGrade);					// 정수형변수(점수) 문자열로 변경
		ScreenPrint(25, 11, string);										// 변경된 문자열 출력
		g_nlastGrade = g_nGrade;											// 현재 점수 마지막 점수에다가 대입

		MYSQL con = { 0 };
		MYSQL* connection = NULL;

		mysql_init(&con);

		connection = mysql_real_connect(&con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);
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

		printf("데이터가 성공적으로 입력되었습니다.\n");

		if (g_nlastGrade > g_nBestGrade) {									// 이전까지의 최고 점수(g_nBestGrade)보다 새로운 점수(g_nlastGrade)가 높은지 확인합니다.
			ScreenPrint(10, 13, "-------BEST SCORE !!-------");				// 화면에 메시지를 출력합니다.
			g_nlastGrade = 0;												// 새로운 최고 점수를 기록한 후, 마지막 점수(g_nlastGrade)를 0으로 초기화합니다.
		}

		mysql_close(connection);
		break;																// 탈출																// 탈출
	}
	ScreenFlipping();														// 현재 사용 중인 콘솔 창 버퍼와 다음에 사용할 콘솔 창 버퍼를 번갈아가며 화면에 보여준다.(화면을 교체하는 역할)
}