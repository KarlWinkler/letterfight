// team.c
//
// Author: Karl Winkler
// Date Created: Mar. 6, 2022
// Last Change: Mar. 8, 2022 (git is correct if different)

struct member{
    char name;
    int atk;
    int def;
    int dex;
    int crit;
    int cost;
};

struct menu_item{
    struct member m;
    char title[1024];
    char title_select[1024];
    char disabled[1024];
    char disabled_selected[1024];
    int bought;
};

struct history_item{
    struct menu_item *item;
    struct member mem;
    int mem_inx;
    int type; // 0 = buy; 1 = delete; 

};

struct team{
    struct member members[24];
    int num_members;
    int health;
    int balance;

    // used to display power of team
    int total_cost;
    // power stats
    float offence;
    float defence;
    float dexterity;
    float crit;
    // more for bonuses
    // more for stats/logs 
};

// struct member *map;