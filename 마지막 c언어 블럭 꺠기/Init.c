#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "MyVariable.h"

void Init() {
	if (g_nStage == -1) {	//	스테이지가 -1 일경우

		g_nStage = 0;		//	스테이지를 0으로 바꿈 

	}

	// 파일을 열어서 파일 내의 데이터를 읽어낸다.
	// 게임을 플레이하면서 저장된 최고 점수를 저장하고 있는 파일로 추측
	//  파일이 존재하지 않는 경우 (즉, 이전에 게임을 플레이하지 않은 경우) g_nBestGrade 변수를 0으로 초기화합니다.
	// 그렇지 않은 경우 파일에서 읽어들인 최고 점수를 g_nBestGrade 변수에 저장합니다.
	FILE* file = fopen("score.dat", "rt");
	if (file == 0) { g_nBestGrade = 0; }
	else {
		fscanf(file, "%d", &g_nBestGrade);
		fclose(file);
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
	g_sBar.MoveTime = 1;									// 막대기의 속도 1로 지정
	g_sBar.OldTime = clock();								// 현재 시간 OldTime에 담기

	g_nBlockCount = 0;										// 블럭이 부딪힌 수 0
}