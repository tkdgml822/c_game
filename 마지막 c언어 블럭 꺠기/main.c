#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include "structure.h"
#include "MyVariable.h"

// 같은 블럭 찾기
int Search(int nEnd, int nX, int nY) {										// (블럭의 갯수, 블럭의 x, 블럭의 y)
	for (int i = 0; i < nEnd; i++) {										// 블럭의 갯수 만큼 반복
		if (g_sBlock[i].nY == nY) {											// Y축이 같으면 X축 검사
			if (g_sBlock[i].nX == nX || (g_sBlock[i].nX + 1) == nX ||		// 찾으려는 블럭의 좌우로 한 칸씩 여유를 두어 검사
				g_sBlock[i].nX == nX + 1 || (g_sBlock[i].nX + 1) == nX + 1)
				return 1;													// 같은 것이 있으면 (반환 되서 받는 곳은 While문이라서 1이 반환되면 무한 루프)
		}
	}
	return 0;																// 같은 것이 없으면 (0 반환)
}

// RANDOM한 위치 안에서 블록을 입력 받은 개수만큼 표시
void SetBlock(int nBlockCount) {
	int nX, nY, i;							// 랜덤값을 받기위한 x, y, 반복문에 쓰이기 위한 i (int형으로 선언)

	srand((unsigned int)time(NULL));		// 랜덤값을 쓰기위한 시드값 설정

	for (i = 0; i < nBlockCount; i++) {		// 블럭 갯수 만큼 반복
		g_sBlock[i].nLife = 1;				// 블럭에 체력 1 대입

		while (1) {							// 무한 루프 (중복된 블럭이 있을시 무한 반복 없으면 코드 종료)
			nX = rand() % 39 + 2;			// 2 ~ 40 랜덤값 설정 (게임의 경계를 넘기지 않을려고 하기 위해 2부터 시작)
			nY = rand() % 10 + 1;			// 1 ~ 10 랜덤값 설정

			if (Search(i, nX, nY) == 0) {	// 같은 위치에 블럭이 생성되지 않기 위해 방지하는 코드
				g_sBlock[i].nX = nX;		// 중복된 값이 없으면 x에 배치 
				g_sBlock[i].nY = nY;		// 중복된 값이 없으면 y에 배치
				break;						// x, y에 블럭 배치후 while문 종료
			}
		}
	}
}

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

void Render() {
	char string[100];			// 문자열

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

		if (g_nlastGrade > g_nBestGrade) {									// 이전까지의 최고 점수(g_nBestGrade)보다 새로운 점수(g_nlastGrade)가 높은지 확인합니다.
			FILE* file = fopen("score.dat", "wt");							// "score.dat" 파일을 쓰기 모드("wt")로 엽니다
			ScreenPrint(10, 13, "-------BEST SCORE !!-------");				// 화면에 메시지를 출력합니다.
			if (file == 0) {												// 파일 열기에 실패한 경우 오류 메시지를 출력합니다.
				ScreenPrint(25, 12, "FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT "); // 오류 메시지 출력
			}
			else {
				fprintf(file, "%d", g_nlastGrade);							// 새로운 최고 점수를 "score.dat" 파일에 씁니다. g_nlastGrade이 쓰고자 하는 내용입니다. 
				fclose(file);												// 파일을 닫습니다.
				g_nlastGrade = 0;											// 새로운 최고 점수를 기록한 후, 마지막 점수(g_nlastGrade)를 0으로 초기화합니다.
			}
		}
			
		break;																// 탈출
	}
	ScreenFlipping();														// 현재 사용 중인 콘솔 창 버퍼와 다음에 사용할 콘솔 창 버퍼를 번갈아가며 화면에 보여준다.(화면을 교체하는 역할)
}

int main(void) {
	int nKey, nX, nY;	// 키를 담을변수, x축, y축 
	clock_t CurTime;	// 시간을 담을 변수 CurTime(현 시점) 선언

	ScreenInit();		// 콘솔 화면 버퍼 초기화
	Init();				// 초기 상태 : 막대기, 공, 블럭 세팅

	while (1) {
		if (_kbhit()) {      // _kbhit() : 키가 눌렸는지 검사
			nKey = _getch(); // _getch() : 키보드로 하나의 문자를 입력받는다.

			switch (nKey) { // 입력된 키
			case ' ' :		// 스페이스바를 입력시 실행
				if (g_nGameState == INIT && g_nStage == 0) {	// 게임 상태가 초기 및 첫 스테이지이면 아래 코드를 실행
					g_nGameState = READY;						// 게임 상태를 준비상태
					g_UpdateOldTime = clock();					// 	g_UpdateOldTime에다가 시간을 넣는다.
				}
				break;

			
			case 80:// 방향키 아래를 눌렀을 때 발사되는 키
				if (g_nGameState == RUNNING && g_sBall.nReady == 1) {	// 게임 상태가 진행중 및 준비상태인 경우
					g_sBall.nReady = 0;									// 준비상태에서 진행상태로 바꾼다.
					g_sBall.OldTime = clock();							// 공의 예전시간(g_sBall.OldTime)에다가 시간을 넣는다.
				}
				break;

			case 75: // 왼쪽 화살표 키가 눌렸을 때 실행되는 키
				if (g_nGameState == RUNNING) {		// 현재 게임의 상태 RUNNING(움직이고 있을 때)
					CurTime = clock();				// 현재 시간을 CurTime에다가 넣고 있다.
					if (CurTime - g_sBar.OldTime > g_sBar.MoveTime) { // 현재 시간(CurTime)과 이전에 바(bar)가 이동한 시간(g_sBar.OldTime)을 비교하여 바(bar)를 이동할 시간이 되었는지를 확인
						g_sBar.OldTime = CurTime;	// 현재시간을 이전 막대기 이동시간으로 설정
						if (g_sBar.nX[0] > 2) {		// 막대기(패들)이 왼쪽 경계 영역을 벗어나지 않도록 하는 역할
							g_sBar.nX[0]--;			// 막대기 왼쪽부분을 원쪽으로 이동
							g_sBar.nX[1]--;			// 막대기 중간부분을 원쪽으로 이동
							g_sBar.nX[2]--;			// 막대기 오른쪽부분을 원쪽으로 이동

							if (g_sBall.nReady == 1)	// 공이 준비 상태인 경우에만 공을 바와 함께 움직입니다.
								g_sBall.nX--;			// 공도 같이 원쪽으로 이동
						}
					}
				}
				break;
			case 77: // 오른 쪽 방향키를 눌렀을때 움직이는 코드
				if (g_nGameState == RUNNING) {	// 현재 게임의 상태 RUNNING(움직이고 있을 때)
					CurTime = clock();			// 현재 시간을 CurTime에다가 넣고 있다.
					if (CurTime - g_sBar.OldTime > g_sBar.MoveTime) {	// 현재 시간(CurTime)과 이전에 바(bar)가 이동한 시간(g_sBar.OldTime)을 비교하여 바(bar)를 이동할 시간이 되었는지를 확인
						g_sBar.OldTime = CurTime;	// 현재시간을 예전시간(g_sBar.OldTime)에다가 넣기
						if (g_sBar.nX[2] < 40) {	// 경계 영역 체크
							g_sBar.nX[0]++;			// 막대기 윈쪽 오른쪽으로
							g_sBar.nX[1]++;			// 막대기 중간 오른쪽으로
							g_sBar.nX[2]++;			// 막대기 오른쪽 오른쪽으로

							if (g_sBall.nReady == 1) {	// 공이 준비상태인 경우 (막대기와 함께 붙어 있음)
								g_sBall.nX++;			// 막대기와 함께 오른쪽
							}
						}
					}
				}		
				break;									// 탈출

			case 72: // 방향키 위쪽눌렀을때
				if (g_nGameState == RUNNING && g_sBall.nReady == 0) {	// 게임이 진행상태및 공이 진행 중일때
					nX = g_sBall.nX;	// 현재의 공의 위치 저장 (x축)
					nY = g_sBall.nY;	// 현재의 공의 위치 저장 (y축)

					for (int i = 0; i < 3; i++) {		// 막대기가 3개로 구성
						if (nY == (g_sBar.nY - 1)) {	// 공과 막대기가 접한 경우
							if ((nX >= g_sBar.nX[0] && nX <= (g_sBar.nX[2]))) { // 막대기 원쪽 부분과 오른쪽 부분 사이에 있으면
								g_sBall.nReady = 1;		// 충돌한 경우 공의 상태를 1(ready)로 변경 - 공이 멈춤
								break;					// 탈출
							}	
						}
					}
				}
				break;									// 탈출

			case '1':													// 1을 눌렀을때	
				if (g_nGameState == RUNNING && g_sBall.nReady == 1) {	// 게임이 진행상태 및 공이 준비상태일때
					g_sBall.nDirect = RIGHT_TOP;						// 공을 오른쪽 대각선으로
					g_sBall.OldTime = clock();							// 현시간을 예전시간으로
				}
				break;													// 탈출

			case '2':													// 2을 눌렀을때									
				if (g_nGameState == RUNNING && g_sBall.nReady == 1) {	// 게임이 진행상태 및 공이 준비상태일때
					g_sBall.nDirect = TOP;								// 공을 위쪽으로
					g_sBall.OldTime = clock();							// 현시간을 예전시간으로
				}	
				break;													// 탈출	

			case '3':													// 3을 눌렀을때
				if (g_nGameState == RUNNING && g_sBall.nReady == 1) {	// 게임이 진행상태 및 공이 준비상태일때
					g_sBall.nDirect = LEFT_TOP;							// 공을 원쪽 대각선으로
					g_sBall.OldTime = clock();							// 현시간을 예전시간으로 
				}
				break;
			case 'y':													// 소문자 'y' 눌렀을때
			case 'Y':													// 대문자 'Y' 눌렀을때
				if (g_nGameState == FAILED) {							// 게임 상태 실패 변경
					Init();												// 초기 상태로
					g_nGameState = READY;								// 게임을 다시 준비 상태로
					if (g_nStage != 1 && g_nStage != 2) {				// 스테이지가 1, 2가 아닐시
						g_nGrade = 0;									// 점수를 0으로
					}
					g_UpdateOldTime = clock();							// 현시간을 예전시간으로
				}
				break;													// 탈출
			case 'n':													// 소문자 'n' 눌렀을때
			case 'N':													// 대문자 'N' 눌렀을때
				if (g_nGameState == FAILED) {							// 게임 상태 실패로 변경
					g_nGameState = RESULT;								// 게임 상태 최종 결과로 변경
				}
				break;													// 탈출 
			}
		}

		Update();														// 게임 상태 업데이트(오브젝트 위치, 속도)
		Render();														// 현게임 상태에 따라 화면을 그리는 역할 
	}

	ScreenRelease();													// 콘솔 화면을 닫습니다.
	return 0;
}