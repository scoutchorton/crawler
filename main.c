#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>

int main(void) {

    //Curses initialization
    setlocale(LC_ALL, "");  //Sets the locale to allow unicode characters
    initscr();  //Inits stdscr
    keypad(stdscr, true);   //Forces special characters to use values like KEY_UP as opposed to raw()
    cbreak();   //Doesn't wait for a newline to submit stream of characters like a command line
    noecho();
    nodelay(stdscr, true);  //Normally getch() will wait for input, but this will remove that
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

    while(game_loop==true) {
        //On
        //if(first) {
        //    first=false;
        //} else {
            character=getch();
        //}

        //Character processing
        mvwaddch(border_win, 0, 0, character);
        switch(character) {
            case KEY_UP:
                waddstr(border_win, " up");
                y--;
                break;
            case KEY_RIGHT:
                waddstr(border_win, " right");
                x++;
                break;
            case KEY_DOWN:
                waddstr(border_win, " down");
                y++;
                break;
            case KEY_LEFT:
                waddstr(border_win, " left");
                x--;
                break;
        }
        wrefresh(border_win);

        //Screen manipilation
        werase(game_win);
        for(int i=0; i<20; i++) {
            for(int i=0; i<20; i++) {
                waddstr(game_win, ".");
            }
        }
        mvwaddch(game_win, y, x, zero);
        //refresh();
        wrefresh(game_win);
    }

    //Cleanup
    delwin(game_win);
    delwin(border_win);
    endwin();

    return 0;
}