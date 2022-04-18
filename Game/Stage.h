#pragma once

//역할
//1. 스테이지를 불러옴
//2. 스테이지 현재 상황을 보관
//3. 스테이지 클리어 됐는지?

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
///스테이지를 로딩한다
///</summary>
void LoadStage(EStageLevel level);

///<summary>
///스테이지를 업데이트한다
///</summary>
void UpdateStage();

///<summary>
///맵을 반환한다.
///</summary>
const char** GetMap();

///<summary>
///플레이어를 x또는 y만큼 이동 시킨다.
///</summary>
///<param name = "x" > 이동할 x 좌표 </param>
///<param name = "y" > 이동할 y 좌표 </param>
void PlayerMove(int x, int y);

///<summary>
///플레이어가 이동할때의 예외처리를 하는 함수.
///</summary>
///<param name = "x" > 이동할 x 좌표 </param>
///<param name = "y" > 이동할 y 좌표 </param>
void MoveException(int x, int y);

///<summary>
/// 게임이 끝났는지 검사한다.
///</summary>
int ClearCondition();