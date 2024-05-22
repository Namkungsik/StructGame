#include "AttackedCharacter.h"

void AttackedCharacter(CHARACTER* character)
{
	if (character->bIsLive)
	{
		character->nDamage = rand() % ATTACK_POWER; // �������� ���� 0 ~ 10
		character->nLife -= character->nDamage;

		if (character->nLife <= 0) // ĳ������ �������� 0���϶�� ���� ���� FALSE��ȯ
		{
			character->bIsLive = FALSE;
		}
	}
}