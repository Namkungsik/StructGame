#pragma once
#include <windows.h>
#include <time.h>

#define randomize() srand((unsigned)time(NULL)) //������ �õ尪(������)�ִ� �Լ�
#define random(n) (rand() % (n)) //������ �� ��ȯ �Լ�
#define delay(n) Sleep(n) //��� �Լ�
#define clrscr() system("cls") //�ܼ�â�� ���� ������