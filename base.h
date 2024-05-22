#pragma once
#include <windows.h>
#include <time.h>

#define randomize() srand((unsigned)time(NULL)) //난수에 시드값(시작점)넣는 함수
#define random(n) (rand() % (n)) //랜덤한 값 반환 함수
#define delay(n) Sleep(n) //대기 함수
#define clrscr() system("cls") //콘솔창을 전부 지워줌