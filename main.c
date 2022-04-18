﻿/*include 될 헤더*/
#include "stdafx.h"             //공통 라이브러리
#include "Framework/Game.h"     //게임관련 데이터 헤더파일

/****************************************************************
* 설명 : main 함수 실행 
*****************************************************************/
int main()
{   
    titleDraw();
    if (false == Initialize()) //게임과 관련된 데이터 초기화 함수.
    {
        puts("게임을 로딩하는 데 문제가 생겼습니다.");
        return 1;
    }
    return Run();
}
