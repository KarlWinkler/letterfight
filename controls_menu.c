// controls_menu.c
//
// displays the controls menu
//
// Author: Karl Winkler
// Date Created: Mar. 10, 2022
// Last Change: Mar. 10, 2022 (git is correct if different)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros"

void display_controls_menu(){
    CLEAR;
    system("cat controls_file");
}