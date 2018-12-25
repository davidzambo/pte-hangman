//
// Created by zdavid on 23/12/18.
//

#include "headers/selectcategory.h"

/**
 * Prepare the category selection menu list
 *
 * @return
 */
char selectCategory()
{
    int i = 0;
    char categoryName[40], action = '\0';

    system("clear");

    MENUITEM *menu = createMenuItem("==================== SELECT A CATEGORY ====================");

    MENUITEM *first = menu;
    menu->next = createMenuItem(" ");

    for (i = 0; i < COUNT_OF_CATEGORIES; i++) {

        categoryName[0] = (char)(i + 49);
        categoryName[1] = '\0';

        strcat(categoryName, ". ");
        strcat(categoryName, categories[i]);
        menu = menu->next;
        menu->next = createMenuItem(categoryName);
    }
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("<ESC> STEP BACK TO MAIN MENU");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("SELECT AN ACTION AND PRESS <ENTER>!");

    while (!((int)action == 10 || (action >= '1' && action <= (char)(COUNT_OF_CATEGORIES + 48)))) {
        renderView(first);

        getchar();
        action = getchar();
    }

    return action;
}

/**
 * Select a word from given category
 *
 * @param category
 * @param words
 * @param length
 * @return
 */
char *selectAWordFromCategory(char category, WORD **words, int length) {
    int i = 0, counter = 0;
    time_t t;
    WORD **categoryWords = (WORD**) malloc(sizeof(WORD*));

    for (i = 0; i < length; i++) {
        /*
            Search for the matching categories in the wordList
            Store them in a pointer array and determine the number of
            available options.
        */
        //printf("\nDATA %s | %s", words[i]->category, words[i]->content);
        if (strcmp((char *) categories[category - 49], (char *) words[i]->category) == 0) {
            counter++;
            categoryWords = (WORD **) realloc(categoryWords, counter * sizeof(WORD*));
            categoryWords[counter - 1] = words[i];
        }
    }

    srand((unsigned int)time(0));
    int num = rand() % counter;
    return categoryWords[num]->content;
}
