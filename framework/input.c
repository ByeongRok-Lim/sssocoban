#include "stdafx.h"
#include "input.h"

static bool s_currentKeyStates[256] = { false };
static bool s_prevKeyStates[256] = { false };

/*************************************************************
* ���� : Ű�� ���ȴ� �������� Ȯ���Ѵ�.
**************************************************************/

bool isKeyDown(int32_t keyCode)
{
	if (0x8000 & GetAsyncKeyState(keyCode))		//��������~
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************
* ���� : �Է� ���¸� ������Ʈ �Ѵ�.
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
		//3���� ���°��� ��ȯ�Ѵ�.
		// 0x8000 => 0b 1000 0000 0000 0000 => ���� ����
		// 0x0001 => 0b 1000 0000 0000 0001 => ��� ���� ����
		// 0x0001 => ���̿� ���ȴµ� ������ ��
		// 0x0000 => �ƿ� �ȴ���
		//���� Ű�� ��������
		//���� Ű�� �������ִ���..? => MSB(1)�� set(1)���� 0����
		//GetAsyncKeyState() --- GetAsyncKeyState()  <- �̰� �ϰ� ����ϸ� ���װ� ����....
		//					  �� ����̿� ���ȴ��� => LSB Set

	}
}
/*************************************************************
* ���� : ���� �����ӿ� ��ư�� �������� üũ�Ѵ�.
**************************************************************/
bool GetButtonDown(EKeyCode keyCode)
{
	if (false == s_prevKeyStates[keyCode] && s_currentKeyStates[keyCode])	//Ű�ڵ忡 �ε����� �ο��Ͽ� ���
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*************************************************************
* ���� : ���� �����ӿ� ��ư�� �������� üũ�Ѵ�.
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
* ���� : ��ư�� ��� ���ȴ��� üũ�Ѵ�.
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