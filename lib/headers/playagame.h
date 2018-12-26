//
// Created by zdavid on 26/12/18.
//

#ifndef HANGMAN_PLAYAGAME_H
#define HANGMAN_PLAYAGAME_H

#include "selectcategory.h"
#include "renderHang.h"

int playAGame(char *category, char *word, char *letterGuesses, unsigned int countOfFails);

#endif //HANGMAN_PLAYAGAME_H
