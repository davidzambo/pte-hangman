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
        isInWord = 0,
        isLetterInAlreadyGuessedLetters = 0;
    char thisGuess;

    MENUITEM *menu = renderHang(countOfFails);
    MENUITEM *first = menu;
    MENUITEM *last = menu;

    while (last->next != NULL) {
        last = last->next;
    }
    last->next = createMenuItem(word);

    /*
     * If we have already guessed letters, let show it to the user
     */
    if (countOfLetterGuesses > 0) {
        last = last->next;
        last->next = createMenuItem(" ");
        last = last->next;
        last->next = createMenuItem("Already guessed letters: ");
        last = last->next;
        char letterList[40];
        for (i = 0; i < countOfLetterGuesses; i++) {
            letterList[2*i] = letterGuesses[i];
            /*
             * A list last element doesn't followed by ','
             */
            if (i < countOfLetterGuesses - 1) {
                letterList[2*i + 1] = ',';
            }
        }
        letterList[2*i-1] = '\0';
        last->next = createMenuItem(letterList);
    }

    renderView(first);
//    getchar();
//    thisGuess = (char) getchar();
    scanf(" %1s[^\n]", &thisGuess);
//    getchar();

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

    MENUITEM *this = renderHang(0);
    renderView(this);
    this = renderHang(1);
    renderView(this);
    this = renderHang(2);
    renderView(this);
    this = renderHang(3);
    renderView(this);
    this = renderHang(4);
    renderView(this);
    this = renderHang(5);
    renderView(this);
    this = renderHang(6);
    renderView(this);
    this = renderHang(7);
    renderView(this);
    this = renderHang(8);
    renderView(this);
    this = renderHang(9);
    renderView(this);
    this = renderHang(10);

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