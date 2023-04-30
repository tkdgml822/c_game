#include "MyVariable.h"

int Collision(int nX, int nY) { // ���� x, ���� y
	int nCount = 0; // �浹 ����

	// ���� ������ �浹
	for (int i = 0; i < g_StageInfo[g_nStage].nBlockCount; i++) {		// 3���� ���������� ���� ������ŭ �ݺ�
		if (g_sBlock[i].nLife == 1) {									// ������ ü���� 1�϶�
			if (g_sBlock[i].nY == nY) {									// �ش� ������ ���� ��ġ�� ���Ͽ� �浹 ���θ� �Ǵ�
				if ((g_sBlock[i].nX == nX || (g_sBlock[i].nX + 1) == nX) ||
					(g_sBlock[i].nX == (nX + 1) || (g_sBlock[i].nX + 1) == (nX + 1)))
				{
					g_sBall.nDirect = g_BlockState[g_sBall.nDirect];	// ���� ���� �⵿�� �ε��� ���⿡ ���� ������ �ٲ۴�.(���� ��� ���� ���� 0�϶� 3���� ������)
					g_sBlock[i].nLife = 0;								// ���� �ε����� ���� ü���� 0���� ����
					nCount++;											// �浹�� �浹 ���� ���ϱ�
					g_nGrade += 100;									// �浹�� ���ϳ��� ���� 100�� �߰�
					g_nBlockCount++;									// ���� �� ���� �߰�	
				}
			}
		}
	}

	// �浹 üũ 
	if (nCount != 0) {	//  �浹�� ���� 0�� �ƴ� ���ڵ��� 1�� ��ȯ
		return 1;
	}

	// ���� ����� �浹
	for (int i = 0; i < 3; i++) {									// ������� ���� 3���� 3���� �ݺ�
		if (nY == g_sBar.nY) {										// ���� ���� ������� ������ ���� �� 
			if ((nX >= g_sBar.nX[0] && nX <= (g_sBar.nX[2]))) {		// ���� x������ ������� ���� ���� ������ �� ���̿� ������
				g_sBall.nDirect = g_BlockState[g_sBall.nDirect];	// ���� ���� ������ �� ������ �����̴� ���� �������� ����.

				return 1;											// ���� ����Ⱑ �浹�� ���� ������ �ٲ��� 1�� ��ȯ
			}
		}
	}

	// Note: ����  
	if (nY < 1) {											// ���� ���� ���� �ε����� ���� ������ �ٲ۴�.
		g_sBall.nDirect = g_StateTable[0][g_sBall.nDirect]; // ���� ���� ������	�ٲ۴�.
		return 1;											// 1 ��ȯ
	}

	// Note: ������
	if (nX > 39) {											// ���� ������ ���� �ε����� ���� ������ �ٲ۴�.
		g_sBall.nDirect = g_StateTable[1][g_sBall.nDirect];	// ���� ���� ������ �ٲ۴�.
		return 1;
	}

	// Note: ���� �ʱ�ȭ �� ���� ����
	if (nY > 22) {											// ���� �ع��� ��, ����� ������ ������������ �ڵ�
		g_sBall.nHP--;										// ���� ������ �������� ���� ���� ü���� -1�� ���ش�.

		if (g_sBall.nHP == 0) {								// ���� HP�� 0�� �Ǿ����� ����
			g_nGameState = STOP;							// ������ STOP���� �ٲ۴�.
		}
		else {
			g_sBall.nX = g_sBar.nX[1];						// ���� x���� ������� x�� �߰����ٰ� �Ӵϴ�.
			g_sBall.nY = g_sBar.nY - 1;						// ���� y���� ������� y�� �ٷ� ���ʿ� �Ӵϴ�.(-1���ϴ� ����: ����� �����ٰ� ���� �α� ����)
			g_sBall.nReady = 1;								// �غ���¸� �غ� ���·� �ٲߴϴ�.
		}

		return 1;											// 1 ��ȯ
	}

	if (nX < 2) {											// ���� ����
		g_sBall.nDirect = g_StateTable[3][g_sBall.nDirect];	// ���� ���� �ε����� ���� ������ �ٲ�
		return 1;											// 1 ��ȯ
	}

	return 0;
}