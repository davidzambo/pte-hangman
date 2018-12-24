//
// Created by zdavid on 23/12/18.
//
/*
	Initializer function
		- Checks and validate the database file
		- Reads the categories
		- Reads the words
*/

#include "headers/initializer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void createRecord(char *lineBuffer, struct Word *word)
{
    char buffer[255];
    int i = 0, c = 0;

    while (1) {
//        printf("%c", *(lineBuffer + i));
        buffer[c] = *(lineBuffer + i);

        i++;
        c++;

        /*
            From char to char checks the lineBuffer string.
            If it finds a '\t', that means we found the category string,
            so copy it to the given words category field.
            If we finds a '\n', that will show us the end of the given content.
        */
        if (*(lineBuffer + i) == '\t' || *(lineBuffer + i) == '\n') {
            buffer[c] = '\0';
            //printf("\n !!! GOT FIRST ONE: %s \n", buffer);
            if (i == c) {
                strcpy(word->category, buffer);
                c = 0;
                i++;
                buffer[0] = '\0';
            } else {
                strcpy(word->content, buffer);
//                printf("\nword: %s %s", word->category, word->content);
                break;
            }
        }
    }
}

/**
 * Initialize the game.
 * Reads the given db file from line to line,
 * then creates records into the memory
 *
 * @param db
 * @param wordList
 */
void initializer(FILE *db, WORD **wordList) {
    char lineBuffer[255];
    unsigned int counter = 0;

    while (fgets(lineBuffer, 255, db)) {
        createRecord(lineBuffer, wordList[counter]);
        counter++;
    }

    fclose(db);

}