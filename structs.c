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
    char title[1024];
    char title_select[1024];
};

struct team{
    struct member *members;
    int health;
    // more for stats/logs 
};

// struct member *map;