#pragma once

// Ű���� ��  
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // ����(�����̽���) 

#include <stdint.h>
#include <stdbool.h>

///<summary>
//���Ӱ� ���õ� �����͸� �ʱ�ȭ�մϴ�.
///</summary>
///<return> ���������� �ʱ�ȭ ������ true , �ƴϸ� false</return>
bool Initialize();


/// <summary>
/// ������ ���۽�Ų��.
/// </summary>
/// <returns>���������� ���� �ƴٸ� 0</returns>
int32_t Run();

