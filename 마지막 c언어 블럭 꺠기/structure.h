#pragma once

typedef enum _GAME_STATE {	// ���� �������� ����ü
	INIT,					// �ʱ� ����
	READY,					// �غ� ���� 
	RUNNING,				// ���� ����
	SUCCESS,				// �������� Ŭ���� ����
	FAILED,					// �������� ���� ����
	STOP,					// ���� ������ ��
	RESULT					// ��� ��
} GAME_STATE;				// Game_State�� �̸� �缳��

// ���� ���� ����ü
typedef enum _DIRECT {	// �� ���� ����ü
	TOP,				// ����
	LEFT_TOP,			// ���� ���� �밢��
	LEFT_DOWN,			// ���� ���� �밢��
	DOWN,				// ������
	RIGHT_DOWN,			// ���� ������ �밢��
	RIGHT_TOP			// ���� ������ �밢��
} DIRECT;				// �̸� DIRECT���� �缳��

// �������� ����ü
typedef struct _STAGE_INFO {	// �������� �Ӽ� ����ü
	int      nBlockCount;		// ���� ����
	clock_t  LimitTime;			// ���� �ð�
	clock_t  ball_MoveTime;		// ���� �����̴� �ӵ�
} STAGE_INFO;					// STAGE_INFO���� ����ü �̸� �缳��

// �� ����ü
typedef struct _BALL {   // �� ����ü
	int		 nReady;     // 1 �̸� �غ� ����, 0�̸� �̵� ����
	int		 nHP;        // ����
	int		 nX, nY;     // ��ǥ
	DIRECT   nDirect;    // �̵� ����
	clock_t  MoveTime;   // �̵� �ð� ����
	clock_t  OldTime;	 // ���� �̵� �ð�
} BALL;					 // �̸� BALL�� ����

// �� ����ü
typedef struct _BLOCK { // �� ����ü
	int  nLife;			// �� ü��
	int  nX, nY;		// �� X, Y��
} BLOCK;				// �̸� BLOCK�� ����

// ����� ����ü
typedef struct _BAR {	// ����� ����ü
	int nX[3];			// ����� X ��
	int nY;				// ����� Y ��
	clock_t OldTime;	// ����� �� �ð�
	clock_t MoveTime;	// ����� �����̴� �ð�
} BAR;					// �̸� BAR�� ����