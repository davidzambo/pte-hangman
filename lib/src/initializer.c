//
// Created by zdavid on 23/12/18.
//
/*
	Initializer function
		- Checks and validate the database file
		- Reads the categories
		- Reads the words
*/
#include "../headers/categories.h"
#include "../headers/initializer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * return
 * 1 st
 * 2 nd
 * 3 th
 *
 * @param num
 * @return
 */
char *numberToString(int num) {
   return (num == 1) ? "st" : ((num == 2) ? "nd" : "th");
}

 /**
  * Create a WORD type from the given string
  * read from the file
  *
  * @param lineBuffer
  * @param word
  * @return
  */
int createRecord(char *lineBuffer, struct Word *word)
{
    char buffer[255];
    int i = 0, c = 0, j = 0, isCategoryKnown = 0, hasTabInLineBuffer = 0;

    while (1) {

        buffer[c] = *(lineBuffer + i);

        i++;
        c++;

        if (hasTabInLineBuffer == 0 && lineBuffer[i] == '\t') {
            hasTabInLineBuffer = 1;
        }
        /*
            From char to char checks the lineBuffer string.
            If it finds a '\t', that means we found the category string,
            so copy it to the given words category field.
            If we finds a '\n', that will show us the end of the given content.
        */
        if (*(lineBuffer + i) == '\t' || *(lineBuffer + i) == '\n') {

            /*
             * Examine that if we reached the end of the line, we already set
             * up a category. E.g.  there was a '\t' char in the given line.
             */
            if (lineBuffer[i] == '\n' && hasTabInLineBuffer == 0) {
                return 1;
            }

            buffer[c] = '\0';

            if (i == c) {
                strcpy(word->category, buffer);

                /*
                 * Check, if the given category is in the list of
                 * the known category names;
                 */
                for (j = 0; j < COUNT_OF_CATEGORIES; j++) {
                    if (strcmp(word->category, categories[j]) == 0) {
                        isCategoryKnown = 1;
                    }
                }

                if (isCategoryKnown == 0) {
                    return 2;
                }

                c = 0;
                i++;
                buffer[0] = '\0';
            } else {
                strcpy(word->content, buffer);
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
unsigned int initializer(FILE *db, WORD **wordList) {
    char lineBuffer[255];
    unsigned int counter = 0, errorCounter = 0, skippedLineCounter = 0;

    while (fgets(lineBuffer, 255, db)) {
        /*
         * Let there be comments! :)
         */
        if (lineBuffer[0] == '#' || lineBuffer[0] == '\n') {
            skippedLineCounter++;
            continue;
        }
        /*
         * If the data is corrupted in the given file,
         * skip that record.
         */
        switch (createRecord(lineBuffer, wordList[counter])) {
            case 1:
                errorCounter++;
                printf("Warning! Corrupted data in %d%s line of the given file!\n", errorCounter + counter + skippedLineCounter, numberToString(errorCounter + counter + skippedLineCounter));
                break;
            case 2:
                errorCounter++;
                printf("Warning! Unknown category type in %d%s line of the given file!\n", errorCounter + counter + skippedLineCounter, numberToString(errorCounter + counter + skippedLineCounter));
                break;
            default:
                counter++;
        }
    }

    fclose(db);

    return counter;
}