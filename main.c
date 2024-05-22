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
	int CharacterCount = CHARACTER_DATA; // ���� ����ִ� ĳ���� �� �ʱ�ȭ
	int GraveCount = 0; // ���� �ʱ�ȭ
	int liveCharacter = 0, dieCharacter = 0; // ������ ĳ����, ���� ĳ���� �ʱ�ȭ

	int choice = 0;

	while (choice != 3)
	{
		printMenu();
		printf("�޴��� �����ϼ��� (1, 2, 3): ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			// New Game
			for (int i = 0; i < CHARACTER_DATA; ++i) {
				InitCharacter(&characters[i]);
			}
			printf("���ο� ������ �����մϴ�.\n");
			break;
		case 2:
			// Continue Game
			loadCharacters(characters, &CharacterCount);
			printf("�̾��� ������ �����մϴ�.\n");
			break;
		case 3:
			// Exit
			printf("���α׷��� �����մϴ�.\n");
			break;
		default:
			printf("�߸��� �޴� �����Դϴ�. �ٽ� �����ϼ���.\n");
		}
		if (choice != 3)
		{
			//ĳ���� �ʱ�ȭ
			for (int i = 0; i < CHARACTER_DATA; i++)
			{
				InitCharacter(&characters[i]);
			}

			while (TRUE)
			{
				int reviveCount = 0; // ��Ȱ�� ĳ���� �� �ʱ�ȭ

				int noneAttackedCharacter = GraveCount;
				// �̹� �Ͽ� ������ �������� ĳ���� �� �ʱ�ȭ
				// �������� ���� ������ ���� �����Ƿ� ������ �ִ� ĳ���� ���� �ʱ�ȭ

				int curDie = 0; // �̹� �� �������� ���� ĳ���� �� �ʱ�ȭ 


				// ��� ĳ���͵鿡�� �������� ����
				for (int i = 0; i < CharacterCount; i++)
				{
					AttackedCharacter(&characters[i]);

					if (!characters[i].bIsLive) // ĳ������ �������ΰ� FALSE���
					{
						Grave[GraveCount++] = characters[i]; // ���� �ε����� �ش� ĳ���͸� �ִ´�.
						characters[i] = characters[i + 1]; // ĳ���� �迭�� ����ִ� �κ��� �����.
						CharacterCount--; // ���� ����ִ� ĳ���� ���� ���δ�.
					}
				}

				curDie = GraveCount - noneAttackedCharacter;
				// �̹� �Ͽ� ���� ĳ���� ��
				// ������ �ִ� ��ü ĳ���� ������ �̹� �׾��ִ� ĳ���� ���� ��
				liveCharacter = CharacterCount;
				// ���� ������ ĳ������ �� �ʱ�ȭ
				dieCharacter = GraveCount;
				// ��� ĳ���ʹ� ������ �� �ִ� ĳ������ ��

				if (GraveCount >= 10) // ���� ������ 10�� �̻� ĳ���Ͱ� �ִٸ�
				{
					int reviveAmount = (int)(0.1 * GraveCount); // ���� ��ü �ο��� 10%
					for (int i = 0; i < reviveAmount; i++)
					{
						int picked = random(GraveCount); // �������� ������ �ִ� ĳ���� ����
						characters[++CharacterCount] = Grave[picked];
						InitCharacter(&characters[CharacterCount]); // �� ĳ���͸� ��Ȱ��Ű�� �ٽ� �ʱ�ȭ
						for (int j = picked; j < GraveCount; j++) // ����ִ� ���� �������� �ٽ� ������ ����
						{
							Grave[picked] = Grave[picked + 1];
						}

						reviveCount++; // ��Ȱ�� �÷��̾� �� ����
						GraveCount--; // ������ �ִ� �ο� �� ����
					}
				}
				else // 10�� �̻��� �ȵȴٸ�
				{
					CharacterCount += reviveCount; // ��ü �����ο��� ��Ȱ�� ĳ���� �� ����
					GraveCount -= reviveCount; // ��Ȱ�� ĳ���� ������ �ִ� ĳ���� ���� ��
				}

				saveCharacters(characters, CharacterCount);

				printf("--------------Current Trun Board-------------\n\n");
				printf("���� ĳ���� %d��, ��� ĳ���� %d��\n", liveCharacter, dieCharacter);
				printf("��Ȱ ĳ���� %d��\n", reviveCount);
				printf("�̹� �������� ���� ĳ���� %d��\n", curDie);
				printf("�̹� ���ݿ� ���� ���� ���� ĳ���� %d��\n", noneAttackedCharacter);

				printf("\n---------------Character State---------------\n\n");
				for (int i = 0; i < CharacterCount; i++)
				{
					printf("%d��° ��� / ���� ü�� %d / ���� ���ط� %d \n", i + 1, characters[i].nLife, characters[i].nDamage);
				}

				char input = getchar();

				// Clear input buffer
				while (getchar() != '\n');


			}
		}
	}
}