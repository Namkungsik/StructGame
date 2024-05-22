#include "InitCharacter.h"

void InitCharacter(CHARACTER* character)
{
	character->bIsLive = TRUE;
	character->nLife = rand() % (100 - 50 + 1) + 50;
}