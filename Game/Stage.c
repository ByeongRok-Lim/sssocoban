#include "stdafx.h"
#include "Stage.h"
#include "framework/input.h"
#include "framework/Renderer.h"

static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0;				//��ǥ����
static int32_t s_boxOnGoalCount = 0;		//���� �´� ����
static int32_t s_playerX = 0;				//�÷��̾� ��ǥ x
static int32_t s_playerY = 0;				//�÷��̾� ��ǥ y
static EStageLevel gameStage = STAGE_01;	//�ʱ� stage
static bool s_IsOnGoal = false;				//��ǥ 0 �� ������ üũ

/*************************************************************
* ���� : ���� �ε� �� ��, �� Ÿ�Ժ� �ؾ��ϴ� ���� �������ش�.
**************************************************************/
bool parseMapType(int i, int j, char mapType)
{
	if (mapType == '\0' || mapType == '\n')
	{
		return false;
	}
	s_map[i][j] = mapType;
	// �� �� Ÿ�Ժ��� ����� �ϴ� �ϵ�
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
* ���� : �޸𸮿��� �ʱ�ȭ �����ֱ� ���� �Լ�
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
	s_IsOnGoal = false;				//��ǥ 0 �� ������ üũ
}
/*************************************************************
* ���� : ���������� �ε��Ѵ�.
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
* ���� : ���������� �ε��� ��, Ű input�� ���� �̵���θ� �����ش�.
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
* ���� : ���� ��ȯ�Ѵ�.
***********************************************************/
const char** GetMap()
{
	return s_map;
}


/**********************************************************
* ���� : �÷��̾ x�Ǵ� y��ŭ �̵� ��Ų��.
***********************************************************/
void PlayerMove(int x, int y)
{
	// ���ÿ� originPoint == goal
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
	s_map[s_playerY][s_playerX] = MAPTYPE_PLAYER; //�̵� ��
}

/**********************************************************
* ���� : �÷��̾ �̵��Ҷ��� ����ó���� �ϴ� �Լ�.
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
* ���� : ������ �������� �˻��Ѵ�.
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
