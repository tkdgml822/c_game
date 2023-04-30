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