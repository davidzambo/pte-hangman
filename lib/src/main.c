#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/initializer.h"
#include "../headers/renderview.h"
#include "../structs/word.h"
#include "../structs/menuitem.h"
#include "../headers/categories.h"
#include "../headers/createmenuitem.h"
#include "../headers/selectcategory.h"
#include "../headers/renderHang.h"
#include "../headers/playagame.h"
#include "../headers/showcredits.h"
#include "../headers/storeanewword.h"
#include "../headers/showinstructions.h"

int main(int argCounter, char** args)
{
    int i = 0;
    unsigned int length = 0, lengthAfterInitialization = 0;
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
     * Generate the base menu for the game
     */
    MENUITEM *menu;
    menu = createMenuItem("========================= HANGMAN =========================");
    MENUITEM *first = menu;
    menu->next = createMenuItem(" "); menu = menu->next;
    menu->next = createMenuItem("1. Show instructions"); menu = menu->next;
    menu->next = createMenuItem("2. Play"); menu = menu->next;
    menu->next = createMenuItem("3. Save a new word "); menu = menu->next;
    menu->next = createMenuItem("4. View credits "); menu = menu->next;
    menu->next = createMenuItem(" "); menu = menu->next;
    menu->next = createMenuItem("<q> Exit "); menu = menu->next;
    menu->next = createMenuItem(" "); menu = menu->next;
    menu->next = createMenuItem(" "); menu = menu->next;
    menu->next = createMenuItem("Select an action and press <ENTER> !");

    while(1) {
        switch (action) {
            case '1':
                if (showInstructions() == 0) {
                    action = '\0';
                };
                break;
            case '2':
                category = selectCategory();
                if (category == 'b') {
                    action = '\0';
                    continue;
                }
                else {
                    char *wordToPlayWith = selectAWordFromCategory(category, wordList, length);
                    char *letterGuesses = (char *) malloc(sizeof(char));;
                    letterGuesses[0] = '\0';
                    char categoryName[33];
                    strcpy(categoryName, categories[(int) category - 49]);

                    playAGame(categoryName, wordToPlayWith, letterGuesses, 0);
                }
                break;
            case '3':
                category = selectCategory();
                if (category == 'b') {
                    action = '\0';
                    continue;
                }
                else {
                    int result = 0;
                    char newWord[33];
                    char categoryName[33];
                    strcpy(categoryName, categories[(int) category - 49]);
                    /*
                     * As the selectCategory will return a char number,
                     * we should subtract 49 from its int value to get the
                     * integer value of it, then get the nth element of the
                     * categories array
                     */
                    result = storeANewWord(categoryName, newWord, args[2]);

                    if (result == 0) {
                        length++;
                        lengthAfterInitialization++;
                        wordList = (WORD**) realloc(wordList, length * sizeof(WORD*));
                        wordList[length - 1] = malloc(sizeof(WORD));
                        strcpy(wordList[length - 1]->category, categoryName);
                        strcpy(wordList[length - 1]->content, newWord);
                        showSuccessFeedback(wordList[length - 1]);
                    }
                }
                break;
            case '4':
                showCredits();
                action = '\0';
                break;
            case 'q':
                printf("\nExit...\n");
                return 0;
            default:
                if (lengthAfterInitialization < length) {
                    printf("\nPress <ENTER> to continue!");
                    while(getchar() != '\n');
                    length = lengthAfterInitialization;
                }
                renderView(first);

                action = (char) getchar();
                /*
                 * read all entered characters and do nothing with them
                 * Only the first entered character is valueable.
                 */
                while(getchar() != '\n');
        }
    }
}