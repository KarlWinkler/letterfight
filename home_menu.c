// home_menu.c
//
// displays the home menu
//
// Author: Karl Winkler
// Date Created: Mar. 10, 2022
// Last Change: Mar. 10, 2022 (git is correct if different)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"

void display_home_menu(){
    CLEAR;
    system("cat welcome_file");
}