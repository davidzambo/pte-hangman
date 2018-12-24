//
// Created by zdavid on 23/12/18.
//

#include "headers/createmenuitem.h"
#include <stdlib.h>
#include <string.h>

MENUITEM *createMenuItem(char item[32])
{
    MENUITEM *current = (MENUITEM *)malloc(sizeof(MENUITEM));
    strcpy(current->title, item);
    current->next = NULL;
    return current;
}
