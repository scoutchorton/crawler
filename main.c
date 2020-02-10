#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>

struct coordinates {
    int x;
    int y;
};

struct enemy {
    struct coordinates loc;
    char display;
    int health;
};

struct tile {
    struct coordinates loc;
    char display;
    bool collision;
};

bool coll(struct enemy e[], struct tile t[], struct coordinates c) {
    return false;
}

/*int len(void * arr) {
    return sizeof(arr)/sizeof(arr[0]);
}*/

int main(void) {

    //Curses initialization
    setlocale(LC_ALL, "");  //Sets the locale to allow unicode characters
    initscr();  //Inits stdscr
    keypad(stdscr, true);   //Forces special characters to use values like KEY_UP as opposed to raw()
    cbreak();   //Doesn't wait for a newline to submit stream of characters like a command line
    noecho();
    nodelay(stdscr, true);  //Normally getch() will wait for input, but this will remove that
    halfdelay(1);   //Sets delay on input so there isn't a 100% CPU usage
    curs_set(0);    //Invisible cursor

    //Window initialization
    WINDOW* game_win = newwin(20, 20, 1, 1);
    WINDOW* border_win = newwin(22, 22, 0, 0);
    
    //Border setup for ncurses
    box(border_win, 0, 0);
    refresh();
    wrefresh(border_win);

    //Variables outside of game loop
    bool first=TRUE;
    bool game_loop=true;
    int character;
    int x=0;
    int y=0;
    const char zero = *"0";

    //NPC and tile generation
    struct enemy enemies[3] = {[0 ... 2].loc = {.x = 5, .y = 3}, [0 ... 2].display = 'Z', [0 ... 2].health = 2};
    struct tile tiles[3] = {[0 ... 2].loc = {.x = 5, .y = 3}, [0 ... 2].display = 'O', [0 ... 2].collision = false};

    enemies[0].loc.x = 3; enemies[0].loc.y = 3;
    enemies[1].loc.x = 3; enemies[1].loc.y = 5;
    enemies[2].loc.x = 3; enemies[2].loc.y = 7;

    tiles[0].loc.x = 5; tiles[0].loc.y = 3;
    tiles[1].loc.x = 5; tiles[1].loc.y = 5;
    tiles[2].loc.x = 5; tiles[2].loc.y = 7;

    while(game_loop==true) {
        character=getch();

        //Character processing
        //mvwaddch(border_win, 0, 0, character);
        switch(character) {
            case KEY_UP:
                {
                    //waddstr(border_win, " up");
                    struct coordinates testCoords = {.x = x, .y = y-1};
                    if(!coll(enemies, tiles, testCoords)) {
                        y--;
                    }
                    break;
                }
            case KEY_RIGHT:
                {
                    //waddstr(border_win, " right");
                    struct coordinates testCoords = {.x = x+1, .y = y};
                    if(!coll(enemies, tiles, testCoords)) {
                        x++;
                    }
                    break;
                }
            case KEY_DOWN:
                {
                    //waddstr(border_win, " down");
                    struct coordinates testCoords = {.x = x, .y = y+1};
                    if(!coll(enemies, tiles, testCoords)) {
                        y++;
                    }
                    break;
                }
            case KEY_LEFT:
                {
                    //waddstr(border_win, " left");
                    struct coordinates testCoords = {.x = x-1, .y = y};
                    if(!coll(enemies, tiles, testCoords)) {
                        x--;
                    }
                    break;
                }
        }
        wrefresh(border_win);

        //Screen manipilation
        werase(game_win);
        for(int i=0; i<20; i++) {
            for(int i=0; i<20; i++) {
                waddstr(game_win, ".");
            }
        }
        mvwaddch(game_win, y, x, '0');
        for(int index=0; index<sizeof(enemies)/sizeof(enemies[0]); index++) {
            mvwaddch(game_win, enemies[index].loc.y, enemies[index].loc.x, enemies[index].display);
        }
        for(int index=0; index<sizeof(tiles)/sizeof(tiles[0]); index++) {
            mvwaddch(game_win, tiles[index].loc.y, tiles[index].loc.x, tiles[index].display);
        }
        //refresh();
        wrefresh(game_win);
    }

    //Cleanup
    delwin(game_win);
    delwin(border_win);
    endwin();

    return 0;
}