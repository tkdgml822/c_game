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
void InputData(void);		// 데이터 입력
int SettingMenu(void);		// 메뉴