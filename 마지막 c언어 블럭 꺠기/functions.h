#pragma once
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "Screen.h"

void InitScreen(void);		// 소개 인터페이스
void ReadyScreen(void);		// 준비 인터페이스
void SuccessScreen(void);	// 성공 인터페이스
void FailureScreen(void);	// 실패 인터페이스
void RunningScreen(void);	// 작동중 인터페이스

int Collision(int, int);	// 충돌 기능
void Update(void);			// 게임상태 업데이트
void Init(void);			// 기본값
void Render(void);			// 화면 표시
void SetBlock(int);			// 블럭 배치
int Search(int, int, int);	// 블럭 중복 방지