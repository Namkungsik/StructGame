#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "InitCharacter.h"

#define SAVE_FILE "charinfo.bin"

void saveCharacters(CHARACTER* characters, int characterCount);

void loadCharacters(CHARACTER* characters, int* characterCount);