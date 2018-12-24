cmake_minimum_required(VERSION 3.13)
project(hangman C)

set(CMAKE_C_STANDARD 99)

add_executable(hangman main.c lib/categories.c lib/headers/categories.h lib/createmenuitem.c lib/headers/createmenuitem.h lib/headers/menuitem.h lib/headers/word.h lib/initializer.c lib/headers/initializer.h lib/renderview.c lib/headers/renderview.h lib/selectcategory.c lib/headers/selectcategory.h lib/renderHang.c lib/headers/renderHang.h)