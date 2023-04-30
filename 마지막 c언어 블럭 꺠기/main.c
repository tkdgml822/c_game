#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"
#include "structure.h"
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

// RANDOM�� ��ġ �ȿ��� ����� �Է� ���� ������ŭ ǥ��
void SetBlock(int nBlockCount) {
	int nX, nY, i;							// �������� �ޱ����� x, y, �ݺ����� ���̱� ���� i (int������ ����)

	srand((unsigned int)time(NULL));		// �������� �������� �õ尪 ����

	for (i = 0; i < nBlockCount; i++) {		// �� ���� ��ŭ �ݺ�
		g_sBlock[i].nLife = 1;				// ���� ü�� 1 ����

		while (1) {							// ���� ���� (�ߺ��� ���� ������ ���� �ݺ� ������ �ڵ� ����)
			nX = rand() % 39 + 2;			// 2 ~ 40 ������ ���� (������ ��踦 �ѱ��� �������� �ϱ� ���� 2���� ����)
			nY = rand() % 10 + 1;			// 1 ~ 10 ������ ����

			if (Search(i, nX, nY) == 0) {	// ���� ��ġ�� ���� �������� �ʱ� ���� �����ϴ� �ڵ�
				g_sBlock[i].nX = nX;		// �ߺ��� ���� ������ x�� ��ġ 
				g_sBlock[i].nY = nY;		// �ߺ��� ���� ������ y�� ��ġ
				break;						// x, y�� �� ��ġ�� while�� ����
			}
		}
	}
}

int main(void) {
	int nKey, nX, nY;	// Ű�� ��������, x��, y�� 
	clock_t CurTime;	// �ð��� ���� ���� CurTime(�� ����) ����

	ScreenInit();		// �ܼ� ȭ�� ���� �ʱ�ȭ
	Init();				// �ʱ� ���� : �����, ��, �� ����

	while (1) {
		if (_kbhit()) {      // _kbhit() : Ű�� ���ȴ��� �˻�
			nKey = _getch(); // _getch() : Ű����� �ϳ��� ���ڸ� �Է¹޴´�.

			switch (nKey) { // �Էµ� Ű
			case ' ' :		// �����̽��ٸ� �Է½� ����
				if (g_nGameState == INIT && g_nStage == 0) {	// ���� ���°� �ʱ� �� ù ���������̸� �Ʒ� �ڵ带 ����
					g_nGameState = READY;						// ���� ���¸� �غ����
					g_UpdateOldTime = clock();					// 	g_UpdateOldTime���ٰ� �ð��� �ִ´�.
				}
				break;

			
			case 80:// ����Ű �Ʒ��� ������ �� �߻�Ǵ� Ű
				if (g_nGameState == RUNNING && g_sBall.nReady == 1) {	// ���� ���°� ������ �� �غ������ ���
					g_sBall.nReady = 0;									// �غ���¿��� ������·� �ٲ۴�.
					g_sBall.OldTime = clock();							// ���� �����ð�(g_sBall.OldTime)���ٰ� �ð��� �ִ´�.
				}
				break;

			case 75: // ���� ȭ��ǥ Ű�� ������ �� ����Ǵ� Ű
				if (g_nGameState == RUNNING) {		// ���� ������ ���� RUNNING(�����̰� ���� ��)
					CurTime = clock();				// ���� �ð��� CurTime���ٰ� �ְ� �ִ�.
					if (CurTime - g_sBar.OldTime > g_sBar.MoveTime) { // ���� �ð�(CurTime)�� ������ ��(bar)�� �̵��� �ð�(g_sBar.OldTime)�� ���Ͽ� ��(bar)�� �̵��� �ð��� �Ǿ������� Ȯ��
						g_sBar.OldTime = CurTime;	// ����ð��� ���� ����� �̵��ð����� ����
						if (g_sBar.nX[0] > 2) {		// �����(�е�)�� ���� ��� ������ ����� �ʵ��� �ϴ� ����
							g_sBar.nX[0]--;			// ����� ���ʺκ��� �������� �̵�
							g_sBar.nX[1]--;			// ����� �߰��κ��� �������� �̵�
							g_sBar.nX[2]--;			// ����� �����ʺκ��� �������� �̵�

							if (g_sBall.nReady == 1)	// ���� �غ� ������ ��쿡�� ���� �ٿ� �Բ� �����Դϴ�.
								g_sBall.nX--;			// ���� ���� �������� �̵�
						}
					}
				}
				break;
			case 77: // ���� �� ����Ű�� �������� �����̴� �ڵ�
				if (g_nGameState == RUNNING) {	// ���� ������ ���� RUNNING(�����̰� ���� ��)
					CurTime = clock();			// ���� �ð��� CurTime���ٰ� �ְ� �ִ�.
					if (CurTime - g_sBar.OldTime > g_sBar.MoveTime) {	// ���� �ð�(CurTime)�� ������ ��(bar)�� �̵��� �ð�(g_sBar.OldTime)�� ���Ͽ� ��(bar)�� �̵��� �ð��� �Ǿ������� Ȯ��
						g_sBar.OldTime = CurTime;	// ����ð��� �����ð�(g_sBar.OldTime)���ٰ� �ֱ�
						if (g_sBar.nX[2] < 40) {	// ��� ���� üũ
							g_sBar.nX[0]++;			// ����� ���� ����������
							g_sBar.nX[1]++;			// ����� �߰� ����������
							g_sBar.nX[2]++;			// ����� ������ ����������

							if (g_sBall.nReady == 1) {	// ���� �غ������ ��� (������ �Բ� �پ� ����)
								g_sBall.nX++;			// ������ �Բ� ������
							}
						}
					}
				}		
				break;									// Ż��

			case 72: // ����Ű ���ʴ�������
				if (g_nGameState == RUNNING && g_sBall.nReady == 0) {	// ������ ������¹� ���� ���� ���϶�
					nX = g_sBall.nX;	// ������ ���� ��ġ ���� (x��)
					nY = g_sBall.nY;	// ������ ���� ��ġ ���� (y��)

					for (int i = 0; i < 3; i++) {		// ����Ⱑ 3���� ����
						if (nY == (g_sBar.nY - 1)) {	// ���� ����Ⱑ ���� ���
							if ((nX >= g_sBar.nX[0] && nX <= (g_sBar.nX[2]))) { // ����� ���� �κа� ������ �κ� ���̿� ������
								g_sBall.nReady = 1;		// �浹�� ��� ���� ���¸� 1(ready)�� ���� - ���� ����
								break;					// Ż��
							}	
						}
					}
				}
				break;									// Ż��

			case '1':													// 1�� ��������	
				if (g_nGameState == RUNNING && g_sBall.nReady == 1) {	// ������ ������� �� ���� �غ�����϶�
					g_sBall.nDirect = RIGHT_TOP;						// ���� ������ �밢������
					g_sBall.OldTime = clock();							// ���ð��� �����ð�����
				}
				break;													// Ż��

			case '2':													// 2�� ��������									
				if (g_nGameState == RUNNING && g_sBall.nReady == 1) {	// ������ ������� �� ���� �غ�����϶�
					g_sBall.nDirect = TOP;								// ���� ��������
					g_sBall.OldTime = clock();							// ���ð��� �����ð�����
				}	
				break;													// Ż��	

			case '3':													// 3�� ��������
				if (g_nGameState == RUNNING && g_sBall.nReady == 1) {	// ������ ������� �� ���� �غ�����϶�
					g_sBall.nDirect = LEFT_TOP;							// ���� ���� �밢������
					g_sBall.OldTime = clock();							// ���ð��� �����ð����� 
				}
				break;
			case 'y':													// �ҹ��� 'y' ��������
			case 'Y':													// �빮�� 'Y' ��������
				if (g_nGameState == FAILED) {							// ���� ���� ���� ����
					Init();												// �ʱ� ���·�
					g_nGameState = READY;								// ������ �ٽ� �غ� ���·�
					if (g_nStage != 1 && g_nStage != 2) {				// ���������� 1, 2�� �ƴҽ�
						g_nGrade = 0;									// ������ 0����
					}
					g_UpdateOldTime = clock();							// ���ð��� �����ð�����
				}
				break;													// Ż��
			case 'n':													// �ҹ��� 'n' ��������
			case 'N':													// �빮�� 'N' ��������
				if (g_nGameState == FAILED) {							// ���� ���� ���з� ����
					g_nGameState = RESULT;								// ���� ���� ���� ����� ����
				}
				break;													// Ż�� 
			}
		}

		Update();														// ���� ���� ������Ʈ(������Ʈ ��ġ, �ӵ�)
		Render();														// ������ ���¿� ���� ȭ���� �׸��� ���� 
	}

	ScreenRelease();													// �ܼ� ȭ���� �ݽ��ϴ�.
	return 0;
}