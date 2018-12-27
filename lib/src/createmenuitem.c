//
// Created by zdavid on 23/12/18.
//

#include "../headers/createmenuitem.h"
#include <stdlib.h>
#include <string.h>

/**
 * Create a MENUITEM linked list element
 *
 * @param item
 * @return
 */
MENUITEM *createMenuItem(char item[VIEW_WIDTH])
{
    MENUITEM *current = (MENUITEM *)malloc(sizeof(MENUITEM));
    strcpy(current->title, item);
    current->next = NULL;
    return current;
}
