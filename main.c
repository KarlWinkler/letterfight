// main.c

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "menu.c"

#define CLEAR printf("\033[2J\033[H")

void create_display(){
    printf("team");
}

struct termios orig_term_attr;
struct termios new_term_attr;

int main(){
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
    while(1){

        int select;
        
        // int a;
        char c;
        char old_c;
        // a = fgetc(stdin);
        // display_menu(a);
        // // printf("%s", c);
        // i++;
        // // sleep(1);

        read(0, &c, 1);// printf("%d\n", c);
        if(c == 13){
            continue;
        }
        if(c == '`'){
            break;
        }
        if(c == 67){
            select++;
            c++;
        }
        usleep(100);
        // printf("\r%c", c);

        display_menu(c, select%4);

        old_c = c;
    }

    // CLEAR;
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);
    printf("\e[?25h\033[0m\n");

}

