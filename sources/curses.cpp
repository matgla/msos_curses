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

#include <cstddef>
#include <unistd.h>
#include <stdarg.h>
#include <cstring>

#include "curses.h"

#include "sys/ioctl.h"
#include <termios.h>
#include "msos/libc/printf.hpp"

#include "msos/usart_printer.hpp"

namespace
{
WINDOW window;
static UsartWriter writer;

constexpr const char* bold = "\033[1m";
constexpr const char* underline = "\033[4m";
constexpr const char* reverse = "\033[7m";
constexpr const char* noreverse = "\033[27m";
constexpr const char* nobold = "\033[22m";
constexpr const char* nounderline = "\033[24m";
constexpr const char* color_black = "\033[1;30m";
constexpr const char* color_red = "\033[1;31m";
constexpr const char* color_reset = "\033[0m";
constexpr const char* bgcolor_black = "\033[1;40m";
constexpr const char* bgcolor_red = "\033[1;41m";
constexpr const char* bgcolor_reset = "\033[0m";

    // Background Black: \u001b[40m
    // Background Red: \u001b[41m
    // Background Green: \u001b[42m
    // Background Yellow: \u001b[43m
    // Background Blue: \u001b[44m
    // Background Magenta: \u001b[45m
    // Background Cyan: \u001b[46m
    // Background White: \u001b[47m

struct Color
{
    short fg;
    short bg;
};

Color colors[COLOR_PAIRS];

}



WINDOW* stdscr = nullptr;

int move(int y, int x)
{
    printf("\033[%d;%dH", x, y);
    return 0;
}

int clear()
{
    printf("\033[H\033[J");
    return 0;
}

WINDOW* initscr()
{
    stdscr = &window;
    clear();
    move(0, 0);
    std::memset(&colors, -1, sizeof(colors));
    fflush(stdout);
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    window.max_x = w.ws_col;
    window.max_y = w.ws_row;

    return &window;
}

void endwin()
{
    echo();
    printf(nobold);
    attroff(COLOR_PAIR(1));
    fflush(stdout);
}

int getmaxx(WINDOW* window)
{
    return window->max_x;
}

int getmaxy(WINDOW* window)
{
    return window->max_y;
}

// PRINTERS //

int printw(const char *str, ...)
{
    va_list arg;
    va_start (arg, str);
    int done = __vfprintf_(writer, 1, str, arg, 0);
    va_end (arg);
    return done;
}

int mvprintw(int row, int column, const char *str, ...)
{
    move(column, row);
    va_list arg;
    va_start (arg, str);
    int done = __vfprintf_(writer, 1, str, arg, 0);
    va_end (arg);
    return done;
}

int refresh(void)
{
    fflush(stdout);
    return 0;
}

int noecho(void)
{
    struct termios tattr;

    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON | ECHO);
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr (STDIN_FILENO, TCSANOW, &tattr);
    return 0;
}

int echo(void)
{
    struct termios tattr;

    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag |= ECHO;
    tcsetattr (STDIN_FILENO, TCSANOW, &tattr);
    return 0;
}

// INPUT
int getch(void)
{
    char buffer;
    while (!read(STDIN_FILENO, &buffer, 1));
    return buffer;
}

//-------------------------------------------//
//------         ATTRIBUTES           -------//
//-------------------------------------------//

int wattroff(WINDOW* win, int attrs)
{
    if (win == nullptr)
    {
        return ERR;
    }
    win->attributes &= (~attrs);
    return OK;
}

int wattron(WINDOW* win, int attrs)
{
    if (win == nullptr)
    {
        return ERR;
    }

    if (attrs & A_COLOR_MASK)
    {
        win->attributes &= (~A_COLOR_MASK);
    }
    win->attributes |= attrs;
    return OK;
}

int wattrset(WINDOW* win, int attrs)
{
    if (win == nullptr)
    {
        return ERR;
    }

    win->attributes = attrs;
    return OK;
}

int wcolor_set(WINDOW* win, short color_pair_number, void* opts)
{
    static_cast<void>(opts);
    if (win == nullptr)
    {
        return ERR;
    }

    if (color_pair_number < 1 || color_pair_number > COLOR_PAIRS - 1)
    {
        return ERR;
    }

    win->attributes &= ~(A_COLOR_MASK);
    win->attributes |= (color_pair_number << A_COLOR_OFFSET);
    return OK;
}

int raw()
{
    return 0;
}

int noraw()
{
    return 0;
}

int keypad(WINDOW* window, bool bf)
{
    window->key_translation = bf;
    return 0;
}

int getstr_(char* str, int size)
{
    return fgets(str, size, stdin) == nullptr ? ERR : OK;
}

//-------------------------------------------//
//------           COLORS             -------//
//-------------------------------------------//

int start_color(void)
{
    // TODO: initialize default
    return 0;
}

int init_pair(short id, short fg, short bg)
{
    if (id < 1 || id > COLOR_PAIRS - 1)
    {
        return ERR;
    }

    colors[id] = {
        .fg = fg,
        .bg = bg
    };
    return OK;
}

bool has_colors()
{
    // TODO: terminal type detector
    return TRUE;
}

int init_color(short color, short r, short g, short b)
{
    static_cast<void>(color);
    static_cast<void>(r);
    static_cast<void>(g);
    static_cast<void>(b);
    // TODO: color manipulation implementation
    return ERR;
}

bool can_change_color(void)
{
    // TODO: terminal type detector, color support
    return FALSE;
}

int pair_content(short pair, short* foreground, short* background)
{
    if (pair < 1 || pair > COLOR_PAIRS - 1)
    {
        return ERR;
    }

    *foreground = colors[pair].fg;
    *background = colors[pair].bg;
    return OK;
}
