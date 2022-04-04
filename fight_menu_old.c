// // fight_menu.c
// //
// // displays the controls menu
// //
// // Author: Karl Winkler
// // Date Created: Mar. 10, 2022
// // Last Change: Mar. 10, 2022 (git is correct if different)

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "macros.h"
// #include "structs.h"
// #include "random.h"
// #include "team.c"

// struct member enemy[5];
// int enemy_len = 0;

// void generate_enemy(struct team *enemy_team, struct member *letter_map, struct team *user_team){
//     int total_cost = 0;
//     int used[MAX_MEMBERS];
//     int used_num = 0;
//     int target_cost = user_team->total_cost;

//     while(total_cost < target_cost && enemy_len < MAX_MEMBERS){

//         int rand = random_int(ITEMS_LEN);
//         int duplicate = 0;

//         for(int i = 0; i < used_num; i++){
//             if(used[i] == rand){
//                 duplicate = 1;
//             }  
//         }
//         if(duplicate){
//             duplicate = 0;
//             continue;
//         }

//         used[used_num] = rand;
//         enemy[enemy_len] = letter_map[rand];
//         total_cost += enemy[enemy_len].cost;
//         enemy_len++;
//         used_num++;
//     }

//     while(total_cost < target_cost){
//         int rand_memb = random_int(enemy_len);
//         total_cost += enemy[rand_memb].cost;
//         level_up(&enemy[rand_memb]);
//     }

//     enemy_team->total_cost = total_cost;
//     for(int i = 0; i < enemy_len; i++){
//         enemy_team->members[i].me = enemy[i];
//     }
//     calc_team_power(enemy_team);
// }

// void display_fight_menu(int enemy_select, int  team_select, struct team my_team, struct team enemy_team){
//     CLEAR;

//     // printf("%d\n", enemy_len);
//     char enemy_out[1024];
//     bzero(enemy_out, sizeof(enemy_out));

//     for(int i = 0; i < enemy_len; i++){
//         char n[4];
//         n[0] = enemy[i].name;
//         n[1] = '\0';
//         // strcat(enemy_out, n);
//         if(i == enemy_select){
//             strcat(enemy_out, "\033[30m\033[41m ");
//         }
//         else{
//             strcat(enemy_out, "\033[30m\033[47m ");
//         }
//         strcat(enemy_out, n);
//         strcat(enemy_out, " \033[0m ");
//     }

//     char team_out[100];
//     bzero(team_out, sizeof(team_out));

//     for(int i = 0; i < my_team.num_members; i++){
        
//         char n[2];

//         n[0] = my_team.members[i].me.name;
//         n[1] = '\0';

//         if(i == team_select){
//             strcat(team_out, "\033[30m\033[44m ");
//         }
//         else{
//             strcat(team_out, "\033[30m\033[47m ");
//         }
//         strcat(team_out, n);
//         strcat(team_out, " \033[0m ");

//     } 
//     printf("%s\n", enemy_out);
//     printf("cost: %d\n\nattack: %d\ndeffence: %d\ndexterity: %d\ncrit chance: %d\n\n", enemy_team.members[enemy_select].me.cost, enemy_team.members[enemy_select].me.atk, enemy_team.members[enemy_select].me.def, enemy_team.members[enemy_select].me.dex, enemy_team.members[enemy_select].me.crit);
//     printf("%s\n", team_out);
//     printf("cost: %d\n\nattack: %d\ndeffence: %d\ndexterity: %d\ncrit chance: %d\n", my_team.members[team_select].me.cost, my_team.members[team_select].me.atk, my_team.members[team_select].me.def, my_team.members[team_select].me.dex, my_team.members[team_select].me.crit);
//     printf("%d\n", enemy_team.total_cost);

// }