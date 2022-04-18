#include "stdafx.h"
#include "input.h"

static bool s_currentKeyStates[256] = { false };
static bool s_prevKeyStates[256] = { false };

/*************************************************************
* 설명 : 키가 눌렸는 상태인지 확인한다.
**************************************************************/

bool isKeyDown(int32_t keyCode)
{
	if (0x8000 & GetAsyncKeyState(keyCode))		//눌렀으면~
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************
* 설명 : 입력 상태를 업데이트 한다.
**************************************************************/
void UpdateInput()
{
	memcpy(s_prevKeyStates, s_currentKeyStates, sizeof(s_prevKeyStates));

	for (int32_t keyCode = 0; keyCode < 256; ++keyCode)
	{
		if (isKeyDown(keyCode))
		{
			s_currentKeyStates[keyCode] = true;
		}
		else
		{
			s_currentKeyStates[keyCode] = false;
		}
		
		//GetAsyncKeyState(keyCode); 
		//3가지 상태값을 반환한다.
		// 0x8000 => 0b 1000 0000 0000 0000 => 눌린 상태
		// 0x0001 => 0b 1000 0000 0000 0001 => 계속 눌린 상태
		// 0x0001 => 사이엔 눌렸는데 지금은 뗌
		// 0x0000 => 아예 안눌림
		//현재 키가 눌렀는지
		//현재 키가 떼어져있는지..? => MSB(1)가 set(1)인지 0인지
		//GetAsyncKeyState() --- GetAsyncKeyState()  <- 이거 믿고 사용하면 버그가 많데....
		//					  ↑ 요사이에 눌렸는지 => LSB Set

	}
}
/*************************************************************
* 설명 : 현재 프레임에 버튼이 눌렀는지 체크한다.
**************************************************************/
bool GetButtonDown(EKeyCode keyCode)
{
	if (false == s_prevKeyStates[keyCode] && s_currentKeyStates[keyCode])	//키코드에 인덱스를 부여하여 사용
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************
* 설명 : 현재 프레임에 버튼이 떼었는지 체크한다.
**************************************************************/
bool GetButtonUp(EKeyCode keyCode)
{
	if (s_prevKeyStates[keyCode] && false == s_currentKeyStates[keyCode])
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************
* 설명 : 버튼이 계속 눌렸는지 체크한다.
**************************************************************/
bool GetButton(EKeyCode keyCode)
{
	if (s_prevKeyStates[keyCode] && s_currentKeyStates[keyCode])
	{
		return true;
	}
	else
	{
		return false;
	}
}