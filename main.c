#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/headers/initializer.h"
#include "lib/headers/renderview.h"
#include "lib/headers/word.h"
#include "lib/headers/menuitem.h"
#include "lib/headers/categories.h"
#include "lib/headers/createmenuitem.h"
#include "lib/headers/selectcategory.h"
#include "lib/headers/renderHang.h"


int playAGame(char *word, char *letterTips, unsigned int countOfFails)
{
    int lengthOfWord = (int) strlen(word), i = 0, isInWord = 0;
    char thisTip;

    MENUITEM *menu = renderHang(countOfFails);
    MENUITEM *first = menu;
    MENUITEM *last = menu;

    while (last->next != NULL) {
        last = last->next;
    }
    last->next = createMenuItem(word);

    renderView(first);
    thisTip = (char) getchar();
    getchar();

    for (i = 0; i < lengthOfWord; i++) {
        printf("ez :  %c ", word[i]);
        if (thisTip == word[i]) {
            int letterTipsLength = (int) strlen(letterTips);
            letterTips = (char *) realloc(letterTips, (letterTipsLength + 1) * sizeof(char));
            letterTips[letterTipsLength] = thisTip;
            isInWord = 1;
            break;
        }
    }

    if (isInWord == 0) {
        countOfFails++;
        printf("\n Nope!!!");

    } else {
        printf("\n In WORD!!!");
    }
    printf("\ntips: %s", letterTips);
    getchar();
    getchar();

    playAGame(word, letterTips, countOfFails);

    if (countOfFails == 10) {
        return 0;
    }
}

int main(int argCounter, char** args)
{
    int i = 0;
    unsigned int length = 0;
    FILE *db;
    char action = '\0', category = '\0';
    struct Word **wordList = NULL;
    char tmp[1000];

    if (argCounter < 3) {
        printf("Error!\nWord list not found!\n\nusage: hangman.exe -f words.txt");
        return 1;
    }

    if (strcmp(args[1],"-f") != 0) {
        printf("Error!\nWord list not found!\n\nusage: hangman.exe -f words.txt\n");
        return 1;
    }

    /*
     * Open file to find out the number of records,
     * to let it allocate the proper amount of memory for the
     * word list
     */
    db = fopen(args[2], "r");

    if (db == NULL) {
        printf("\nError!\nCannot read file!\n");
        return 1;
    }

    while(fgets(tmp, 1000, db)) length++;

    if (length == 0) {
        printf("\nError!\nCannot find any record in file!\n");
        return 1;
    }

    /*
     * As we know the count of the possible record, allocate
     * them enough memory
     */
    wordList = (WORD**) realloc(wordList, length * sizeof(WORD*));
    for (i = 0; i < length; i++) {
        wordList[i] = malloc(sizeof(WORD));
    }

    // Jump back to the beginning of the file
    rewind(db);

    initializer(db, wordList);

    /*
     * Generate the base manu for the game
     */
    MENUITEM *menu;
    menu = createMenuItem("=============== HANGMAN ===============");
    MENUITEM *first = menu;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("1. PLAY");
    menu = menu->next;
    menu->next = createMenuItem("2. SAVE A NEW WORD ");
    menu = menu->next;
    menu->next = createMenuItem("3. VIEW CREDITS ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("<ESC> EXIT ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("SELECT AN ACTION AND PRESS <ENTER>!");

    MENUITEM *this = first;

    while(1) {
        renderView(this);

        action = (char) getchar();

        if ((int) action == 10) {
            exit(0);
        }


        if (action == '1') {
            category = selectCategory();
            if ((int)category == 10) { // ESC
                continue;
            }
            else {
                char *wordToPlayWith = selectAWordFromCategory(category, wordList, length);
                char *letterTips = '\t';
                playAGame(wordToPlayWith, letterTips, 0);
                getchar();
                getchar();
            }
        }
    }


    printf("\nWait for exit: ");
    scanf("%d", &i);
    return 0;
}