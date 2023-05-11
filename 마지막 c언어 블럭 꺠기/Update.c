#include "MyVariable.h"

// 게임 상태 업데이트
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