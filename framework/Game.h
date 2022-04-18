#pragma once

// 키보드 값  
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // 선택(스페이스바) 

#include <stdint.h>
#include <stdbool.h>

///<summary>
//게임과 관련된 데이터를 초기화합니다.
///</summary>
///<return> 정상적으로 초기화 했으면 true , 아니면 false</return>
bool Initialize();


/// <summary>
/// 게임을 동작시킨다.
/// </summary>
/// <returns>정상적으로 종로 됐다면 0</returns>
int32_t Run();

