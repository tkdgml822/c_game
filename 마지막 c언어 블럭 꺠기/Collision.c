#include "MyVariable.h"

int Collision(int nX, int nY) { // 공의 x, 공의 y
	int nCount = 0; // 충돌 개수

	// 공과 벽돌의 충돌
	for (int i = 0; i < g_StageInfo[g_nStage].nBlockCount; i++) {		// 3개의 스테이지별 블럭의 갯수만큼 반복
		if (g_sBlock[i].nLife == 1) {									// 벽돌의 체력이 1일때
			if (g_sBlock[i].nY == nY) {									// 해당 벽돌과 공의 위치를 비교하여 충돌 여부를 판단
				if ((g_sBlock[i].nX == nX || (g_sBlock[i].nX + 1) == nX) ||
					(g_sBlock[i].nX == (nX + 1) || (g_sBlock[i].nX + 1) == (nX + 1))) // x축 충돌 했는지에 판단
				{
					g_sBall.nDirect = g_BlockState[g_sBall.nDirect];	// 공이 블럭과 출동후 부딪힌 방향에 따라 방향을 바꾼다.(예를 들어 공의 값이 0일때 3으로 가도록)
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
		return 1;		//	
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