//
// Created by zdavid on 27/12/18.
//

#include "../headers/showinstructions.h"
#include "../headers/createmenuitem.h"
#include <string.h>
#include <stdio.h>
#include "../headers/renderview.h"

MENUITEM *renderInstructions(int step) {

    char pagination[VIEW_WIDTH] = "                                                     ";
    char stepChar[2];
    stepChar[0] = (char) (step + 49);
    stepChar[1] = '\0';
    strcat(pagination, stepChar);
    strcat(pagination, "/6");

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
            menu->next = createMenuItem("Previous guesses: p,t,e,m,i,k                     "); menu = menu->next;
            break;
        case 2:
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("When you are guessing, keep in mind, that words can contain"); menu = menu->next;
            menu->next = createMenuItem("only letters! In case you enter anything else, the computer"); menu = menu->next;
            menu->next = createMenuItem("will send you a warning message, but will not count as a"); menu = menu->next;
            menu->next = createMenuItem("failed guess!"); menu = menu->next;
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
            menu->next = createMenuItem("new words to the game by selecting the \"Save a new word\""); menu = menu->next;
            menu->next = createMenuItem("action from the main menu."); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("You should select a category you would like to extend, "); menu = menu->next;
            menu->next = createMenuItem("then you should just enter the new word!"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("The new words must be longer then 4 and shorter then 32"); menu = menu->next;
            menu->next = createMenuItem("characters, and it can contains the letters which are"); menu = menu->next;
            menu->next = createMenuItem("allowed during gameplay plus \"'\", \"-\" and \" \"!"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("e.g.: New Orleans"); menu = menu->next;
            break;
        case 4:
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("The file that contains the words have a strict"); menu = menu->next;
            menu->next = createMenuItem("hierarchy. Every new record should start in a new line,"); menu = menu->next;
            menu->next = createMenuItem("the category and the exact word should separated"); menu = menu->next;
            menu->next = createMenuItem("with a <TAB> character!"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("e.g.: animal\tlion"); menu = menu->next;
            menu->next = createMenuItem(" "); menu = menu->next;
            menu->next = createMenuItem("When the program starts, it reads the file into the"); menu = menu->next;
            menu->next = createMenuItem("memory. If something is wrong with given line, it will"); menu = menu->next;
            menu->next = createMenuItem("return a detailed message about the errors."); menu = menu->next;
            break;
        case 5:
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
    menu->next = createMenuItem("_________________________________________________________"); menu = menu->next;
    menu->next = createMenuItem("Press <n> to continue, <b> to go back to previous screen"); menu = menu->next;
    menu->next = createMenuItem("or <q> to go back to main menu. Remember to press <ENTER>!"); menu = menu->next;
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
                    step = 5;
                }
                break;
            case 'n':
            case 'N':
                step++;
                if (step == 6) {
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
