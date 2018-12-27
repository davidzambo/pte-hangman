//
// Created by zdavid on 24/12/18.
//

#include "../headers/renderHang.h"
#include "../headers/createmenuitem.h"
#include <string.h>

MENUITEM *renderHang(char *category, int stage)
{
    int i = 0,
        lengthOfCategory = (int) strlen(category),
        beginningOfCategory = (VIEW_WIDTH - lengthOfCategory) / 2 - 2;

    char localCategory[lengthOfCategory];
    strcpy(localCategory, category);
    localCategory[lengthOfCategory] = ' ';
    char title[VIEW_WIDTH];

    for (i = 0; i < VIEW_WIDTH; i++) {
        if ((i < beginningOfCategory) || (i > beginningOfCategory + lengthOfCategory + 1)) {
            title[i] = '=';
        } else if ((i == beginningOfCategory ) || (i == beginningOfCategory + lengthOfCategory + 2)) {
            title[i] = ' ';
        } else {
            title[i] = localCategory[i - beginningOfCategory - 1];
        }
    }
    title[i] = '\0';

    MENUITEM *menu;
    menu = createMenuItem(title);
    MENUITEM *first = menu;

    switch (stage) {
        case 1:
            menu->next = createMenuItem(" "); menu = menu->next;

            for (i = 0; i < 8; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 2:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;

            for (i = 0; i < 8; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 3:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                                            \\  |"); menu = menu->next;
            menu->next = createMenuItem("                                             \\ |"); menu = menu->next;
            menu->next = createMenuItem("                                              \\|"); menu = menu->next;

            for (i = 0; i < 5; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 4:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                             |              \\  |"); menu = menu->next;
            menu->next = createMenuItem("                             |               \\ |"); menu = menu->next;
            menu->next = createMenuItem("                                              \\|"); menu = menu->next;

            for (i = 0; i < 5; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 5:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                             |              \\  |"); menu = menu->next;
            menu->next = createMenuItem("                             |               \\ |"); menu = menu->next;
            menu->next = createMenuItem("                             O                \\|"); menu = menu->next;

            for (i = 0; i < 5; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 6:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                             |              \\  |"); menu = menu->next;
            menu->next = createMenuItem("                             |               \\ |"); menu = menu->next;
            menu->next = createMenuItem("                             O                \\|"); menu = menu->next;
            menu->next = createMenuItem("                             |                 |"); menu = menu->next;

            for (i = 0; i < 4; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 7:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                             |              \\  |"); menu = menu->next;
            menu->next = createMenuItem("                             |               \\ |"); menu = menu->next;
            menu->next = createMenuItem("                             O                \\|"); menu = menu->next;
            menu->next = createMenuItem("                            /|                 |"); menu = menu->next;

            for (i = 0; i < 4; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 8:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                             |              \\  |"); menu = menu->next;
            menu->next = createMenuItem("                             |               \\ |"); menu = menu->next;
            menu->next = createMenuItem("                             O                \\|"); menu = menu->next;
            menu->next = createMenuItem("                            /|\\                |"); menu = menu->next;

            for (i = 0; i < 4; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 9:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                             |              \\  |"); menu = menu->next;
            menu->next = createMenuItem("                             |               \\ |"); menu = menu->next;
            menu->next = createMenuItem("                             O                \\|"); menu = menu->next;
            menu->next = createMenuItem("                            /|\\                |"); menu = menu->next;
            menu->next = createMenuItem("                            /                  |"); menu = menu->next;

            for (i = 0; i < 3; i++) {
                menu->next = createMenuItem("                                               |"); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;
        case 10:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                             |              \\  |"); menu = menu->next;
            menu->next = createMenuItem("                             |               \\ |"); menu = menu->next;
            menu->next = createMenuItem("                             O                \\|"); menu = menu->next;
            menu->next = createMenuItem("                            /|\\                |"); menu = menu->next;
            menu->next = createMenuItem("                            / \\                |"); menu = menu->next;
            menu->next = createMenuItem("                                               |"); menu = menu->next;
            menu->next = createMenuItem("                    BETTER LUCK NEXT TIME :(   |"); menu = menu->next;
            menu->next = createMenuItem("                                               |"); menu = menu->next;
            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" ");
            break;

        default:

            for (i = 0; i < 9; i++) {
                menu->next = createMenuItem(" "); menu = menu->next;
            }

            menu->next = createMenuItem("     __________________________________________________"); menu = menu->next;
            menu->next = createMenuItem(" ");
    }
    return first;
}
