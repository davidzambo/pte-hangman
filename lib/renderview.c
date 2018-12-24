/*
	This function is responsibe for rendering the
	console type view.

	It Accepts a MENUITEM linked list, and draws out the
	necessary view.
*/
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 24
#include "headers/renderview.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void renderView(MENUITEM *menuItem)
{
    int i = 0, j = 0, isMenuItemPrintedInLine = 0;
    system("clear");
    for (i = 0; i < WINDOW_HEIGHT; i++) {
        isMenuItemPrintedInLine = 0;
        for (j = 0; j < WINDOW_WIDTH; j++) {

            if (i == 0) {
                if (j == 0) {
                    printf("%c", 201);
                }
                else if (j < WINDOW_WIDTH - 1) {
                    printf("%c", 205);
                }
                else {
                    printf("%c\n", 187);
                }
            }
            else if (i < WINDOW_HEIGHT - 1) {
                if (j == 0 || j == WINDOW_WIDTH - 1) {
                    printf("%c", 186);
                    if (j == WINDOW_WIDTH - 1) {
                        printf("\n");
                    }
                }
                else {
                    if (i > 5) {
                        if (j > WINDOW_WIDTH / 4 && isMenuItemPrintedInLine == 0 && menuItem != NULL) {
                            printf("%s", menuItem->title);
                            j += strlen(menuItem->title);
                            isMenuItemPrintedInLine = 1;
                            if (menuItem != NULL) {
                                menuItem = menuItem->next;
                            }
                        }
                    }
                    printf(" ");
                }
            }
            else {
                if (j == 0) {
                    printf("%c", 200);
                }
                else if (j < WINDOW_WIDTH - 1) {
                    printf("%c", 205);
                }
                else {
                    printf("%c\n", 188);
                }
            }
        }
    }
}
