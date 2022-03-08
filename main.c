// main.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>

// #include "structs.c"
#include "menu.c"

#define MAX_TO_SCREEN 20

struct member letter_map[ITEMS_LEN];

int random(int max){
    struct timeval time;

    //get time as microseconds since unix epoch
    gettimeofday(&time, NULL);
    usleep(23);
    return (int)time.tv_usec % max;
}

int random_range(int min, int max){
    struct timeval time;

    //get time as microseconds since unix epoch
    gettimeofday(&time, NULL);

    // datetime modulo delta range added to min
    // leaves negative modulo unhandled
    usleep(23);
    return (min + (int)time.tv_usec % (max - min + 1));

    
    
}

void generate_map(){
    int i = '0';
    int index = 0;
    while(i < '}'){
        struct member new;

        int strength_roll = random(10);

        new.name = i;
        new.cost = strength_roll;
        new.atk = (int)(strength_roll*(random(100)*0.01) + 1); // multiply by decimal
        new.def = (int)(strength_roll*(random(100)*0.01) + 1);
        new.dex = (int)(strength_roll*(random(100)*0.01) + 1);
        new.crit = (int)(strength_roll*(random(100)*0.01) + 1);

        letter_map[index] = new;
         
        i++;
        index++;
    }
}

struct termios orig_term_attr;
struct termios new_term_attr;

int main(){
    // srand();

    CLEAR;
    printf("\e[?25l"); // https://stackoverflow.com/questions/30126490/how-to-hide-console-cursor-in-c


    struct winsize w;
   
    /* from https://github.com/benapetr/snake/blob/master/src/main.c */
    /* more resources at https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html */
    /* set the terminal to raw mode */ 
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);


    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);
    // int i = 0;

    generate_map();
    CLEAR;

    int select = 0;
    int team_sel = 0;
    char c = 0;
    char old_c = 1;
    team_init();

    while(1){


        // const int modulo_var = 20;
        
        // int a;

        // a = fgetc(stdin);
        // display_menu(a);
        // // printf("%s", c);
        // i++;
        // // sleep(1);

        // move into a new file or at least function

        
        while(c == old_c){
             read(0, &c, 1);// printf("%d\n", c);
             usleep(100);
        }

        old_c = c; 

        if(c == 13){
            continue;
        }
        if(c == '`'){
            break;
        }

        // arrow keys
        if(c == 65){ // increase team_select
            team_sel++;
        }
        if(c == 66){ // decrement team_select
            if(team_sel > 0){
                team_sel--;                
            }
            else{
                team_sel = MAX_MEMBERS - 1;
            }
        }
        if(c == 67){ // increment select
            select++;
        }
        if(c == 68){ // decrement select
            if(select > 0){
                select--;            
            }
            else{
                select = MAX_TO_SCREEN - 1;
            }
        }
        if(c == 112){ // p adds 
            add_to_team(select % MAX_TO_SCREEN, letter_map);
        }
        if(c == 100){ // d deletes
            delete_from_team(team_sel % MAX_MEMBERS);
        }

        usleep(10);
        // printf("\r%c", c);

        display_menu(c, select % MAX_TO_SCREEN, team_sel % MAX_MEMBERS, letter_map);
        
        // display_menu(c, -1, letter_map);

    }

    // CLEAR;
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);
    printf("\e[?25h\033[0m\n");

}

