#include "AttackedCharacter.h"

void AttackedCharacter(CHARACTER* character)
{
	if (character->bIsLive)
	{
		character->nDamage = rand() % ATTACK_POWER; // 데미지의 범위 0 ~ 10
		character->nLife -= character->nDamage;

		if (character->nLife <= 0) // 캐릭터의 라이프가 0이하라면 생존 여부 FALSE반환
		{
			character->bIsLive = FALSE;
		}
	}
}