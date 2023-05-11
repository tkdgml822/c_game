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