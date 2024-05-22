#pragma once

#define TRUE 1
#define FALSE 0
#define CHARACTER_DATA 100
#define ATTACK_POWER 11

typedef int	BOOL;

typedef struct
{
	BOOL bIsLive;
	int nDamage;
	int nLife;
}CHARACTER;

void InitCharacter(CHARACTER* character);