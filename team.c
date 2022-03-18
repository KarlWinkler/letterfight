// team.c
//
// used to hold functions that deal with team 
//
// Author: Karl Winkler
// Date Created: Mar. 8, 2022
// Last Change: Mar. 8, 2022 (git is correct if different)
#ifndef TEAM_C
#define TEAM_C

#include "structs.h"
#include "macros.h"

struct history_item history[UNDO_BUFFER];
int history_index = 0;

void team_init(struct team *my_team){
    my_team->total_cost = 0;
    my_team->offence = 0;
    my_team->defence = 0.0f;
    my_team->dexterity = 0;
    my_team->crit = 0;
    my_team->health = 0;
    my_team->num_members = 0;
    my_team->balance = 0;
}

void level_up(struct member m){
    float level = m.level;
    m.cost += m.cost / level;
    m.atk += m.atk / level;
    m.def += m.def / level;
    m.dex += m.dex / level;
    m.crit += m.crit / level;
    m.level++;
}

void level_to(struct member mem, int lvl){
    mem.cost *= lvl;
    mem.atk *= lvl;
    mem.def *= lvl;
    mem.dex *= lvl;
    mem.crit *= lvl;
    mem.level = lvl;
}

int check_duplicate(struct member m, struct member *mem_list, int len){
    for(int i = 0; i < len; i++){
        if(m.name == mem_list[i].name){
            return i;
        }
    }
    return -1;
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

void add_to_team(struct menu_item *toAdd, struct team *my_team){
    if((*toAdd).bought == 1){
        return;
    }

    if(my_team->num_members < MAX_MEMBERS){
        int inx = 0;

        if((inx = check_duplicate(toAdd->m, my_team->members, my_team->num_members)) >= 0){
            level_up(my_team->members[inx]);
            struct menu_item empty;
            add_to_history(2, my_team->members[inx], inx, &empty);
            return;
        }

        my_team->members[my_team->num_members] = (*toAdd).m;
        my_team->num_members ++;
        if(my_team->num_members == 1){
            my_team->total_cost = 0;
        }
        my_team->total_cost += (*toAdd).m.cost;
        (*toAdd).bought = 1;

        struct member empty;
        add_to_history(0, empty, 0, toAdd);
    }
}

void sell_from_team(int team_select, struct team *my_team){
    if(team_select >= my_team->num_members){
        return;
    }

    // remove cost

    struct menu_item empty;
    add_to_history(1, my_team->members[team_select], team_select, &empty);

    my_team->total_cost -= my_team->members[team_select].cost;
    for(int i = team_select; i < my_team->num_members; i++){
        my_team->members[i] = my_team->members[i+1];
    }
    my_team->num_members --;
}

void undo_last(struct team *my_team){
    struct history_item h = history[history_index-1];
    if(history_index <= 0){
        return;
    }
    if(h.type == 0){
        h.item->bought = 0;
        my_team->num_members--;
        my_team->total_cost -= h.item->m.cost;
        history_index--;
    }
    else if(h.type == 1){
        for(int i = my_team->num_members; i > h.mem_inx; i--){
            my_team->members[i] = my_team->members[i-1];
        }
        my_team->members[h.mem_inx] = h.mem;
        my_team->num_members++;
        my_team->total_cost += h.mem.cost;
        history_index--;
    }
    else if(h.type == 2){
        h.mem.cost -= h.mem.cost / (float)h.mem.level;
        h.mem.atk -= h.mem.atk / (float)h.mem.level;
        h.mem.def -= h.mem.def / (float)h.mem.level;
        h.mem.dex -= h.mem.dex / (float)h.mem.level;
        h.mem.crit -= h.mem.crit / (float)h.mem.level;
        h.mem.level--;

    }
}

void calc_team_power(struct team *my_team){

    my_team->offence = 0;
    my_team->defence = 0;
    my_team->dexterity = 0;
    my_team->crit = 0;

    for(int i = 0; i < my_team->num_members; i++){
        my_team->offence += my_team->members[i].atk;
        my_team->defence += my_team->members[i].def;
        my_team->dexterity += my_team->members[i].dex;
        my_team->crit += my_team->members[i].crit;

    }
    my_team->defence = my_team->defence / my_team->total_cost;
    my_team->offence = my_team->offence / my_team->total_cost;
    my_team->dexterity = my_team->dexterity / my_team->total_cost;
    my_team->crit = my_team->crit / my_team->total_cost;

}
#endif