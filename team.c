#include "structs.c"

#define FIRST 'a'
#define LAST 'z'
#define ITEMS_LEN LAST - FIRST
#define CLEAR printf("\033[2J\033[H")
#define MAX_MEMBERS 5

struct team my_team;

void team_init(){
    my_team.total_cost = 0;
    my_team.offence = 0;
    my_team.defence = 0.0f;
    my_team.dexterity = 0;
    my_team.crit = 0;
    my_team.health = 0;
    my_team.num_members = 0;
}

void add_to_team(int select, struct menu_item *items){
    if(items[select].bought == 1){
        return;
    }

    if(my_team.num_members < MAX_MEMBERS){
        my_team.members[my_team.num_members] = items[select].m;
        my_team.num_members ++;
        if(my_team.num_members == 1){
            my_team.total_cost = 0;
        }
        my_team.total_cost += items[select].m.cost;
        items[select].bought = 1;
    }
}

void delete_from_team(int team_select){
    if(team_select >= my_team.num_members){
        return;
    }

    // remove cost
    my_team.total_cost -= my_team.members[team_select].cost;
        

    for(int i = team_select; i < my_team.num_members; i++){
        my_team.members[i] = my_team.members[i+1];
    }
    my_team.num_members --;
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
