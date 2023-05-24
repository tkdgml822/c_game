#include "MyVariable.h"
#include "functions.h"
#include <mysql.h>

#define DB_HOST "127.0.0.1" // ip
#define DB_USER "root"		// username
#define DB_PASS "abc123"	// userpassword
#define DB_NAME "test"		// tablename
#define DB_PORT 3306		// mySQLport

void SettingMenu(void) {
	int choice;
	init_interFace(); // 기본 화면
	
	printf("유저확인 : 0");
	printf("진행 : 1");
	scanf("%d", &choice);
}