// team.c

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
    char *title;
    int title_select;
};

struct team{
    struct member *members;
    int health;
    // more for stats/logs 
};

struct member *letter_map;
// struct member *map;