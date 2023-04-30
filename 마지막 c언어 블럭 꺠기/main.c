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

void Init() {
	if (g_nStage == -1) {	//	���������� -1 �ϰ��

		g_nStage = 0;		//	���������� 0���� �ٲ� 

	}

	// ������ ��� ���� ���� �����͸� �о��.
	// ������ �÷����ϸ鼭 ����� �ְ� ������ �����ϰ� �ִ� ���Ϸ� ����
	//  ������ �������� �ʴ� ��� (��, ������ ������ �÷������� ���� ���) g_nBestGrade ������ 0���� �ʱ�ȭ�մϴ�.
	// �׷��� ���� ��� ���Ͽ��� �о���� �ְ� ������ g_nBestGrade ������ �����մϴ�.
	FILE* file = fopen("score.dat", "rt");
	if (file == 0) { g_nBestGrade = 0; }
	else {
		fscanf(file, "%d", &g_nBestGrade);
		fclose(file);
	}


	SetBlock(g_StageInfo[g_nStage].nBlockCount);			// ���������� ���� ������ŭ ���� �������ش�.

	// �� �ʱ�ȭ
	g_sBall.nX = 19;										// ���� x�� ���� 19�� ����
	g_sBall.nHP = 3;										// ���� ü�� 3���� ����
	g_sBall.nY = 20;										// ���� Y�� 20���� ����
	g_sBall.nDirect = TOP;									// �⺻ ���� ���� ���� TOP���� ����
	g_sBall.OldTime = clock();								// ���� �ð� OldTime�� ���
	g_sBall.nReady = 1;										// �غ� �Ϸ� ����
	g_sBall.MoveTime = g_StageInfo[g_nStage].ball_MoveTime; // ���������� ���� �ӵ� ����

	// Note: ����� �ʱ�ȭ
	g_sBar.nY = g_sBall.nY + 1;								// ����� y�� ���� �ٷ� ������ �ʱ�ȭ 
	g_sBar.nX[0] = g_sBall.nX - 2;							// ����� ���� ��x �� -2�� ����
	g_sBar.nX[1] = g_sBall.nX;								// ����� �߰� x �� ��ġ�� �Ȱ��� ����
	g_sBar.nX[2] = g_sBall.nX + 2;							// ���� ������ ��x �� +2�� ����
	g_sBar.MoveTime = 1;									// ������� �ӵ� 1�� ����
	g_sBar.OldTime = clock();								// ���� �ð� OldTime�� ���

	g_nBlockCount = 0;										// ���� �ε��� �� 0
}

void Render() {
	char string[100];			// ���ڿ�

	ScreenClear();				// ���� ����

	switch (g_nGameState) {		// ���� ���� ����
	case INIT:					// �ʱ� ���� 
		if (g_nStage == 0)		// ù��° ���� ���
			InitScreen();		// ���� �Ұ� �������̽�
		break;					// Ż��

	case READY:					// �غ����
		ReadyScreen();			// �غ���� �������̽�
		sprintf_s(string, sizeof(string), "%d", g_nStage + 1); // ������ ���ڿ��� ��ȯ (��������)
		ScreenPrint(13, 7, string);	// �ٲ� ���ڿ� ȭ�� ���
		break;					// Ż��
	case RUNNING:				// �۵� ��
		RunningScreen();		// �۵� �� �϶� �������̽�

		sprintf_s(string, sizeof(string), "�������� : %d", g_nStage + 1);	// �������� ���ڿ��� ����(���� ��������)
		ScreenPrint(45, 2, string);											// ����� ���ڿ� ȭ�� ���

		sprintf_s(string, sizeof(string), "���� : %d ", g_sBall.nHP);		// �������� ���ڿ��� ����(���� ü��)
		ScreenPrint(45, 4, string);											// ����� ���ڿ� ȭ�� ���

		sprintf_s(string, sizeof(string), "���� : %d ", g_nGrade);			// �������� ���ڿ��� ����(����)
		ScreenPrint(45, 6, string);											// ����� ���ڿ� ȭ�� ���

		sprintf_s(string, sizeof(string), "���� �ð� : %d �� %d ��", g_RemainTime / 60, g_RemainTime % 60);// �ð��� ���ڿ��� ����(�� ��)
		ScreenPrint(45, 8, string);											// ����� ���ڿ� ȭ�� ���

		sprintf_s(string, sizeof(string), "BEST SCORE : %d", g_nBestGrade);	// �������� ���ڿ��� ����(�ְ�����)
		ScreenPrint(45, 10, string);										// ����� ���ڿ� ȭ�� ���


		for (int i = 0; i < g_StageInfo[g_nStage].nBlockCount; i++) {		// ���� ������ŭ �ݺ�
			if (g_sBlock[i].nLife == 1)										// ���� ü���� 1�϶�
				ScreenPrint(g_sBlock[i].nX, g_sBlock[i].nY, "��");			// �ݺ��Ǵ� ����ŭ ȭ�� ���
		}

		for (int i = 0; i < 3; i++)											// ������� ����ŭ �ݺ�(3��)
		{			
			SetColor(14);													// ����� ���� �����
			ScreenPrint(g_sBar.nX[i], g_sBar.nY, "��");						// ����� ���
		}
		SetColor(14);														// ���� ���� �����
		ScreenPrint(g_sBall.nX, g_sBall.nY, "��");							// �����
		SetColor(7);														// �� �ٽ� �����·�
		break;																// Ż��
	case SUCCESS:															// ���� �Ͻ� 
		SuccessScreen();													// ���� �������̽� ���
		sprintf_s(string, sizeof(string), "%d Stage", g_nStage + 1);		// ������ ������������ ���ڿ��� ���� 
		ScreenPrint(19, 12, string);										// ����� ���ڿ� ���
		sprintf_s(string, sizeof(string), "����: %d", g_nGrade);			// ������ ���� ���ڿ��� ����
		ScreenPrint(25, 16, string);										// ����� ���ڿ� ���
		break;																// Ż��
	case FAILED:															// ���н�
		FailureScreen();													// ���� �������̽� ������
		sprintf_s(string, sizeof(string), "%d Stage!", g_nStage + 1);		// ������ ������������ ���ڿ��� ����
		ScreenPrint(16, 4, string);											// ����� ���ڿ� ���
		break;																// Ż��

	case RESULT:															// ���
		ResultScreen();														// ��� ȭ��
		sprintf_s(string, sizeof(string), "%d", g_nGrade);					// ����������(����) ���ڿ��� ����
		ScreenPrint(25, 11, string);										// ����� ���ڿ� ���

		g_nlastGrade = g_nGrade;											// ���� ���� ������ �������ٰ� ����

		if (g_nlastGrade > g_nBestGrade) {									// ���������� �ְ� ����(g_nBestGrade)���� ���ο� ����(g_nlastGrade)�� ������ Ȯ���մϴ�.
			FILE* file = fopen("score.dat", "wt");							// "score.dat" ������ ���� ���("wt")�� ���ϴ�
			ScreenPrint(10, 13, "-------BEST SCORE !!-------");				// ȭ�鿡 �޽����� ����մϴ�.
			if (file == 0) {												// ���� ���⿡ ������ ��� ���� �޽����� ����մϴ�.
				ScreenPrint(25, 12, "FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT "); // ���� �޽��� ���
			}
			else {
				fprintf(file, "%d", g_nlastGrade);							// ���ο� �ְ� ������ "score.dat" ���Ͽ� ���ϴ�. g_nlastGrade�� ������ �ϴ� �����Դϴ�. 
				fclose(file);												// ������ �ݽ��ϴ�.
				g_nlastGrade = 0;											// ���ο� �ְ� ������ ����� ��, ������ ����(g_nlastGrade)�� 0���� �ʱ�ȭ�մϴ�.
			}
		}
			
		break;																// Ż��
	}
	ScreenFlipping();														// ���� ��� ���� �ܼ� â ���ۿ� ������ ����� �ܼ� â ���۸� �����ư��� ȭ�鿡 �����ش�.(ȭ���� ��ü�ϴ� ����)
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