//
// Created by zdavid on 26/12/18.
//

#include "../headers/storeanewword.h"
#include "../headers/createmenuitem.h"
#include "../headers/renderview.h"
#include <stdio.h>
#include <string.h>

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