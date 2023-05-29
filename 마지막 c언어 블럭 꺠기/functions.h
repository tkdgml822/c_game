#pragma once
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

int Collision(int, int);	// 충돌 기능
void Update(void);			// 게임상태 업데이트
void Init(void);			// 기본값
void Render(void);			// 화면 표시
void SetBlock(int);			// 블럭 배치
int Search(int, int, int);	// 블럭 중복 방지
void UserData(void);			// 유저 데이터베이스 연결
void newSign(void);		// 데이터 입력
int SettingMenu(void);		// 메뉴
void login(void);		 // 로그인
void score_check(void);  // 점수 체크
void userBestScore(void); // 데이터베이스에 있는 유저의 최고 점수