#pragma once
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "Screen.h"

void InitScreen(void);		// �Ұ� �������̽�
void ReadyScreen(void);		// �غ� �������̽�
void SuccessScreen(void);	// ���� �������̽�
void FailureScreen(void);	// ���� �������̽�
void RunningScreen(void);	// �۵��� �������̽�

int Collision(int, int);	// �浹 ���
void Update(void);			// ���ӻ��� ������Ʈ
void Init(void);			// �⺻��
void Render(void);




