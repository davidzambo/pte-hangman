//
// Created by zdavid on 23/12/18.
//

#ifndef HANGMAN_MENUITEM_H
#define HANGMAN_MENUITEM_H

typedef struct MenuItem
{
    char title[40];
    struct MenuItem *next;
} MENUITEM;

#endif //HANGMAN_MENUITEM_H
