#include "MyVariable.h"

// ���� ���� ������Ʈ
void Update() {
	clock_t CurTime = clock();								// ����ð� ���

	switch (g_nGameState) {									// ������ ���� ����(�ʱ� ���� INIT)
	case READY:												// �غ�
		if (CurTime - g_UpdateOldTime > 3000) {				// ���ӽ����� 2���� �ڵ����� ����
			g_nGameState = RUNNING;							// 2���� Running�� �ٲ�
			g_GameStartTime = CurTime;
		}
		break;

	case RUNNING: // ���ӻ��� ������
		g_RemainTime = (g_StageInfo[g_nStage].LimitTime - (CurTime - g_GameStartTime)) / 1000; // ���� ���� ���� �ð� ( ���ѽð� - (����ð� - ���ӽ��� �ð�) / 1�� )  1�ʴ� �и��� ������ �� ������ ǥ�� �ϱ� ���ؼ� �����ش�.

		if ((CurTime - g_GameStartTime) > g_StageInfo[g_nStage].LimitTime || g_nBlockCount == g_StageInfo[g_nStage].nBlockCount) { // ���� �� �ڵ�� ���ѽð��� �����ų� ����� ������ ��� ���� �Ǿ����� ���� ���¸� STOP���� ���ش�.
			g_nGameState = STOP;	// ���� ����
			return;
		}
		else if (g_sBall.nReady == 0) {	// ������ ������

			// �� �ڵ尡 ������ ���� �ѹ��� ���� ĭ�� �������� ������ ��Ģ�� ��Ű�� ���� �� �ֱ� ������ �߿��� �ڵ�
			if (CurTime - g_sBall.OldTime > g_sBall.MoveTime) { // ���� �ð��� ���� ���� ������ �ð��� ���� ���� �� ���� ������ �� �ɸ��� �ð����� ũ�� �� �ڵ� ����
				g_sBall.OldTime = CurTime;	// ���ð��� �����ð����ٰ� �־��ش�.

				switch (g_sBall.nDirect)	// ���� ����
				{
				case TOP:													// �����Ͻ�
					if (Collision(g_sBall.nX, g_sBall.nY - 1) == 0) {		// ���� �浹�˻�( -1�� ���ִ� ������ ���� ���ʿ� �ִ� �������� �浹 ���ΰ� �ִ��� Ȯ���ϱ� ���� �ֽ��ϴ�.)
						g_sBall.nY--;										// �� ����
					}
					break;
				case LEFT_TOP:												// ���� ���� �밢��
					if (Collision(g_sBall.nX + 1, g_sBall.nY - 1) == 0) {	// ���� �浹 ���θ� ��Ÿ���� ���� �浹�� ������ �� �ڵ� ����
						g_sBall.nX++;										// �� ����
						g_sBall.nY--;										// �� ����
					}
					break;
				case LEFT_DOWN:												// ���� ���� �밢��
					if (Collision(g_sBall.nX + 1, g_sBall.nY + 1) == 0) {	// ���� �浹 ���θ� ��Ÿ���� ���� �浹�� ������ �� �ڵ� ����
						g_sBall.nX++;										// �� ����
						g_sBall.nY++;										// �� ����
					}
					break;													// Ż��
				case DOWN:													// ������
					if (Collision(g_sBall.nX, g_sBall.nY + 1) == 0)			// ���� �浹 ���θ� ��Ÿ���� ���� �浹�� ������ �� �ڵ� ����
						g_sBall.nY++;										// �� �Ʒ���
					break;													// Ż��
				case RIGHT_DOWN:											// ���� ������ �밢��
					if (Collision(g_sBall.nX - 1, g_sBall.nY + 1) == 0) {	// ���� �浹 ���θ� ��Ÿ���� ���� �浹�� ������ �� �ڵ� ����
						g_sBall.nX--;										// �� ������		
						g_sBall.nY++;										// �� �Ʒ���
					}
					break;													// Ż��
				case RIGHT_TOP:												// �� ������ �밢��
					if (Collision(g_sBall.nX - 1, g_sBall.nY - 1) == 0) {	// ���� �浹 ���θ� ��Ÿ���� ���� �浹�� ������ �� �ڵ� ����
						g_sBall.nX--;										// �� ����
						g_sBall.nY--;										// �� ����
					}
					break;													// Ż��
				}
			}
		}
		break;																// Ż��
	case STOP:	// ���� ����
		// �����̳� ���и� �Ǵ����־ ����� ���ִ� �κ��� �;� �Ѵ�.
		if (g_nBlockCount == g_StageInfo[g_nStage].nBlockCount && g_sBall.nHP > 0 && g_RemainTime > 0) {	// ���� ���� �����߰� ü�µ� 0���� ���� �ð� 0���̻��̸� �������� �Ǵ�
			g_UpdateOldTime = CurTime;	// ����ð� �����ð����� ����
			g_nGameState = SUCCESS;		// �������� ����
		}
		else {
			g_nGameState = FAILED;		// ������ �������� ���ߴٸ� �������� ����
		}
		break;
	case SUCCESS:						// ������ �����϶�
		if (CurTime - g_UpdateOldTime > 3000) {	// �� ���� ���� ������Ʈ�� �󸶳� �����Ǿ������� ��Ÿ����, �� ���� 3000���� ũ�� ������ ������ ���¿��� 3�ʰ� ����� ������ �Ǵ�
			g_UpdateOldTime = CurTime;	// ����ð��� �����ð����� ������Ʈ
			++g_nStage;					// ���� ��������
			Init();						// �ʱ�ȭ
			g_nGameState = READY;		// �غ� ����
		}
		break;							// Ż��
	}
}