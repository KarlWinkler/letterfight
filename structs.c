// team.c

struct member{
    char name;
    int atk;
    int def;
    int dex;
    int crit;
};

struct team{
    struct member *members;
    int health;
    // more for stats/logs 
};

struct map{
    struct member *map;
};