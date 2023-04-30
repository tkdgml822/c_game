#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include "structure.h"

BAR  g_sBar;  // 막대기 구조체 선언
BALL g_sBall; // 공 구조체 선언

// 벽과 충돌하게 되면 방향 상태
int g_StateTable[4][6] = { 
   {  3,  2, -1, -1, -1,  4 },
   { -1,  5,  4, -1, -1, -1 },
   { -1, -1,  1,  0,  5, -1 }, 
   { -1, -1, -1, -1,  2,  1 }
};

int g_BlockState[6] = { 3, 2, 1, 0, 5, 4 }; // 블럭이 부딪혔을 때, 공의 방향을 변경하는데 사용되는 배열이다.

BLOCK g_sBlock[200]; // 블럭 200개 선언
GAME_STATE	g_nGameState = INIT;
int         g_nIsSuccess = 0;
int			g_nStage = -1;		// g_nStage변수는 3개의 맵을 알려주는 변수 main함수가 돌아가면 0으로 초기화되면 스테이지를 클리어 할때마다 1씩 늘어남
int			g_nGrade = 0;	    // 점수
int			g_nBestGrade = 0;
int			g_nlastGrade = 0;
int			g_nStageCount = 1;
clock_t		g_GameStartTime, g_UpdateOldTime, g_RemainTime;
int			g_nTotalGrade = 0;	// 총점

STAGE_INFO  g_StageInfo[3] = {		 // STAGE_INFO의 구조체 배열을 초기화하는 코드입니다.
	{  30, 100 * 1000       , 140 }, // { 벽돌의 개수, 남은 시간, 공의 속도 }
	{  50,   2 * 100 * 1000 , 100 },
	{ 100,   3 * 100 * 1000 ,  60 }};

int			g_nBlockCount = 0;		// 맞춘 벽돌

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


int Collision(int nX, int nY) { // 공의 x, 공의 y - 1
	int nCount = 0; // 충돌 개수

	// 공과 벽돌의 충돌
	for (int i = 0; i < g_StageInfo[g_nStage].nBlockCount; i++) {		// 3개의 스테이지별 블럭의 갯수만큼 반복
		if (g_sBlock[i].nLife == 1) {									// 벽돌의 체력이 1일때
			if (g_sBlock[i].nY == nY) {									// 해당 벽돌과 공의 위치를 비교하여 충돌 여부를 판단
				if ((g_sBlock[i].nX == nX || (g_sBlock[i].nX + 1) == nX) ||
					(g_sBlock[i].nX == (nX + 1) || (g_sBlock[i].nX + 1) == (nX + 1)))
				{
					g_sBall.nDirect = g_BlockState[g_sBall.nDirect];	// 공이 블럭과 출동후 부딪힌 방향에 따라 방향을 바꾼다.(예를 들어 공의 값이 0일때 3으로 가도록)
																		// 공의 방향을 g_BlockState을 참조해서 방향을 바꿉니다.
					g_sBlock[i].nLife = 0;								// 공이 부딪히면 블럭의 체력을 0으로 설정
					nCount++;											// 충돌후 충돌 갯수 더하기
					g_nGrade += 100;									// 충돌후 블럭하나당 점수 100점 추가
					g_nBlockCount++;									// 맞춘 블럭 갯수 추가	
				}
			}
		}
	}

	// 충돌 체크 
	if (nCount != 0) {	//  충돌한 수가 0이 아닌 숫자들은 1을 반환
		return 1;
	}

	// 공과 막대기 충돌
	for (int i = 0; i < 3; i++) {									// 막대기의 수는 3개라서 3까지 반복
		if (nY == g_sBar.nY) {										// 만약 공과 막대기의 갯수가 같을 시 
			if ((nX >= g_sBar.nX[0] && nX <= (g_sBar.nX[2]))) {		// 공의 x방향이 막대기의 왼쪽 끝과 오른쪽 끝 사이에 있을시
				g_sBall.nDirect = g_BlockState[g_sBall.nDirect];	// 현재 공의 방향이 들어가 다음에 움직이는 공의 방향으로 간다.

				return 1;											// 공과 막대기가 충돌후 공의 방향을 바꾼후 1을 반환
			}
		}
	}

	// Note: 위쪽  
	if (nY < 1) {											// 공이 위쪽 벽에 부딪히면 공의 방향을 바꾼다.
		g_sBall.nDirect = g_StateTable[0][g_sBall.nDirect]; // 공의 현재 방향을	바꾼다.
		return 1;											// 1 반환
	}

	// Note: 오른쪽
	if (nX > 39) {											// 공이 오른쪽 벽에 부딪히면 공의 방향을 바꾼다.
		g_sBall.nDirect = g_StateTable[1][g_sBall.nDirect];	// 공의 현재 방향을 바꾼다.
		return 1;
	}

	// Note: 공의 초기화 및 생명 감소
	if (nY > 22) {											// 공이 밑방향 즉, 막대기 밑으로 떨어졌을때의 코드
		g_sBall.nHP--;										// 공이 밑으로 떨어지고 나면 공의 체력을 -1을 해준다.
		
		if (g_sBall.nHP == 0) {								// 공의 HP가 0이 되었을때 실행
			g_nGameState = STOP;							// 게임을 STOP으로 바꾼다.
		}
		else {
			g_sBall.nX = g_sBar.nX[1];						// 공의 x축을 막대기의 x축 중간에다가 둡니다.
			g_sBall.nY = g_sBar.nY - 1;						// 공의 y축을 막대기의 y축 바로 위쪽에 둡니다.(-1을하는 이유: 막대기 위에다가 공을 두기 위해)
			g_sBall.nReady = 1;								// 준비상태를 준비 상태로 바꿉니다.
		}

		return 1;											// 1 반환
	}

	if (nX < 2) {											// 원쪽 방향
		g_sBall.nDirect = g_StateTable[3][g_sBall.nDirect];	// 원쪽 벽과 부딪히면 공의 방향을 바꿈
		return 1;											// 1 반환
	}

	return 0;
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

void Update() {
	clock_t CurTime = clock();								// 현재시간 담기

	switch (g_nGameState) {									// 게임의 현재 상태(초기 값은 INIT)
	case READY:												// 준비
		if (CurTime - g_UpdateOldTime > 3000) {				// 게임시작후 2초후 자동으로 시작
			g_nGameState = RUNNING;							// 2초후 Running로 바꿈
			g_GameStartTime = CurTime;
		}
		break;

	case RUNNING: // 게임상태 진행중
		g_RemainTime = (g_StageInfo[g_nStage].LimitTime - (CurTime - g_GameStartTime)) / 1000; // 게임 진행 남은 시간 ( 제한시간 - (현재시간 - 게임시작 시간) / 1초 )  1초는 밀리초 단위를 초 단위로 표현 하기 위해서 나누준다.

		if ((CurTime - g_GameStartTime) > g_StageInfo[g_nStage].LimitTime || g_nBlockCount == g_StageInfo[g_nStage].nBlockCount) { // 현재 이 코드는 제한시간이 지나거나 블록의 개수가 모두 제거 되었을때 게임 상태를 STOP으로 해준다.
			g_nGameState = STOP;	// 게임 중지
			return;
		}
		else if (g_sBall.nReady == 0) {	// 게임이 진행중

			// 이 코드가 없으면 공이 한번에 여러 칸씩 움직여서 게임의 규칙을 지키지 않을 수 있기 때문에 중요한 코드
			if (CurTime - g_sBall.OldTime > g_sBall.MoveTime) { // 현재 시간과 이전 공이 움직인 시간의 차가 공이 한 번에 움직일 때 걸리는 시간보다 크면 밑 코드 실행
				g_sBall.OldTime = CurTime;	// 현시간을 예전시간에다가 넣어준다.

				switch (g_sBall.nDirect)	// 공의 방향
				{
				case TOP:													// 위쪽일시
					if (Collision(g_sBall.nX, g_sBall.nY - 1) == 0) {		// 공의 충돌검사( -1을 해주는 이유는 공의 위쪽에 있는 벽돌과의 충돌 여부가 있는지 확인하기 위해 있습니다.)
						g_sBall.nY--;										// 공 위로
					}
					break;
				case LEFT_TOP:												// 위쪽 왼쪽 대각선
					if (Collision(g_sBall.nX + 1, g_sBall.nY - 1) == 0) {	// 공의 충돌 여부를 나타내는 문장 충돌이 없을시 밑 코드 실행
						g_sBall.nX++;										// 공 왼쪽
						g_sBall.nY--;										// 공 위로
					}
					break;
				case LEFT_DOWN:												// 밑쪽 왼쪽 대각선
					if (Collision(g_sBall.nX + 1, g_sBall.nY + 1) == 0) {	// 공의 충돌 여부를 나타내는 문장 충돌이 없을시 밑 코드 실행
						g_sBall.nX++;										// 공 왼쪽
						g_sBall.nY++;										// 공 위로
					}
					break;													// 탈출
				case DOWN:													// 밑으로
					if (Collision(g_sBall.nX, g_sBall.nY + 1) == 0)			// 공의 충돌 여부를 나타내는 문장 충돌이 없을시 밑 코드 실행
						g_sBall.nY++;										// 공 아래쪽
					break;													// 탈출
				case RIGHT_DOWN:											// 밑쪽 오른쪽 대각선
					if (Collision(g_sBall.nX - 1, g_sBall.nY + 1) == 0) {	// 공의 충돌 여부를 나타내는 문장 충돌이 없을시 밑 코드 실행
						g_sBall.nX--;										// 공 오른쪽		
						g_sBall.nY++;										// 공 아래로
					}
					break;													// 탈출
				case RIGHT_TOP:												// 위 오른쪽 대각선
					if (Collision(g_sBall.nX - 1, g_sBall.nY - 1) == 0) {	// 공의 충돌 여부를 나타내는 문장 충돌이 없을시 밑 코드 실행
						g_sBall.nX--;										// 공 원쪽
						g_sBall.nY--;										// 공 위로
					}
					break;													// 탈출
				}
			}
		}	
		break;																// 탈출
	case STOP:	// 게임 멈춤
		// 성공이냐 실패를 판단해주어서 출력을 해주는 부분이 와야 한다.
		if (g_nBlockCount == g_StageInfo[g_nStage].nBlockCount && g_sBall.nHP > 0 && g_RemainTime > 0) {	// 블럭을 전부 제거했고 체력도 0보다 많고 시간 0초이상이면 성공으로 판단
			g_UpdateOldTime = CurTime;	// 현재시간 예전시간으로 대입
			g_nGameState = SUCCESS;		// 스테이지 성공
		}
		else {
			g_nGameState = FAILED;		// 조건을 만족하지 못했다면 스테이지 실패
		}
		break;
	case SUCCESS:						// 게임이 성공일때
		if (CurTime - g_UpdateOldTime > 3000) {	// 이 값은 게임 업데이트가 얼마나 오래되었는지를 나타내며, 이 값이 3000보다 크면 게임이 성공한 상태에서 3초가 경과한 것으로 판단
			g_UpdateOldTime = CurTime;	// 현재시간을 예전시간으로 업데이트
			++g_nStage;					// 다음 스테이지
			Init();						// 초기화
			g_nGameState = READY;		// 준비 상태
		}
		break;							// 탈출


	}
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