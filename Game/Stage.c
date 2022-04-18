#include "stdafx.h"
#include "Stage.h"
#include "framework/input.h"
#include "framework/Renderer.h"

static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0;				//목표갯수
static int32_t s_boxOnGoalCount = 0;		//현재 맞는 갯수
static int32_t s_playerX = 0;				//플레이어 좌표 x
static int32_t s_playerY = 0;				//플레이어 좌표 y
static EStageLevel gameStage = STAGE_01;	//초기 stage
static bool s_IsOnGoal = false;				//목표 0 의 위인지 체크

/*************************************************************
* 설명 : 맵이 로드 될 때, 맵 타입별 해야하는 일을 설정해준다.
**************************************************************/
bool parseMapType(int i, int j, char mapType)
{
	if (mapType == '\0' || mapType == '\n')
	{
		return false;
	}
	s_map[i][j] = mapType;
	// 각 맵 타입별로 해줘야 하는 일들
	switch (mapType)
	{
	case MAPTYPE_PLAYER:
		s_playerX = j;
		s_playerY = i;
		break;
	case MAPTYPE_GOAL:
		s_goalCount++;
		return true;
	default:
		s_map[i][j] = mapType;
	}
	return true;
}

/*************************************************************
* 설명 : 메모리에서 초기화 시켜주기 위한 함수
**************************************************************/
void clearStage()
{
	memset(s_map, ' ', sizeof(s_map));
	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		s_map[i][MAP_SIZE - 1] = '\0';
	}
	s_goalCount = 0;
	s_boxOnGoalCount = 0;
	s_playerX = 0;	
	s_playerY = 0;
	s_IsOnGoal = false;				//목표 0 의 위인지 체크
}
/*************************************************************
* 설명 : 스테이지를 로딩한다.
**************************************************************/
void LoadStage(EStageLevel level)
{
	assert(STAGE_01 <= level && level < STAGE_MAX);
	static char path[MAX_PATH] = { 0 };
	
	sprintf_s(path, sizeof(path), "Stage/Stage%02d.txt", (int32_t)level);
	FILE* fp = NULL;
	fopen_s(&fp, path, "r");
	assert(fp != NULL);
	
	clearStage();

	for (size_t i = 0; i < MAP_SIZE; ++i) 
	{
		for (size_t j = 0; j < MAP_SIZE; ++j) 
		{
			char ch = fgetc(fp);
			if (false == parseMapType(i, j, ch))
			{
				break;
			}
		}
		if (feof(fp))
		{
			break;
		}
	}
	fclose(fp);
}


/******************************************************************
* 설명 : 스테이지를 로드할 때, 키 input에 따른 이동경로를 정해준다.
*******************************************************************/
void UpdateStage()
{
	if (GetButtonDown(KEYCODE_W)) 
	{
		MoveException(0, -1);
	}
	else if (GetButtonDown(KEYCODE_D)) 
	{
		MoveException(1, 0);
	}
	else if (GetButtonDown(KEYCODE_S))
	{
		MoveException(0, 1);
	}
	else if (GetButtonDown(KEYCODE_A))
	{
		MoveException(-1, 0);
	}
	else if (GetButtonDown(KEYCODE_R))
	{
		LoadStage(gameStage);
	}
}

/**********************************************************
* 설명 : 맵을 반환한다.
***********************************************************/
const char** GetMap()
{
	return s_map;
}


/**********************************************************
* 설명 : 플레이어를 x또는 y만큼 이동 시킨다.
***********************************************************/
void PlayerMove(int x, int y)
{
	// 동시에 originPoint == goal
	if (s_IsOnGoal == true)
	{
		// origin -> goal
		s_map[s_playerY][s_playerX] = MAPTYPE_GOAL;
		s_IsOnGoal = false;
	}
	else 
	{
		s_map[s_playerY][s_playerX] = MAPTYPE_PATH;
	}
	s_playerX += x;
	s_playerY += y;
	s_map[s_playerY][s_playerX] = MAPTYPE_PLAYER; //이동 끝
}

/**********************************************************
* 설명 : 플레이어가 이동할때의 예외처리를 하는 함수.
***********************************************************/
void MoveException(int x, int y)
{
	char originPoint = s_map[s_playerY][s_playerX];
	char getMapPoint = s_map[s_playerY + y][s_playerX + x];
	char nextBoxPoint = s_map[s_playerY + (y*2)][s_playerX + (x * 2)];
	
	
	if (getMapPoint != MAPTYPE_GOAL)
	{
		if (getMapPoint == MAPTYPE_WALL)
		{
			return;
		}
		if (getMapPoint == MAPTYPE_BOX_ON_GOAL)
		{	
			if (nextBoxPoint == MAPTYPE_WALL)
			{
				return;
			}
			else if (nextBoxPoint == MAPTYPE_PATH)
			{
				s_map[s_playerY + (y * 2)][s_playerX + (x * 2)] = MAPTYPE_BOX;
				PlayerMove(x, y);
				s_IsOnGoal = true;
				return;
			}
			else if (nextBoxPoint == MAPTYPE_BOX)
			{
				return;
			}
			else if (nextBoxPoint == MAPTYPE_BOX_ON_GOAL)
			{
				return;
			}
			else if (nextBoxPoint == MAPTYPE_GOAL)
			{
				s_map[s_playerY + (y * 2)][s_playerX + (x * 2)] = MAPTYPE_BOX_ON_GOAL;
				PlayerMove(x, y);
				s_IsOnGoal = true;
				return;
			}
		}
	
		if (getMapPoint == MAPTYPE_BOX)
		{
			if (nextBoxPoint != MAPTYPE_WALL)
			{
				s_map[s_playerY][s_playerX] = MAPTYPE_PATH;
				if (nextBoxPoint == MAPTYPE_GOAL)
				{
					s_map[s_playerY + (y * 2)][s_playerX + (x * 2)] = MAPTYPE_BOX_ON_GOAL;
					s_boxOnGoalCount++;
				}
				else if (nextBoxPoint == MAPTYPE_BOX)
				{
					s_map[s_playerY][s_playerX] = MAPTYPE_PLAYER;
					return;
				}
				else
				{
					s_map[s_playerY + (y * 2)][s_playerX + (x * 2)] = MAPTYPE_BOX;
				}
				PlayerMove(x, y);
			}
		}
		else
		{
			PlayerMove(x, y);
		}
	}
	else if (getMapPoint == MAPTYPE_GOAL)
	{
		PlayerMove(x, y);
		s_IsOnGoal = true;
	}
	
	
}
/**********************************************************
* 설명 : 게임이 끝났는지 검사한다.
***********************************************************/
int ClearCondition()
{
	if (s_boxOnGoalCount == s_goalCount)
	{
		gameStage++;
		return 0;
	}
	return 1;
}
