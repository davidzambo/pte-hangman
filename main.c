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
#include "lib/headers/showcredits.h"

int storeANewWord(char *category, char *newWord, char *filename)
{
    char title[VIEW_WIDTH] = "",
        message[VIEW_WIDTH] = "";
    unsigned int isValidWord = 1,
        i = 0,
        lengthOfNewWord = 0;

    FILE *db;

    db = fopen(filename, "a+");

    /**
     * Check file permission
     */
    if (db == NULL) {

        strcpy(message, "Error! File is not found or don\'t have permission to write!");

    }

    do {
        strcpy(title, "Add new word to \"");
        MENUITEM *menu;
        menu = createMenuItem("====================== ADD NEW WORD =======================");
        MENUITEM *first = menu;
        menu->next = createMenuItem(" "); menu = menu->next;

        if (db != NULL) {

            strcat(title, category);
            strcat(title, "\" category.");
            menu->next = createMenuItem(title); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("Enter the new word, then press <ENTER>"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("(Note: only letters, \"'\", \" \" and \"-\" characters are"); menu = menu->next;
            menu->next = createMenuItem("accepted, and the word should have at least 4 characters,"); menu = menu->next;
            menu->next = createMenuItem("but the word cannot be longer than 32 characters.)"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("If you would like to go back, press <b> and press <ENTER> !"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;

        }

        menu->next = createMenuItem(message);

        renderView(first);

        fgets(newWord, 100, stdin);

        if (db == NULL) {
            return 2;
        }

        lengthOfNewWord = (unsigned int) strlen(newWord);
        /*
         * Remove \n from the end of the newWord
         */

        newWord[lengthOfNewWord - 1] = '\0';

        /*
         * Set the isValidWord flag to true, to let the for loop
         * decide if it is a valid word
         */
        if (isValidWord == 0) isValidWord = 1;

        if (lengthOfNewWord == 1 && (newWord[0] == 'b' || newWord[0] == 'B')) {
            fclose(db);
            return 0;
        }

        if (lengthOfNewWord > 32) {

            isValidWord = 0;
            strcpy(message, "Error! The given word is longer than 32 characters!");

        } else if (lengthOfNewWord < 4) {

            isValidWord = 0;
            strcpy(message, "Error! The given word should have at least 4 characters!");

        }
        else {
            for (i = 0; i < lengthOfNewWord - 1; i++) {
                /*
                 * It's a tricky condition, let me explain it:
                 * If a char is a lowercase letter OR
                 *  a char is an uppercase letter OR
                 *  a char is ' ' OR
                 *  a char is '-' OR
                 *  a char is "'"
                 *  then the given character is a valid character.
                 *
                 *  So if I negate the statement (!), I can trigger
                 *  the invalid case.
                 */
                if (!((newWord[i] >= 'a' && newWord[i] <= 'z') ||
                        (newWord[i] >= 'A' && newWord[i] <= 'Z') ||
                        (newWord[i] == ' ') ||
                        (newWord[i] == '-') ||
                        (newWord[i] == '\'')
                        )){
                    isValidWord = 0;
                    strcpy(message, "Error! The given word contains illegal characters!");

                }

            }
        }

    } while (isValidWord == 0);

    /*
     * If everything is fine, write it to the file
     */
    fprintf(db,"\n%s\t%s",category, newWord);
    fclose(db);
    return 0;
}

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

        switch (action) {
            case '2':
                category = selectCategory();
                if (category == 'b') {
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
                    }
                }
                break;
            case '4':
                showCredits();
                break;
            case 'q':
                printf("\nExit...\n");
                return 0;
            default:
                continue;
        }
    }


    printf("\nWait for exit: ");
    scanf("%d", &i);
    return 0;
}