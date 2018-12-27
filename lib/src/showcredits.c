//
// Created by zdavid on 26/12/18.
//

#include "../headers/showcredits.h"
#include "../headers/createmenuitem.h"
#include "../headers/renderview.h"
#include <stdio.h>

void showCredits()
{
    MENUITEM *menu;
    menu = createMenuItem("========================= CREDITS =========================");
    MENUITEM *first = menu;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("Created at: 26/12/2018");menu = menu->next;
    menu->next = createMenuItem("Created by: David Zambo");menu = menu->next;
    menu->next = createMenuItem("Contact: dave@dcmf.io");menu = menu->next;
    menu->next = createMenuItem("Site: https://dcmf.io");menu = menu->next;
    menu->next = createMenuItem("GitHub: https://github.com/davidzambo");menu = menu->next;
    menu->next = createMenuItem("Repo: https://github.com/davidzambo/pte-hangman");menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("Press <ENTER> to go back to main menu!");

    renderView(first);
    while(getchar() != '\n');
}