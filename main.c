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


int playAGame(char *word, char *letterGuesses, unsigned int countOfFails)
{
    int lengthOfWord = (int) strlen(word),
        countOfLetterGuesses = (int) strlen(letterGuesses),
        i = 0,
        j = 0,
        isInWord = 0,
        isLetterInAlreadyGuessedLetters = 0,
        isWordFoundOut = 1,
        isValidGuess = 1;
    char thisGuess;

    MENUITEM *menu = renderHang(countOfFails);
    MENUITEM *first = menu;
    MENUITEM *last = menu;

    while (last->next != NULL) {
        last = last->next;
    }
    // only for testing:
//    last->next = createMenuItem(word);
//    last = last->next;
//    last->next = createMenuItem(" ");
//    last = last->next;
    // END only for testing

    /*
     * create the word we will show to the user
     */
    char wordToShow[lengthOfWord*2];

    for (i = 0; i < lengthOfWord; i++) {
        isInWord = 0;
        /*
         * Check, that the given character has already been guessed
         * If yes, show it, else render a '_' char
         */
        for (j = 0; j < countOfLetterGuesses; j++) {
            /*
             * Check both uppercase and lowercase letters
             */
            if (word[i] == letterGuesses[j] || (word[i] + 32) == letterGuesses[j]) {
                isInWord = 1;
                break;
            }
        }

        if (isInWord == 1) {
            wordToShow[2 * i] = word[i];
        } else {
            /*
             * Take care of special characters not
             * to hide out.
             */
            switch (word[i]) {
                case ' ':
                    wordToShow[2*i] = ' ';
                    break;
                case '\'':
                    wordToShow[2*i] = '\'';
                    break;
                case '-':
                    wordToShow[2*i] = '-';
                    break;
                default:
                    wordToShow[2 * i] = '_';
                    if (isWordFoundOut == 1) {
                        isWordFoundOut = 0;
                    }
            }
        }
        /*
         * Draw a separator between characters
         */
        wordToShow[2 * i + 1] = ' ';
    }
    /*
     * Close the string
     */
    wordToShow[2 * i - 1] = '\0';
    
    /*
     * Prepare word to centrelized
     */
    char wordToShowCentralized[VIEW_WIDTH];

    /*
     * Fill up the new string with ' ' until we reach
     * the middle of the screen - the length of word
     */
    for (i = 0; i < ((VIEW_WIDTH - lengthOfWord * 2) / 2); i++) {
        wordToShowCentralized[i] = ' ';
    }
    wordToShowCentralized[i] = '\0';

    /*
     * Copy the word that we want to show to the end
     * of the space filled new word
     */
    strcat(wordToShowCentralized, wordToShow);
    last->next = createMenuItem(wordToShowCentralized);

    /*
     * If we have already guessed letters, let's show it
     * to the user
     */
    if (countOfLetterGuesses > 0) {
        last = last->next;
        last->next = createMenuItem(" ");
        last = last->next;

        /*
         * Check if the user found out the word
         */
        if (isWordFoundOut == 1) {
            last->next = createMenuItem("                Congratulations! You win!"); last = last->next;
            last->next = createMenuItem("              Press <ENTER> to play again!");
        } else if (countOfFails == 11) {
            last->next = createMenuItem("              Press <ENTER> to play again!");
        } else {
            char letterList[VIEW_WIDTH] = " ";
            strcat(letterList, "Previous guesses:  ");

            /*
             * strlen("PREVIOUS GUESSES: ") = 18
             */
            for (i = 0; i < countOfLetterGuesses; i++) {
                letterList[2*i + 19] = letterGuesses[i];
                /*
                 * A list last element doesn't followed by ','
                 */
                if (i < countOfLetterGuesses - 1) {
                    letterList[2*i + 19 + 1] = ',';
                } else {
                    letterList[2*i + 19 + 1] = '\0';
                }
            }
            letterList[2*i-1 + 19] = '\0';
            last->next = createMenuItem(letterList);
        }
    }

    renderView(first);

    if (isWordFoundOut == 1 || countOfFails == 10) {
        getchar();
        getchar();
        return 0;
    } else {
        /*
         * Get the actual guess in this round
         */
        scanf(" %1s[^\n]", &thisGuess);
    }

    /*
     * lowerize the guess
     */
    if (thisGuess >= 'A' && thisGuess <= 'Z') {
        thisGuess += 32;
    }

    if (thisGuess < 'a' || thisGuess > 'z') {
        printf("\nOnly letters are accepted!\nPlease press <ENTER> !");
        isValidGuess = 0;
        getchar();
        getchar();
    }

    if (isValidGuess == 1)
    {
        /*
     * Check, if actual guess is a char, that has been already tipped
     * before, and it was a successful tip
     */
        for (i = 0; i < countOfLetterGuesses; i++) {
            if (thisGuess == letterGuesses[i]) {
                isLetterInAlreadyGuessedLetters = 1;
                break;
            }
        }

        if (isLetterInAlreadyGuessedLetters == 0) {
            letterGuesses = (char *) realloc(letterGuesses, (countOfLetterGuesses + 2) * sizeof(char));
            letterGuesses[countOfLetterGuesses] = thisGuess;
            letterGuesses[countOfLetterGuesses + 1] = '\0';

            for (i = 0; i < lengthOfWord; i++) {
                if (thisGuess == word[i]) {
                    isInWord = 1;
                    break;
                }
            }

            if (isInWord == 0) {
                countOfFails++;
            }
        }

        if (countOfFails == 11) {
            return 0;
        }
    }

    playAGame(word, letterGuesses, countOfFails);
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
    menu->next = createMenuItem("<ESC> Exit ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem(" ");
    menu = menu->next;
    menu->next = createMenuItem("Select an action and press <ENTER> !");

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
                char *letterGuesses = (char *) malloc(sizeof(char));;
                letterGuesses[0] = '\0';

                playAGame(wordToPlayWith, letterGuesses, 0);
            }
        }
    }


    printf("\nWait for exit: ");
    scanf("%d", &i);
    return 0;
}