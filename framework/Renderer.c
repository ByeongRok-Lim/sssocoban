#include "stdafx.h"
#include "Renderer.h"
#include "../Game/Stage.h"

static char s_map[MAP_SIZE][MAP_SIZE];	//�� ����
static HANDLE s_consoleHandle;			//�ڵ� ����

/*************************************************************
* ���� : ���� �ʱ�ȭ �Ѵ�.
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
* ���� : Ŀ���� ��ġ�� �̵���Ų��.
**************************************************************/
void gotoxy(int x, int y) {
	s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(s_consoleHandle, pos);
}

/*************************************************************
* ���� : �÷��� �����Ų��.
* �Ű�����1 : �ؽ�Ʈ // �Ű�����2 : ��� 
**************************************************************/
void setColor(int forground, int background) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ鰡������ 
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}

/*************************************************************
* ���� : ������(Renderer)�� �ʱ�ȭ�Ѵ�.
**************************************************************/
bool InitializeRenderer()
{	//GetStdHandle => ǥ�� ����̽��� ���� �ڵ� �˻�
	
	s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);		//ǥ�� ��� ����̽�
	
	if (INVALID_HANDLE_VALUE == s_consoleHandle)		//�Լ� ���� ��ȯ ���� s_consoleHandle
	{
		return false;
	}
	return true;
}



/*************************************************************
* ���� : ���� �׸��� �Լ�
**************************************************************/
void RenderMap()
{
	const static COORD initialPos = { 0, 0 };				//�ܼ� ȭ�� ���ۿ��� ���� ���� ��ǥ�� ����.
	const static CONSOLE_CURSOR_INFO info = {100, false};	//�ܼ�â���� Ŀ�� on/off
	SetConsoleCursorPosition(s_consoleHandle, initialPos);	//������ �ܼ� ȭ�� ���ۿ��� Ŀ�� ��ġ�� ����
	SetConsoleCursorInfo(s_consoleHandle, &info);			// �ܼ� Ŀ���� ���� (�β� or ���⿩��) �� �����ϴ� ����

	const char** stage = GetMap();
	memcpy(s_map, stage, sizeof(s_map));

	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		puts(s_map[i]);		//�ʴ� MAP_SIZE��ŭ ���
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
//	sprintf_s(s_map[0], sizeof(s_map[0]), "%cŰ�� ����", keyCode);
//}