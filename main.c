#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/headers/initializer.h"
#include "lib/headers/renderview.h"
#include "lib/structs/word.h"
#include "lib/structs/menuitem.h"
#include "lib/headers/categories.h"
#include "lib/headers/createmenuitem.h"
#include "lib/headers/selectcategory.h"
#include "lib/headers/renderHang.h"
#include "lib/headers/playagame.h"
#include "lib/headers/showcredits.h"
#include "lib/headers/storeanewword.h"

MENUITEM *renderInstructions(int step) {

    char pagination[VIEW_WIDTH] = "                                                     ";
    char stepChar[2];
    stepChar[0] = (char) (step + 49);
    stepChar[1] = '\0';
    strcat(pagination, stepChar);
    strcat(pagination, "/5");

    MENUITEM *menu;
    menu = createMenuItem("======================= INSTRUCTIONS ======================");
    MENUITEM *first = menu;

    switch (step) {
        case 1:
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("If you guessed a letter which is in the word you play with,"); menu = menu->next;
            menu->next = createMenuItem("you will see the occurence(s) of it on the next round,"); menu = menu->next;
            menu->next = createMenuItem("otherwise a gallow will start to be built."); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("                          _ i _ _                     "); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("To help you to win, you will see all your previous guesses"); menu = menu->next;
            menu->next = createMenuItem("on the bottom of the screen. In case you hit a letter"); menu = menu->next;
            menu->next = createMenuItem("previously guessed, the computer will not count as fail."); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("Previous guesses: f,o,x,i                     "); menu = menu->next;
            break;
        case 2:
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("When you are guessing, keep in mind, that words can contain"); menu = menu->next;
            menu->next = createMenuItem("only letters, \"'\" and \"-\" characters! In case you enter"); menu = menu->next;
            menu->next = createMenuItem("anything else, the computer will send you a warning message,"); menu = menu->next;
            menu->next = createMenuItem("but will not count as a failed guess!"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("Another help for you is that you do not need to take care of"); menu = menu->next;
            menu->next = createMenuItem("capital letters! By guessing a letter, the game will show"); menu = menu->next;
            menu->next = createMenuItem("you both uppercase and lowercase matches."); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("                 S _ n   _ r _ n c _ s c o                     "); menu = menu->next;
            break;
        case 3:
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("As time goes on and you will become a pro, you could add"); menu = menu->next;
            menu->next = createMenuItem("new word to the game by selecting the \"Save a new word\""); menu = menu->next;
            menu->next = createMenuItem("action from the main menu."); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("You should select a category you would like to extend, "); menu = menu->next;
            menu->next = createMenuItem("then you should just enter the new word!"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("The new words must be longer then 4 and shorter then 32"); menu = menu->next;
            menu->next = createMenuItem("characters, and it can contains the letters which are"); menu = menu->next;
            menu->next = createMenuItem("allowed during gameplay plus \" \"!"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("e.g.: New Orleans"); menu = menu->next;
            break;
        case 4:
            menu->next = createMenuItem("                             ___________________"); menu = menu->next;
            menu->next = createMenuItem("                             |              \\  |"); menu = menu->next;
            menu->next = createMenuItem("                             |               \\ |"); menu = menu->next;
            menu->next = createMenuItem("                             O                \\|"); menu = menu->next;
            menu->next = createMenuItem("                            /|\\                |"); menu = menu->next;
            menu->next = createMenuItem("                            / \\                |"); menu = menu->next;
            menu->next = createMenuItem("                                               |"); menu = menu->next;
            menu->next = createMenuItem("     __________________________________________|______"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("I hope you will have fun!"); menu = menu->next;
            menu->next = createMenuItem("For further questions and details feel free to contact"); menu = menu->next;
            menu->next = createMenuItem("me on any channels can be found on \"Show credits\""); menu = menu->next;
            menu->next = createMenuItem("section!"); menu = menu->next;
            break;
        default:
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("The task is simple: you should find out a word!"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("At the first step, you should choose a category. The"); menu = menu->next;
            menu->next = createMenuItem("available categories are: animal, car, city, country and"); menu = menu->next;
            menu->next = createMenuItem("profession."); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("When you choose a category, the computer will randomly"); menu = menu->next;
            menu->next = createMenuItem("select a word from the previously given text file, and"); menu = menu->next;
            menu->next = createMenuItem("the guessing begins."); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("                          _ _ _ _                     "); menu = menu->next;
    }
    menu->next = createMenuItem(" "); menu = menu->next;
    menu->next = createMenuItem("________________________________________________________"); menu = menu->next;
    menu->next = createMenuItem("Press <n> to continue, <b> to go back to previous screen"); menu = menu->next;
    menu->next = createMenuItem("or <q> to go back to main menu."); menu = menu->next;
    menu->next = createMenuItem("Remember to press <ENTER> !"); menu = menu->next;
    menu->next = createMenuItem(pagination);
    return first;
}

/**
 * A controller to handle which screen to render
 *
 * @return
 */
int showInstructions() {
    int step = 0;
    char action = '\0';
    while(1) {
        renderView(renderInstructions(step));

        action = (char) getchar();
        while(getchar() != '\n');

        switch (action) {
            case 'b':
            case 'B':
                if (step > 0) {
                    step --;
                } else {
                    step = 4;
                }
                break;
            case 'n':
            case 'N':
                step++;
                if (step == 5) {
                    step = 0;
                }
                break;
            case 'q':
            case 'Q':
                return 0;
            default:
                continue;
        }
    }
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