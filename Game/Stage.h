#pragma once

//����
//1. ���������� �ҷ���
//2. �������� ���� ��Ȳ�� ����
//3. �������� Ŭ���� �ƴ���?

typedef enum MapType
{
	MAPTYPE_WALL = '#',
	MAPTYPE_PLAYER = 'P',
	MAPTYPE_BOX = 'B',
	MAPTYPE_GOAL = 'O',
	MAPTYPE_BOX_ON_GOAL = '@',
	MAPTYPE_PATH = ' '
}EMapType;

typedef enum StageLevel
{
	STAGE_01 = 1,
	STAGE_02,
	STAGE_03,
	STAGE_04,
	STAGE_MAX
}EStageLevel;

///<summary>
///���������� �ε��Ѵ�
///</summary>
void LoadStage(EStageLevel level);

///<summary>
///���������� ������Ʈ�Ѵ�
///</summary>
void UpdateStage();

///<summary>
///���� ��ȯ�Ѵ�.
///</summary>
const char** GetMap();

///<summary>
///�÷��̾ x�Ǵ� y��ŭ �̵� ��Ų��.
///</summary>
///<param name = "x" > �̵��� x ��ǥ </param>
///<param name = "y" > �̵��� y ��ǥ </param>
void PlayerMove(int x, int y);

///<summary>
///�÷��̾ �̵��Ҷ��� ����ó���� �ϴ� �Լ�.
///</summary>
///<param name = "x" > �̵��� x ��ǥ </param>
///<param name = "y" > �̵��� y ��ǥ </param>
void MoveException(int x, int y);

///<summary>
/// ������ �������� �˻��Ѵ�.
///</summary>
int ClearCondition();