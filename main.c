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

bool coll(int eSize, struct enemy e[], int tSize, struct tile t[], struct coordinates c) {
    for(int index=0; index<eSize/sizeof(e[0]); index++) {
        if(e[index].loc.x == c.x && e[index].loc.y == c.y) {
            return true;
        }
    }
    for(int index=0; index<tSize/sizeof(t[0]); index++) {
        if(t[index].loc.x == c.x && t[index].loc.y == c.y && t[index].collision == true) {
            return true;
        }
    }
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
    bool game_loop=true;
    int character;
    int x=1;
    int y=1;
    const char zero = *"0";

    //NPC and tile generation
    struct enemy enemies[2] = {[0 ... 1].loc = {.x = 0, .y = 0}, [0 ... 1].display = 'Z', [0 ... 1].health = 2};
    struct tile tiles[24] = {[0 ... 23].loc = {.x = 0, .y = 0}, [0 ... 23].display = 'W', [0 ... 23].collision = true};

    enemies[0].loc.x = 3; enemies[0].loc.y = 3;
    enemies[1].loc.x = 4; enemies[1].loc.y = 4;

    tiles[0].loc.x = 0; tiles[0].loc.y = 0;
    tiles[1].loc.x = 1; tiles[1].loc.y = 0;
    tiles[2].loc.x = 2; tiles[2].loc.y = 0;
    tiles[3].loc.x = 3; tiles[3].loc.y = 0;
    tiles[4].loc.x = 4; tiles[4].loc.y = 0;
    tiles[5].loc.x = 5; tiles[5].loc.y = 0;
    tiles[6].loc.x = 6; tiles[6].loc.y = 0;
    tiles[7].loc.x = 0; tiles[7].loc.y = 1;
    tiles[8].loc.x = 6; tiles[8].loc.y = 1;
    tiles[9].loc.x = 0; tiles[9].loc.y = 2;
    tiles[10].loc.x = 6; tiles[10].loc.y = 2;
    tiles[11].loc.x = 0; tiles[11].loc.y = 3;
    tiles[12].loc.x = 6; tiles[12].loc.y = 3;
    tiles[13].loc.x = 0; tiles[13].loc.y = 4;
    tiles[14].loc.x = 6; tiles[14].loc.y = 4;
    tiles[15].loc.x = 0; tiles[15].loc.y = 5;
    tiles[16].loc.x = 6; tiles[16].loc.y = 5;
    tiles[17].loc.x = 0; tiles[17].loc.y = 6;
    tiles[18].loc.x = 1; tiles[18].loc.y = 6;
    tiles[19].loc.x = 2; tiles[19].loc.y = 6;
    tiles[20].loc.x = 3; tiles[20].loc.y = 6;
    tiles[21].loc.x = 4; tiles[21].loc.y = 6;
    tiles[22].loc.x = 5; tiles[22].loc.y = 6;
    tiles[23].loc.x = 6; tiles[23].loc.y = 6;

    while(game_loop==true) {
        character=getch();

        //Character processing
        switch(character) {
            case KEY_UP:
                {
                    struct coordinates testCoords = {.x = x, .y = y-1};
                    if(!coll(sizeof(enemies), enemies, sizeof(tiles), tiles, testCoords)) {
                        y--;
                    }
                    break;
                }
            case KEY_RIGHT:
                {
                    struct coordinates testCoords = {.x = x+1, .y = y};
                    if(!coll(sizeof(enemies), enemies, sizeof(tiles), tiles, testCoords)) {
                        x++;
                    }
                    break;
                }
            case KEY_DOWN:
                {
                    struct coordinates testCoords = {.x = x, .y = y+1};
                    if(!coll(sizeof(enemies), enemies, sizeof(tiles), tiles, testCoords)) {
                        y++;
                    }
                    break;
                }
            case KEY_LEFT:
                {
                    struct coordinates testCoords = {.x = x-1, .y = y};
                    if(!coll(sizeof(enemies), enemies, sizeof(tiles), tiles, testCoords)) {
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
        for(int index=0; index<sizeof(enemies)/sizeof(enemies[0]); index++) {
            mvwaddch(game_win, enemies[index].loc.y, enemies[index].loc.x, enemies[index].display);
        }
        for(int index=0; index<sizeof(tiles)/sizeof(tiles[0]); index++) {
            mvwaddch(game_win, tiles[index].loc.y, tiles[index].loc.x, tiles[index].display);
        }
        mvwaddch(game_win, y, x, *"P");
        wrefresh(game_win);
    }

    //Cleanup
    delwin(game_win);
    delwin(border_win);
    endwin();

    return 0;
}