# HANGMAN
### The classic word game implemented in C
###### A homework for C university course

This game will accept only one parameter, the "word-list" text file,
which will be the database of the words it will random choose during the game

You can select a category, and the computer will give choose a word from that category

If you find out the word, you will win, otherwise you will loose and you will be hanged

You can create a new category and add new words.

###### Usage:
After you have compiled the code, you should enter to terminal:

```
./hangman -f words.txt
```
or on windows: 
```
hangman.exe -f words.txt
```

where *hangman.exe* is the binary you compiled, and the words.txt is the text file
which contains the data used in the program.




###### Instruction:

The task is simple: you should find out a word!

At the first step, you should choose a category. The
available categories are:
+ animal
+ car
+ city
+ country
+ profession

When you choose a category, the computer will randomly
select a word from the previously given text file, and
the guessing begins.

If you guessed a letter which is in the word you play with,
you will see the occurence(s) of it on the next round,
otherwise a gallow will start to be built.

```
                          _ i _ _
```

To help you to win, you will see all your previous guesses
on the bottom of the screen. In case you hit a letter
previously guessed, the computer will not count as fail.

```
Previous guesses: p,t,e,m,i,k
```

When you are guessing, keep in mind, that words can contain
only letters! In case you enter anything else, the computer
will send you a warning message, but will not count as a
failed guess!

Another help for you is that you do not need to take care of
capital letters! By guessing a letter, the game will show
you both uppercase and lowercase matches.

```
                 S _ n   _ r _ n c _ s c o
```

As time goes on and you will become a pro, you could add
new words to the game by selecting the **"Save a new word"**
action from the main menu.

You should select a category you would like to extend,
then you should just enter the new word!

*The new words must be longer then 4 and shorter then 32
characters, and it can contains the letters which are
allowed during gameplay plus "'", "-" and " "!*

e.g.: New Orleans

The file that contains the words have a strict
hierarchy. Every new record should start in a new line,
the category and the exact word should separated
with a **<TAB>** character! e.g.:

```
animal	lion
```

When the program starts, it reads the file into the
memory. If something is wrong with given line, it will
return a detailed message about the errors.

```
                              ___________________
                             |              \  |
                             |               \ |
                             O                \|
                            /|\                |
                            / \                |
                                               |
     __________________________________________|______
```

I hope you will have fun!
For further questions and details feel free to contact
me on any channels can be found on **"Show credits"**
section!


###### Note:

You can comment out any records from the *words.txt* file
(or any text file you use to play with) by starting the line
with a '#' mark.

###### Note2:

If the look of the program falls apart, try to set the encoding 
of you console to IBM850 and/or set the minimum width to 80 chars
and minimum height to 24 chars!