#include "Timer.h"
#include "stdafx.h"

static clock_t s_prevTick;
static float s_deltaTime;


void InitializeTimer()
{
	s_prevTick = clock();
}


void UpdateTimer()
{
	clock_t currentTick = clock();

	s_deltaTime = (currentTick - s_prevTick) / (float)CLOCKS_PER_SEC;
	//현재시간 - 지나온 시간 / 1000
	s_prevTick = currentTick;
	// 이전 시간에다가 찍어준 시간 넣어줌
}

float GetDeltaTime()	//프레임 사이의 간격
{
	return s_deltaTime;
}

