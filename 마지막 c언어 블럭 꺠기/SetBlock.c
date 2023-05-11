#include "MyVariable.h"

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