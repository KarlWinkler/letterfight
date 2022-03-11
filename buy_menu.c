// buy_menu.c
//
// displays the buy menu based on the current state
//
// Author: Karl Winkler
// Date Created: Mar. 6, 2022
// Last Change: Mar. 10, 2022 (git is correct if different)

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "team.c"
#include "macros.h"

struct menu_item items[ITEMS_LEN];
// struct menu_item transact[MAX_MEMBERS];
// int trans_size = 0;


void build_items(struct member *letter_map){

    for(int i = 0; i < ITEMS_LEN; i++){
        items[i].m = letter_map[i];
        char temp[10000];

        char n[2];

        n[0] = letter_map[i].name;
        n[1] = '\0';

        // normal
        
        strcat(temp, " ");
        strcat(temp, n);
        strcat(temp, " \t");

        strcpy(items[i].title, temp);

        bzero(temp, sizeof(temp));

        // select

        strcat(temp, "\033[44m ");
        strcat(temp, n);
        strcat(temp, " \t\033[47m");

        strcpy(items[i].title_select, temp);
        
        bzero(temp, sizeof(temp));

        //bought

        strcat(temp, "\033[40m\033[37m ");
        strcat(temp, n);
        strcat(temp, " \t\033[47m\033[30m");

        strcpy(items[i].disabled, temp);
        
        bzero(temp, sizeof(temp));

        // bought selected

        strcat(temp, "\033[40m\033[31m ");
        strcat(temp, n);
        strcat(temp, " \t\033[47m\033[30m");

        strcpy(items[i].disabled_selected, temp);
        
        bzero(temp, sizeof(temp));

        items[i].bought = 0;
    }

}

void display_buy_menu(int str, int select, int team_select, struct member *letter_map){

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

        if(items[i].bought == 1 && i == select){
            strcat(out, items[i].disabled_selected);
        }
        else if(items[i].bought == 1){
            strcat(out, items[i].disabled);
        }
        else if(i == select){
            strcat(out, items[i].title_select);
        }
        else{
            strcat(out, items[i].title);
        }
    }

   char team_out[100];
    for(int i = 0; i < MAX_MEMBERS; i++){
        
        if(i < my_team.num_members){
            char n[2];

            n[0] = my_team.members[i].name;
            n[1] = '\0';

            if(i == team_select){
                strcat(team_out, "\033[30m\033[44m ");
            }
            else{
                strcat(team_out, "\033[30m\033[47m ");
            }
            strcat(team_out, n);
            strcat(team_out, " \033[0m ");
        }
        else{
            if(i == team_select){
                strcat(team_out, "\033[30m\033[44m''\033[0m ");
            }
            else{
                strcat(team_out, "'' ");
            }
        }
    }   

    calc_team_power();
    
    strcat(out, "\033[K\033[0m");
    
    CLEAR;
    printf("%s", out);
    printf("\ncost: %d\n\nattack: %d\ndeffence: %d\ndexterity: %d\ncrit chance: %d\n\nMy Team:\n%s\n", items[select].m.cost, items[select].m.atk, items[select].m.def, items[select].m.dex, items[select].m.crit, team_out);
    printf("Cost: %d\n", my_team.total_cost);
    printf("Offence: %f\nDefence: %f\nDexterity: %f\nCritical Strike: %f\n", my_team.offence, my_team.defence, my_team.dexterity, my_team.crit);

    printf("Team_select: %d\n", team_select);

    
    bzero(out, sizeof(out));
    bzero(team_out, sizeof(team_out));


    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a_selected, option_b, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b_selected, option_c);
    // printf("\r\033[47m\033[30m%s%s%s\033[K\033[0m", option_a, option_b, option_c_selected);

}