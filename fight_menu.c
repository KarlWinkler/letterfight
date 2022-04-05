// fight_menu.c
//
// displays the controls menu
//
// Author: Karl Winkler
// Date Created: Mar. 10, 2022
// Last Change: Mar. 10, 2022 (git is correct if different)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "structs.h"
#include "random.h"
#include "team.c"


void make_attack(struct team *my_team, struct team *enemy_team, int my_sel, int enemy_sel){

}


// my_team is the current players team
// enemy is their opponent

//> Title: display fight menu
// Args: enemy_select, the selected enemy in the menu
// Args: team_select, team member selected in the friendly team
// Args: my_team, friendly team struct
// Args: enemy_team, opponent team struct
// Description: displays the fight menu to the command line
//<

void display_fight_menu(int enemy_select, int  team_select, struct team my_team, struct team enemy_team){
    CLEAR;

    // printf("%d\n", enemy_len);
    char enemy_out[1024];
    bzero(enemy_out, sizeof(enemy_out));

    for(int i = 0; i < enemy_team.num_members; i++){
        char n[4];
        n[0] = enemy_team.members[i].me.name;
        n[1] = '\0';
        // strcat(enemy_out, n);
        if(i == enemy_select){
            strcat(enemy_out, "\033[30m\033[41m ");
        }
        else{
            strcat(enemy_out, "\033[30m\033[47m ");
        }
        strcat(enemy_out, n);
        strcat(enemy_out, " \033[0m ");
    }

    char team_out[100];
    bzero(team_out, sizeof(team_out));

    for(int i = 0; i < my_team.num_members; i++){
        
        char n[2];

        n[0] = my_team.members[i].me.name;
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
    printf("%s\n", enemy_out);
    printf("cost: %d\n\nhealth: %d\nattack: %d\ndeffence: %d\ndexterity: %d\ncrit chance: %d\n\n", enemy_team.members[enemy_select].me.cost, enemy_team.members[enemy_select].cur_hp, enemy_team.members[enemy_select].me.atk, enemy_team.members[enemy_select].me.def, enemy_team.members[enemy_select].me.dex, enemy_team.members[enemy_select].me.crit);
    printf("%s\n", team_out);
    printf("cost: %d\n\nhealth: %d\nattack: %d\ndeffence: %d\ndexterity: %d\ncrit chance: %d\n", my_team.members[team_select].me.cost,my_team.members[team_select].cur_hp ,my_team.members[team_select].me.atk, my_team.members[team_select].me.def, my_team.members[team_select].me.dex, my_team.members[team_select].me.crit);
    printf("%d\n", enemy_team.total_cost);

}