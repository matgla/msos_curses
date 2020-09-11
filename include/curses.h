// This file is part of MSOS Curses project.
// Copyright (C) 2020 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#if defined(__cplusplus)
extern "C"
{
#else
    typedef int bool;
#endif // __cplusplus

    //-------------------------------------------//
    //------         CONFIG               -------//
    //-------------------------------------------//


    #ifndef COLOR_PAIRS
        #define COLOR_PAIRS 16
    #endif // COLOR_PAIRS

    #ifndef COLORS
        #define COLORS 8
    #endif

    typedef struct WINDOW
    {
        int max_x;
        int max_y;
        bool key_translation;
        int attributes;
    } WINDOW;

    // Initialization

    #define FALSE 0
    #define TRUE 1

    #define OK 0
    #define ERR -1

    WINDOW* initscr(void);
    void endwin(void);
    extern WINDOW* stdscr;

    // Parameters
    int getmaxy(WINDOW* window);
    int getmaxx(WINDOW* window);

    #define getmaxyx(win,y,x) (y = getmaxy(win), x = getmaxx(win))


    int printw(const char *, ...);
    int mvprintw(int row, int colums, const char *, ...);
    int refresh(void);
    int noecho(void);
    int echo(void);
    int clear(void);


    // Positioning
    int move(int, int);

    int keypad(WINDOW *, bool);
    int getstr_(char *, int);

    // Input
    int getch(void);

    // Settings
    #define getstr(str) getstr_(str, sizeof(str));

    int raw(void);
    int noraw(void);

    //-------------------------------------------//
    //------         ATTRIBUTES           -------//
    //-------------------------------------------//

    #define A_NORMAL     0x01
    #define A_STANDOUT   0x02
    #define A_UNDERLINE  0x04
    #define A_REVERSE    0x08
    #define A_BLINK      0x10
    #define A_DIM        0x20
    #define A_BOLD       0x40
    #define A_PROTECT    0x80
    #define A_INVIS      0x0100
    #define A_ALTCHARSET 0x0200
    #define A_CHARTEXT   0x0400

    #define A_COLOR_MASK 0xffff0000
    #define A_COLOR_OFFSET 16

    int wattroff(WINDOW* win, int attrs);
    int wattron(WINDOW* win, int attrs);
    int wattrset(WINDOW* win, int attrs);
    int wcolor_set(WINDOW* win, short color_pair_number, void* opts);
    int wstandend(WINDOW* win);
    int wstandout(WINDOW* win);

    #define attron(attrs) wattron(stdscr, attrs)
    #define attroff(attrs) wattroff(stdscr, attrs)
    #define attrset(attrs) wattrset(stdscr, attrs)
    #define standout() attrset(A_STANDOUT)
    #define standend() attrset(A_NORMAL)
    #define wstandend(win) wattrset(win, A_NORMAL)
    #define wstandout(win) wattrset(win, A_STANDOUT)
    #define color_set(color_pair_number, opts) wcolor_set(stdscr, color_pair_number, opts)

    // Attribute
    // +---+---+---+---+---+---+---+---+
    // | . | . | . | . | . | . | . | . |
    // +---+---+---+---+---+---+---+---+
    // | . | C | O | L | O | R | . | . | color mask = 0xffff
    // +---+---+---+---+---+---+---+---+
    // | - | - | - | - | - | C | A | I | "-" - empty
    // +---+---+---+---+---+---+---+---+
    // | P | O | D | B | R | U | S | N | N - normal, S - standout, U - underline
    // +---+---+---+---+---+---+---+---+ R - reverse, B - blink, D - dim, O - bold
    //                                   P - protect, I -invisible, A - altcharset
    //                                   C - chartext

    //-------------------------------------------//
    //------           COLORS             -------//
    //-------------------------------------------//

    #define COLOR_BLACK   1
    #define COLOR_RED     2
    #define COLOR_GREEN   3
    #define COLOR_YELLOW  4
    #define COLOR_BLUE    5
    #define COLOR_MAGENTA 6
    #define COLOR_CYAN    7
    #define COLOR_WHITE   8

    int start_color(void);
    int init_pair(short pair, short foreground, short background);
    int init_color(short color, short r, short g, short b);
    bool has_colors();
    bool can_change_color(void);
    int color_content(short color, short* r, short* g, short* b);
    int pair_content(short pair, short* foreground, short* background);

    #define COLOR_PAIR(n) (n << A_COLOR_OFFSET)


#if defined(__cplusplus)
}
#endif // __cplusplus
