#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/headers/initializer.h"
#include "lib/headers/renderview.h"
#include "lib/stucts/word.h"
#include "lib/stucts/menuitem.h"
#include "lib/headers/categories.h"
#include "lib/headers/createmenuitem.h"
#include "lib/headers/selectcategory.h"
#include "lib/headers/renderHang.h"
#include "lib/headers/playagame.h"


int main(int argCounter, char** args)
{
    int i = 0;
    unsigned int length = 0, lengthAfterInitialization = 0;
    FILE *db;
    char action = '\0', category = '\0', inputBuffer = '\0';
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

    while(fgets(tmp, 1000, db)) {
        if (tmp[0] == '#' || tmp[0] == '\n') {
            continue;
        }
        length++;
    }

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

    lengthAfterInitialization = initializer(db, wordList);

    if (length < lengthAfterInitialization) {
        printf("\nError!\nSomething went wrong during initialization!");
        printf("\nPlease check the database file!");
    }

    /*
     * There were corrupted data in the database file,
     * so we should free the previously allocated memory size
     */
    if (lengthAfterInitialization < length) {
        for (i = length; i == lengthAfterInitialization; i--) {
            free(wordList[i - 1]);
        }
        wordList = (WORD**) realloc(wordList, lengthAfterInitialization * sizeof(WORD*));
    }

    /*
     * Generate the base manu for the game
     */
    MENUITEM *menu;
    menu = createMenuItem("========================= HANGMAN =========================");
    MENUITEM *first = menu;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("1. Play");
    menu = menu->next;
    menu->next = createMenuItem("2. Save a new word ");
    menu = menu->next;
    menu->next = createMenuItem("3. View credits ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("<q> Exit ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("Select an action and press <ENTER> !");

    while(1) {
        if (lengthAfterInitialization < length) {
            printf("\nPress <ENTER> to continue!");
            while((inputBuffer = getchar() != '\n'));
            length = lengthAfterInitialization;
        }
        renderView(first);

        action = (char) getchar();
        /*
         * read all entered characters and do nothing with them
         * Only the first entered character is valueable.
         */
        while((inputBuffer = getchar() != '\n'));

        switch (action) {
            case '1':
                category = selectCategory();
                if (category == 'b') {
                    continue;
                }
                else {
                    char *wordToPlayWith = selectAWordFromCategory(category, wordList, length);
                    char *letterGuesses = (char *) malloc(sizeof(char));;
                    letterGuesses[0] = '\0';

                    playAGame(wordToPlayWith, letterGuesses, 0);
                }
                break;
            case 'q':
                printf("\nExit...\n");
                return 0;
            default:
                printf("\nSomething went wrong...\n");
        }
    }


    printf("\nWait for exit: ");
    scanf("%d", &i);
    return 0;
}