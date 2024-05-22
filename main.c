#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MainScene.h"
#include "InitCharacter.h"
#include "AttackedCharacter.h"
#include "SaveNLoad.h"

void main()
{
	randomize();

	CHARACTER characters[CHARACTER_DATA];
	CHARACTER Grave[CHARACTER_DATA];
	int CharacterCount = CHARACTER_DATA; // 현재 살아있는 캐릭터 수 초기화
	int GraveCount = 0; // 무덤 초기화
	int liveCharacter = 0, dieCharacter = 0; // 생존한 캐릭터, 죽은 캐릭터 초기화

	int choice = 0;

	while (choice != 3)
	{
		printMenu();
		printf("메뉴를 선택하세요 (1, 2, 3): ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			// New Game
			for (int i = 0; i < CHARACTER_DATA; ++i) {
				InitCharacter(&characters[i]);
			}
			printf("새로운 게임을 시작합니다.\n");
			break;
		case 2:
			// Continue Game
			loadCharacters(characters, &CharacterCount);
			printf("이어진 게임을 시작합니다.\n");
			break;
		case 3:
			// Exit
			printf("프로그램을 종료합니다.\n");
			break;
		default:
			printf("잘못된 메뉴 선택입니다. 다시 선택하세요.\n");
		}
		if (choice != 3)
		{
			//캐릭터 초기화
			for (int i = 0; i < CHARACTER_DATA; i++)
			{
				InitCharacter(&characters[i]);
			}

			while (TRUE)
			{
				int reviveCount = 0; // 부활한 캐릭터 수 초기화

				int noneAttackedCharacter = GraveCount;
				// 이번 턴에 공격을 받지않은 캐릭터 수 초기화
				// 무덤으로 가면 공격을 받지 않으므로 무덤의 있는 캐릭터 수로 초기화

				int curDie = 0; // 이번 턴 공격으로 죽은 캐릭터 수 초기화 


				// 모든 캐릭터들에게 데미지를 입힘
				for (int i = 0; i < CharacterCount; i++)
				{
					AttackedCharacter(&characters[i]);

					if (!characters[i].bIsLive) // 캐릭터의 생존여부가 FALSE라면
					{
						Grave[GraveCount++] = characters[i]; // 무덤 인덱스에 해당 캐릭터를 넣는다.
						characters[i] = characters[i + 1]; // 캐릭터 배열에 비어있는 부분을 땡긴다.
						CharacterCount--; // 현재 살아있는 캐릭터 수를 줄인다.
					}
				}

				curDie = GraveCount - noneAttackedCharacter;
				// 이번 턴에 죽은 캐릭터 수
				// 무덤에 있는 전체 캐릭터 수에서 이미 죽어있던 캐릭터 수를 뺌
				liveCharacter = CharacterCount;
				// 현재 생존한 캐릭터의 수 초기화
				dieCharacter = GraveCount;
				// 사망 캐릭터는 무덤에 들어가 있는 캐릭터의 수

				if (GraveCount >= 10) // 현재 무덤에 10명 이상에 캐릭터가 있다면
				{
					int reviveAmount = (int)(0.1 * GraveCount); // 무덤 전체 인원의 10%
					for (int i = 0; i < reviveAmount; i++)
					{
						int picked = random(GraveCount); // 랜덤으로 무덤에 있는 캐릭터 추출
						characters[++CharacterCount] = Grave[picked];
						InitCharacter(&characters[CharacterCount]); // 그 캐릭터를 부활시키고 다시 초기화
						for (int j = picked; j < GraveCount; j++) // 비어있는 무덤 공간부터 다시 앞으로 땡김
						{
							Grave[picked] = Grave[picked + 1];
						}

						reviveCount++; // 부활한 플레이어 수 증가
						GraveCount--; // 무덤의 있는 인원 수 감소
					}
				}
				else // 10명 이상이 안된다면
				{
					CharacterCount += reviveCount; // 전체 생존인원에 부활한 캐릭터 수 더함
					GraveCount -= reviveCount; // 부활한 캐릭터 무덤에 있는 캐릭터 수에 뺌
				}

				saveCharacters(characters, CharacterCount);

				printf("--------------Current Trun Board-------------\n\n");
				printf("생존 캐릭터 %d명, 사망 캐릭터 %d명\n", liveCharacter, dieCharacter);
				printf("부활 캐릭터 %d명\n", reviveCount);
				printf("이번 공격으로 죽은 캐릭터 %d명\n", curDie);
				printf("이번 공격에 공격 받지 않은 캐릭터 %d명\n", noneAttackedCharacter);

				printf("\n---------------Character State---------------\n\n");
				for (int i = 0; i < CharacterCount; i++)
				{
					printf("%d번째 용사 / 현재 체력 %d / 입은 피해량 %d \n", i + 1, characters[i].nLife, characters[i].nDamage);
				}

				char input = getchar();

				// Clear input buffer
				while (getchar() != '\n');


			}
		}
	}
}