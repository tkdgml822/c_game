#include "MyVariable.h"

// ���� �� ã��
int Search(int nEnd, int nX, int nY) {										// (���� ����, ���� x, ���� y)
	for (int i = 0; i < nEnd; i++) {										// ���� ���� ��ŭ �ݺ�
		if (g_sBlock[i].nY == nY) {											// Y���� ������ X�� �˻�
			if (g_sBlock[i].nX == nX || (g_sBlock[i].nX + 1) == nX ||		// ã������ ���� �¿�� �� ĭ�� ������ �ξ� �˻�
				g_sBlock[i].nX == nX + 1 || (g_sBlock[i].nX + 1) == nX + 1)
				return 1;													// ���� ���� ������ (��ȯ �Ǽ� �޴� ���� While���̶� 1�� ��ȯ�Ǹ� ���� ����)
		}
	}
	return 0;																// ���� ���� ������ (0 ��ȯ)
}