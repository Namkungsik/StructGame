#include "SaveNLoad.h"
#pragma warning(disable:4996)

void saveCharacters(CHARACTER* characters, int characterCount)
{
    FILE* file = fopen(SAVE_FILE, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(characters, sizeof(CHARACTER), characterCount, file);

    fclose(file);
}

void loadCharacters(CHARACTER* characters, int* characterCount)
{
    FILE* file = fopen(SAVE_FILE, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    fread(characters, sizeof(CHARACTER), CHARACTER_DATA, file);

    // Calculate the actual number of characters loaded
    fseek(file, 0, SEEK_END);
    *characterCount = ftell(file) / sizeof(CHARACTER);

    fclose(file);
}
