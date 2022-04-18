#include "stdafx.h"
#include "Renderer.h"
#include "../Game/Stage.h"

static char s_map[MAP_SIZE][MAP_SIZE];	//맵 설정
static HANDLE s_consoleHandle;			//핸들 설정

/*************************************************************
* 설명 : 맵을 초기화 한다.
**************************************************************/
void clear()
{
	memset(s_map, ' ', sizeof(s_map));

	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		s_map[i][MAP_SIZE - 1] = '\0';
	}
}

/*************************************************************
* 설명 : 커서의 위치를 이동시킨다.
**************************************************************/
void gotoxy(int x, int y) {
	s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(s_consoleHandle, pos);
}

/*************************************************************
* 설명 : 컬러를 변경시킨다.
* 매개변수1 : 텍스트 // 매개변수2 : 배경 
**************************************************************/
void setColor(int forground, int background) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들가져오기 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}

/*************************************************************
* 설명 : 렌더러(Renderer)를 초기화한다.
**************************************************************/
bool InitializeRenderer()
{	//GetStdHandle => 표준 디바이스에 대한 핸들 검색
	
	s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);		//표준 출력 디바이스
	
	if (INVALID_HANDLE_VALUE == s_consoleHandle)		//함수 실패 반환 값이 s_consoleHandle
	{
		return false;
	}
	return true;
}



/*************************************************************
* 설명 : 맵을 그리는 함수
**************************************************************/
void RenderMap()
{
	const static COORD initialPos = { 0, 0 };				//콘솔 화면 버퍼에서 문자 셀의 좌표를 정의.
	const static CONSOLE_CURSOR_INFO info = {100, false};	//콘솔창에서 커서 on/off
	SetConsoleCursorPosition(s_consoleHandle, initialPos);	//지정된 콘솔 화면 버퍼에서 커서 위치를 설정
	SetConsoleCursorInfo(s_consoleHandle, &info);			// 콘솔 커서의 형태 (두께 or 노출여부) 를 설정하는 역할

	const char** stage = GetMap();
	memcpy(s_map, stage, sizeof(s_map));

	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		puts(s_map[i]);		//초당 MAP_SIZE만큼 출력
	}	
	clear();
	
}

//void SetMessage(const char* message)
//{
//	strcpy_s(s_map[0], MAP_SIZE, message);
//}
//
//void SetKeyMessage(int32_t keyCode)
//{
//	sprintf_s(s_map[0], sizeof(s_map[0]), "%c키가 눌림", keyCode);
//}