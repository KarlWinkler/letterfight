// team.c
//
// used to hold functions that deal with team 
//
// Author: Karl Winkler
// Date Created: Mar. 8, 2022
// Last Change: Mar. 8, 2022 (git is correct if different)

#include "structs.c"

// defines used by anything that uses team.c
#define FIRST 'a'
#define LAST 'z'
#define ITEMS_LEN LAST - FIRST
#define CLEAR printf("\033[2J\033[H")
#define MAX_MEMBERS 5
#define UNDO_BUFFER 20

struct team my_team;
struct history_item history[UNDO_BUFFER];
int history_index = 0;

void team_init(){
    my_team.total_cost = 0;
    my_team.offence = 0;
    my_team.defence = 0.0f;
    my_team.dexterity = 0;
    my_team.crit = 0;
    my_team.health = 0;
    my_team.num_members = 0;
}

void add_to_history(int type, struct member mem, int mem_inx, struct menu_item *item){

    if(history_index >= UNDO_BUFFER){
        for(int i = 0; i < UNDO_BUFFER - 1; i++){
            history[i] = history[i+1];
        }
        history_index = UNDO_BUFFER - 1;      
    }

    history[history_index].type = type;
    history[history_index].mem = mem;
    history[history_index].item = item;
    history[history_index].mem_inx = mem_inx;
    history_index++;
}

void add_to_team(struct menu_item *toAdd){
    if((*toAdd).bought == 1){
        return;
    }

    if(my_team.num_members < MAX_MEMBERS){
        my_team.members[my_team.num_members] = (*toAdd).m;
        my_team.num_members ++;
        if(my_team.num_members == 1){
            my_team.total_cost = 0;
        }
        my_team.total_cost += (*toAdd).m.cost;
        (*toAdd).bought = 1;

        struct member empty;
        add_to_history(0, empty, 0, toAdd);
    }
}

void delete_from_team(int team_select){
    if(team_select >= my_team.num_members){
        return;
    }

    // remove cost

    struct menu_item empty;
    add_to_history(1, my_team.members[team_select], team_select, &empty);

    my_team.total_cost -= my_team.members[team_select].cost;
    for(int i = team_select; i < my_team.num_members; i++){
        my_team.members[i] = my_team.members[i+1];
    }
    my_team.num_members --;
}

void undo_last(){
    struct history_item h = history[history_index-1];
    if(history_index <= 0){
        return;
    }
    if(h.type == 0){
        h.item->bought = 0;
        my_team.num_members--;
        my_team.total_cost -= h.item->m.cost;
        history_index--;
    }
    else if(h.type == 1){
        for(int i = my_team.num_members; i > h.mem_inx; i--){
            my_team.members[i] = my_team.members[i-1];
        }
        my_team.members[h.mem_inx] = h.mem;
        my_team.num_members++;
        my_team.total_cost += h.mem.cost;
        history_index--;
    }
}

void calc_team_power(){

    my_team.offence = 0;
    my_team.defence = 0;
    my_team.dexterity = 0;
    my_team.crit = 0;

    for(int i = 0; i < my_team.num_members; i++){
        my_team.offence += my_team.members[i].atk;
        my_team.defence += my_team.members[i].def;
        my_team.dexterity += my_team.members[i].dex;
        my_team.crit += my_team.members[i].crit;
    }

    my_team.offence = my_team.offence / my_team.total_cost;
    my_team.defence = my_team.defence / my_team.total_cost;
    my_team.dexterity = my_team.dexterity / my_team.total_cost;
    my_team.crit = my_team.crit / my_team.total_cost;

}
