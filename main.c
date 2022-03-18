// main.c
//
// Fight with randomly statted letters, use power-ups to win close fights 
// and level up your units to dominate your opponents!
//
// Author: Karl Winkler
// Date Created: Mar. 6, 2022
// Last Change: Mar. 8, 2022 (git is correct if different)
// github repository: https://github.com/KarlWinkler/letterfight

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

// #include "structs.c"
#include "home_menu.c"
#include "buy_menu.c"
#include "controls_menu.c"
#include "fight_menu.c"
#include "random.h"
#include "macros.h"

// variables required in main 
struct member letter_map[ITEMS_LEN];
struct team my_team;
struct team enemy_team;

int gamestate = 0; // 0 = home; 1 = buy; 2 = fight; 3 = controls; 4 = stats?(maybe i will implement this)
int last_state = 0;
int member_sel = 0;
int team_sel = 0;
int enemy_select = 0;
int fight_sel_state = 0;
char c = 0;
char old_c = 1;

// generates the new members to play the game
// this is called once at the start of a game
void generate_map(){
    int i = FIRST;
    int index = 0;
    while(i < LAST){
        struct member new;

        int strength_roll = random_int(10);

        new.name = i;
        new.cost = strength_roll;
        new.atk = (int)(strength_roll*(random_int(100)*0.01) + 1); // multiply by decimal
        new.def = (int)(strength_roll*(random_int(100)*0.01) + 1);
        new.dex = (int)(strength_roll*(random_int(100)*0.01) + 1);
        new.crit = (int)(strength_roll*(random_int(100)*0.01) + 1);
        new.level = 1;

        letter_map[index] = new;
         
        i++;
        index++;
    }
}

struct menu_item items[ITEMS_LEN];
// struct menu_item transact[MAX_MEMBERS];
// int trans_size = 0;


void build_items(struct member *letter_map){

    for(int i = 0; i < ITEMS_LEN; i++){
        items[i].m = letter_map[i];
        char temp[10000];

        char n[2];

        n[0] = letter_map[i].name;
        n[1] = '\0';

        // normal
        
        strcat(temp, " ");
        strcat(temp, n);
        strcat(temp, " \t");

        strcpy(items[i].title, temp);

        bzero(temp, sizeof(temp));

        // select

        strcat(temp, "\033[44m ");
        strcat(temp, n);
        strcat(temp, " \t\033[47m");

        strcpy(items[i].title_select, temp);
        
        bzero(temp, sizeof(temp));

        //bought

        strcat(temp, "\033[40m\033[37m ");
        strcat(temp, n);
        strcat(temp, " \t\033[47m\033[30m");

        strcpy(items[i].disabled, temp);
        
        bzero(temp, sizeof(temp));

        // bought selected

        strcat(temp, "\033[40m\033[31m ");
        strcat(temp, n);
        strcat(temp, " \t\033[47m\033[30m");

        strcpy(items[i].disabled_selected, temp);
        
        bzero(temp, sizeof(temp));

        items[i].bought = 0;
    }

}

void new_fight_state(){
    team_sel = 0;
    generate_enemy(&enemy_team, letter_map, &my_team);

}

// takes a char 
// returns a response code
// 0 == OK; 1 == exit;
int handel_key_press(char c){

    // global hot keys
    
    // ` => quit game (maybe ESC should as well) 

    // quit the program
    if(c == '`'){ 
        return 1;
    }

    if(gamestate == 0){
        if(c == ' ' || c == 13 || c == 'p'){
            gamestate = 1;
        }
        if(c == 'c'){
            gamestate = 3;
            last_state = 0;
        }
        else{
            return 0;
        }
    } 

    // buy menu hotkeys 
    // UP => move team select rightS
    // DOWN => move team select left
    // LEFT => move member select left
    // RIGHT => move member select right
    // p => purchase member from member list
    // d => delete member from team list
    // u => undo last action (up to UNDO_BUFFER)
    else if(gamestate == 1){

        if(c == 65){ // UP - increment team_select
            team_sel++;
        }
        if(c == 66){ // DOWN - decrement team_select
            if(team_sel > 0){
                team_sel--;                
            }
            else{
                team_sel = MAX_MEMBERS - 1;
            }
        }
        if(c == 67){ // RIGHT - increment member_sel
            member_sel++;
        }
        if(c == 68){ // LEFT - decrement member_sel
            if(member_sel > 0){
                member_sel--;            
            }
            else{
                member_sel = MAX_TO_SCREEN - 1;
            }
        }
        if(c == 'p'){ // purchase
            add_to_team(&items[member_sel % MAX_TO_SCREEN], &my_team);
        }
        if(c == 's'){ // sell 
            sell_from_team(team_sel % MAX_MEMBERS, &my_team);
        }
        if(c == 'u'){ // undo
            undo_last(&my_team);
        }
        if(c == 'c'){
            gamestate = 3;
            last_state = 1;
        }
        if(c == 10){ // ENTER moves to fight phase
            gamestate = 2;
            new_fight_state();
        }
        else{
            return 0;
        }
    }

    if(gamestate == 2){
        if(fight_sel_state == 0){
            if(c == 67){ // RIGHT - increment member_sel
                enemy_select++;
            }
            if(c == 68){ // LEFT - decrement member_sel
                if(enemy_select > 0){
                    enemy_select--;            
                }
                else{
                    enemy_select = enemy_len - 1;
                }
            }
        }

        if(fight_sel_state == 1){
            if(c == 67){ // RIGHT - increment member_sel
                team_sel++;
            }
            if(c == 68){ // LEFT - decrement member_sel
                if(team_sel > 0){
                    team_sel--;            
                }
                else{
                    team_sel = my_team.num_members - 1;
                }
            }
        }
        

        if(c == 65){ // UP - increment fight_sel_state
            if(fight_sel_state == 0){
                fight_sel_state = 1;                
            }
            else{
                fight_sel_state = 0;
            }
        }
        if(c == 66){ // DOWN - decrement fight_sel_state
            if(fight_sel_state == 0){
                fight_sel_state = 1;                
            }
            else{
                fight_sel_state = 0;
            }
        }

        if(c == 'c'){
            gamestate = 3;
            last_state = 2;
        }
        else{
            return 0;
        }
    }

    if(gamestate == 3){
        if(c == 'b'){
            gamestate = last_state;
        }
        else{
            return 0;
        }
    }

    return 0;
}

// iniit gamedata
void game_init(){

    // generate required data
    generate_map();
    build_items(letter_map);
    team_init(&my_team);
}

// stuff for setting terminal to raw mode
struct termios orig_term_attr;
struct termios new_term_attr;

int main(){

    char cur = 0;
    //clear game board and hide cursor
    CLEAR;
    printf("\e[?25l"); // https://stackoverflow.com/questions/30126490/how-to-hide-console-cursor-in-c


    struct winsize w;
   
    // raw mode 
    /* from https://github.com/benapetr/snake/blob/master/src/main.c */
    /* more resources at https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html */
    /* set the terminal to raw mode */ 
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // more raw mode
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    game_init();

    // clear again just in case
    CLEAR;

    while(1){

        // don't do anything unless the last key pressed changes

        // i deal with duplicate key presses by setting c to 0 
        // after the user presses it        
        while(c == old_c){
             read(0, &c, 1); // read user input
             cur = c;
             usleep(100); // so that it is not too memory intensive (still not great I think)
        }

        old_c = c; // so that above works

        if((c = handel_key_press(c))){ // handel key press 0 == OK; 1 == exit;
            break;
        }

        switch(gamestate){
            case 0:
                display_home_menu();
                // printf("c = %d\n", cur);

                break;
            case 1:
                display_buy_menu(c, member_sel % MAX_TO_SCREEN, team_sel % MAX_MEMBERS, letter_map, items, &my_team);
                printf("c = %d\n", cur);
                break; 
            case 2:
                display_fight_menu(enemy_select % enemy_len, team_sel % my_team.num_members, my_team, enemy_team);
                break;
            case 3:
                display_controls_menu();
                break;
            default:
                display_home_menu();
        }
    }
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr); // remove raw
    printf("\e[?25h\033[0m\n"); // give cursor back

}

