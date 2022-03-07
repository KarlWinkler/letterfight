// menu.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "structs.c"

#define ITEMS_LEN '}' - '0'

struct menu_item *items;

void build_items(){

    for(int i = 0; i < ITEMS_LEN; i++){
        items[i].m = letter_map[i];
        items[i].title = asprintf(" %c \t", letter_map[i].name); 
        items[i].title_select = asprintf("\033[44m %c \t\033[47m", letter_map[i].name);
    }

}

void display_menu(int str, int select){

    build_items();

    char *option_a = " a \t";
    char *option_b = " b \t";
    char *option_c = " c \t";

    char *option_a_selected = "\033[44m a \t\033[47m";
    char *option_b_selected = "\033[44m b \t\033[47m";
    char *option_c_selected = "\033[44m c \t\033[47m";

    /* 
    string formatting resources to explain this mess
    - https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a 
    - https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#cursor-navigation
    - https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 
    */

    // also this thing makes the entire line have bold 'black' text on a white background // 
    // printf("\r\033[1m\033[47m\033[30m%c\033[K\033[0m", str);

    switch(select){
        case 0:
            printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b, option_c);

            break;
        case 1:
            printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a_selected, option_b, option_c);
            break;
        case 2:
            printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b_selected, option_c);
            break;
        case 3:
            printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b, option_c_selected);
            break;
        default:
            printf("\r\033[47m\033[30m%d\033[K\033[0m", str);
    }

    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a_selected, option_b, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b_selected, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b, option_c_selected);

}