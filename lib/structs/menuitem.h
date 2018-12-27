//
// Created by zdavid on 23/12/18.
//

#ifndef HANGMAN_MENUITEM_H
#define HANGMAN_MENUITEM_H
#define VIEW_WIDTH 60

typedef struct MenuItem
{
    char title[VIEW_WIDTH + 1];
    struct MenuItem *next;
} MENUITEM;

#endif //HANGMAN_MENUITEM_H
