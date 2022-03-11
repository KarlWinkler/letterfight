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


struct member enemy[5];
int enemy_len = 0;

void enemy_level(struct member *mem, int lvl){
    mem->cost *= lvl;
    mem->atk *= lvl;
    mem->def *= lvl;
    mem->dex *= lvl;
    mem->crit *= lvl;
    mem->level = lvl;
}

void generate_enemy(struct member *letter_map){
    int total_cost = 0;
    int used[MAX_MEMBERS];
    int used_num = 0;

    int rand_one = random_int(ITEMS_LEN);
    int rand_two = 0;
    while((rand_two = random_int(ITEMS_LEN)) == rand_one){}

    total_cost = letter_map[rand_one].cost + letter_map[rand_two].cost;
    used[0] = rand_one;
    used[1] = rand_two;
    enemy[0] = letter_map[rand_one];
    enemy[1] = letter_map[rand_two];
    used_num = 2;
    enemy_len = 2;

    if(total_cost >= my_team.total_cost){
        // printf("%d\n", enemy_len);
        
        return;
    }
    while(total_cost < my_team.total_cost && enemy_len < MAX_MEMBERS){

        int rand = random_int(ITEMS_LEN);
        int duplicate = 0;

        for(int i = 0; i < used_num; i++){
            if(used[i] == rand){
                duplicate = 1;
            }  
        }
        if(duplicate){
            continue;
        }

        used[used_num] = rand;
        enemy[enemy_len] = letter_map[rand];
        total_cost += enemy[enemy_len].cost;
        enemy_len++;
        used_num++;
    }
}

void display_fight_menu(int enemy_select, int  team_select){
    CLEAR;

    // printf("%d\n", enemy_len);
    char enemy_out[1024];
    bzero(enemy_out, sizeof(enemy_out));

    for(int i = 0; i < enemy_len; i++){
        char n[4];
        n[0] = enemy[i].name;
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
    printf("%s\n", enemy_out);
    printf("cost: %d\n\nattack: %d\ndeffence: %d\ndexterity: %d\ncrit chance: %d\n\n", enemy[enemy_select].cost, enemy[enemy_select].atk, enemy[enemy_select].def, enemy[enemy_select].dex, enemy[enemy_select].crit);
    printf("%s\n", team_out);
    printf("cost: %d\n\nattack: %d\ndeffence: %d\ndexterity: %d\ncrit chance: %d\n", items[team_select].m.cost, items[team_select].m.atk, items[team_select].m.def, items[team_select].m.dex, items[team_select].m.crit);


}