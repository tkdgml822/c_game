#pragma once

typedef enum _GAME_STATE {	// 게임 스테이지 구조체
	INIT,					// 초기 상태
	READY,					// 준비 상태 
	RUNNING,				// 가동 상태
	SUCCESS,				// 스테이지 클리어 상태
	FAILED,					// 스테이지 실패 상태
	STOP,					// 게임 멈췄을 때
	RESULT					// 결과 값
} GAME_STATE;				// Game_State로 이름 재설정

// 공의 각도 구조체
typedef enum _DIRECT {	// 공 방향 구조체
	TOP,				// 위쪽
	LEFT_TOP,			// 위쪽 왼쪽 대각선
	LEFT_DOWN,			// 밑쪽 왼쪽 대각선
	DOWN,				// 밑으로
	RIGHT_DOWN,			// 밑쪽 오른쪽 대각선
	RIGHT_TOP			// 위쪽 오른쪽 대각선
} DIRECT;				// 이름 DIRECT으로 재설정

// 스테이지 구조체
typedef struct _STAGE_INFO {	// 스테이지 속성 구조체
	int      nBlockCount;		// 벽돌 개수
	clock_t  LimitTime;			// 제한 시간
	clock_t  ball_MoveTime;		// 공이 움직이는 속도
} STAGE_INFO;					// STAGE_INFO으로 구조체 이름 재설정

// 공 구조체
typedef struct _BALL {   // 공 구조체
	int		 nReady;     // 1 이면 준비 상태, 0이면 이동 상태
	int		 nHP;        // 생명
	int		 nX, nY;     // 좌표
	DIRECT   nDirect;    // 이동 방향
	clock_t  MoveTime;   // 이동 시간 간격
	clock_t  OldTime;	 // 이전 이동 시각
} BALL;					 // 이름 BALL로 선언

// 블럭 구조체
typedef struct _BLOCK { // 블럭 구조체
	int  nLife;			// 블럭 체력
	int  nX, nY;		// 블럭 X, Y축
} BLOCK;				// 이름 BLOCK로 선언

// 막대기 구조체
typedef struct _BAR {	// 막대기 구조체
	int nX[3];			// 막대기 X 축
	int nY;				// 막대기 Y 축
	clock_t OldTime;	// 막대기 전 시간
	clock_t MoveTime;	// 막대기 움직이는 시간
} BAR;					// 이름 BAR로 선언