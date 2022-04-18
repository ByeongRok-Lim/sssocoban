/*include 될 헤더*/
#include "stdafx.h"
#include "Game.h"
#include "Renderer.h"
#include "input.h"
#include "Timer.h"
#include "Game/Stage.h"

static EStageLevel gameStage = STAGE_01;
/*************************************************************
* 설명 : 게임과 관련된 데이터를 초기화 하는 함수.
**************************************************************/
bool Initialize()
{
	system("mode con cols=100 lines=50 | title 무소유갱");
	if (false == InitializeRenderer())	//렌더러를 초기화하는 함수
	{
		return false;
	}
	InitializeTimer();		//타이머 초기화.

	LoadStage(STAGE_01);	//스테이지 로딩
	return true;
}
/*************************************************************
* 설명 : 맵의 제목을 출력한다.
**************************************************************/
void titleDraw() {
	printf("\n\n"); // 맨위에 2칸 개행  
	printf("    #####    ###    ###    #    ####   ##### \n");
	printf("    #       #      #      # #   #   #  #     \n");
	printf("    ####    ####   #     #####  ####   ####  \n");
	printf("    #           #  #     #   #  #      #     \n");
	printf("    #####   ####    ###  #   #  #      ##### \n");
	Sleep(3000);
}

/****************************************************************
* 설명 : 게임 전체에서의 입력처리를 해준다.
*****************************************************************/
void processInput()
{
	UpdateInput();
}

/****************************************************************
* 설명 : 게임 중에 변화하는 상태들을 업데이트한다.
*****************************************************************/
void update()
{
	UpdateStage();
	//0.5초 간격으로 특정 메시지를 깜빡이기.
	
	//float xTime = 1.0;
	//float oTime = 2.0;

	//static float delta = 0.0;
	//delta += GetDeltaTime();

	//if (delta >= xTime)
	//{
	//	SetMessage("뭐라 그러는 거냐");

	//}

	//if (delta >= xTime + oTime)
	//{
	//	delta = 0.0;
	//}

	
}

/****************************************************************
* 설명 : 맵을 콘솔에서 텍스트형태로 출력한다.
*****************************************************************/
void render()
{
	RenderMap();
}

/****************************************************************
* 설명 : 전체적인 게임의 흐름을 정의한다.
*****************************************************************/
int32_t Run()
{
	//Game Loop의 전체를 Frame
	while (true)
	{
		UpdateTimer();
		//프레임 시작 ------- 다음프레임 시작
		//				↑ 여기가 델타 타임
		//입력처리
		processInput();	//키입력 어떤건지 
		//업데이트
		update();
		//렌더링
		render();
		if (ClearCondition() == 0)
		{
			clearStage();
			gameStage++;
			if (gameStage == STAGE_MAX) 
			{
				break;
			}
			LoadStage(gameStage);
		}
		
	}
	return 0;

}