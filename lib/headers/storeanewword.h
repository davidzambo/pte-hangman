//
// Created by zdavid on 26/12/18.
//

#ifndef HANGMAN_STOREANEWWORD_H
#define HANGMAN_STOREANEWWORD_H
#include "../structs/word.h"

void showSuccessFeedback(WORD *newWord);

int storeANewWord(char *category, char *newWord, char *filename, WORD **wordList, int length);

#endif //HANGMAN_STOREANEWWORD_H
