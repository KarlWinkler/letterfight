// menu.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "structs.c"

#define ITEMS_LEN '}' - '0'
#define CLEAR printf("\033[2J\033[H")

struct menu_item items[ITEMS_LEN];

void build_items(struct member *letter_map){

    for(int i = 0; i < ITEMS_LEN; i++){
        items[i].m = letter_map[i];
        char temp[10000];
        
        strcat(temp, " ");
        strcat(temp, &letter_map[i].name);
        strcat(temp, " \t");

        strcpy(items[i].title, temp);

        bzero(temp, sizeof(temp));

        strcat(temp, "\033[44m ");
        strcat(temp, &letter_map[i].name);
        strcat(temp, " \t\033[47m");

        strcpy(items[i].title_select, temp);
        
        bzero(temp, sizeof(temp));
    }

}

void display_menu(int str, int select, struct member *letter_map){

    build_items(letter_map);

    // char *option_a = " a \t";
    // char *option_b = " b \t";
    // char *option_c = " c \t";

    // char *option_a_selected = "\033[44m a \t\033[47m";
    // char *option_b_selected = "\033[44m b \t\033[47m";
    // char *option_c_selected = "\033[44m c \t\033[47m";

    /* 
    string formatting resources to explain this mess
    - https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a 
    - https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#cursor-navigation
    - https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 
    */

    // also this thing makes the entire line have bold 'black' text on a white background // 
    // printf("\r\033[1m\033[47m\033[30m%c\033[K\033[0m", str);

    CLEAR;
    char out[10000];
    strcat(out, "\r\033[47m\033[30m");   

    for(int i = 0; i < 20; i++){
        
        if(i == select){
            strcat(out, items[i].title_select);
        }
        else{
            strcat(out, items[i].title);
        }
    }   
    
    strcat(out, "\033[K\033[0m");
    
    CLEAR;
    printf("%s", out);
    usleep(10);
    printf("\ncost: %d\n\nattack: %d\ndeffence: %d\ndexterity: %d\ncrit chance: %d\n", items[select].m.cost, items[select].m.atk, items[select].m.def, items[select].m.dex, items[select].m.crit);


    bzero(out, sizeof(out));
    

    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a_selected, option_b, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b_selected, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b, option_c_selected);

}