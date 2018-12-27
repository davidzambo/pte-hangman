//
// Created by zdavid on 23/12/18.
//

#ifndef HANGMAN_SELECTCATEGORY_H
#define HANGMAN_SELECTCATEGORY_H
#include "categories.h"
#include "../structs/menuitem.h"
#include "createmenuitem.h"
#include "renderview.h"
#include "../structs/word.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

char selectCategory();

char *selectAWordFromCategory(char category, WORD **words, int length);

#endif //HANGMAN_SELECTCATEGORY_H
