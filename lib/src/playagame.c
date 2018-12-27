//
// Created by zdavid on 26/12/18.
//

#include "../headers/playagame.h"

int playAGame(char *category, char *word, char *letterGuesses, unsigned int countOfFails)
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

    MENUITEM *menu = renderHang(category, countOfFails);
    MENUITEM *first = menu;
    MENUITEM *last = menu;

    while (last->next != NULL) {
        last = last->next;
    }
    // only for testing:
    /*
    last->next = createMenuItem(word);
    last = last->next;
    last->next = createMenuItem(" ");
    last = last->next;
    */


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

        /*
         * If the user failed, show the full word
         */
        if (isInWord == 1 || countOfFails == 10) {
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
        if (countOfFails == 10) {
            last->next = createMenuItem("              Press <ENTER> to play again!");
        } else if (isWordFoundOut == 1) {
            last->next = createMenuItem("                Congratulations! You win!"); last = last->next;
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
        while(getchar() != '\n');
        return 0;
    } else {
        /*
         * Get the actual guess in this round
         */
        thisGuess = (char) getchar();
        /*
         * read all entered characters and do nothing with them
         * Only the first entered character is valueable.
         */
        while(getchar() != '\n');

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

    }

    playAGame(category, word, letterGuesses, countOfFails);
}
