cmake_minimum_required(VERSION 3.13)
project(hangman C)

set(CMAKE_C_STANDARD 99)

add_executable(hangman lib/src/main.c lib/src/categories.c lib/headers/categories.h lib/src/createmenuitem.c lib/headers/createmenuitem.h lib/structs/menuitem.h lib/structs/word.h lib/src/initializer.c lib/headers/initializer.h lib/src/renderview.c lib/headers/renderview.h lib/src/selectcategory.c lib/headers/selectcategory.h lib/src/renderHang.c lib/headers/renderHang.h lib/src/playagame.c lib/headers/playagame.h lib/src/showcredits.c lib/headers/showcredits.h lib/src/storeanewword.c lib/headers/storeanewword.h lib/src/showinstructions.c lib/headers/showinstructions.h)