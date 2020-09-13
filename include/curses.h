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

#include <term.h>
#include <stdio.h>

#if defined(__cplusplus)
extern "C"
{
#else
    typedef int bool;
#endif // __cplusplus

    //-------------------------------------------//
    //------         CONFIG               -------//
    //-------------------------------------------//

    typedef char cchar_t;

    #ifndef COLOR_PAIRS
        #define COLOR_PAIRS 16
    #endif // COLOR_PAIRS

    #ifndef COLORS
        #define COLORS 8
    #endif

    // -----------------------------------------//
    // -------         types            --------//
    // -----------------------------------------//

    // Attribute 16-bit
    // +---+---+---+---+---+---+---+---+
    // | - | - | - | - | - | - | - | - | character
    // +---+---+---+---+---+---+---+---+
    // | C | C | C | C | A | R | U | B |  C - color, color mask = 0x00f0,
    // +---+---+---+---+---+---+---+---+  U - underline, R - reverse, B - bold, A - alternative character set

    // maximum color pairs = 16 due to implementation limit, violates X/Open Curses Issue 4 version 2
    typedef short chtype;

    typedef struct WINDOW
    {
        bool key_translation;
        char attributes;

        short max_x;
        short max_y;
        short cursor_x;
        short cursor_y;

        chtype* screen_buffer;
    } WINDOW;

    typedef struct SCREEN {

    } SCREEN;

    // Initialization

    #define FALSE 0
    #define TRUE 1

    #define OK 0
    #define ERR -1

    WINDOW* initscr(void);
    extern WINDOW* stdscr;

    // Parameters

    // Specification
    // https://pubs.opengroup.org/onlinepubs/009638999/toc.pdf

    //-------------------------------------------//
    //------           OUTPUT             -------//
    //-------------------------------------------//


    int waddch(WINDOW* win, const chtype ch);
    #define addch(ch) waddch(stdscr, ch)
    int mvwaddch(WINDOW* win, int y, int x, const chtype ch);
    #define mvaddch(y, x, ch) mvwaddch(stdscr, y, x, ch)

    // TODO: implement
    int wechochar(WINDOW* win, const chtype ch);
    #define echochar(ch) wechochar(stdscr, ch)

    // https://invisible-island.net/ncurses/man/curs_addchstr.3x.html
    int waddchstr(WINDOW *win, const chtype *chstr);
    #define addchstr(chstr) waddchstr(stdscr, chstr)
    int mvwaddchstr(WINDOW *win, int y, int x, const chtype *chstr);
    #define mvaddchstr(y, x, chstr) mvwaddchstr(stdscr, y, x, chstr)

    // https://invisible-island.net/ncurses/man/curs_beep.3x.html
    int beep(void);
    int flash(void);

    // https://invisible-island.net/ncurses/man/curs_bkgd.3x.html

    void wbkgdset(WINDOW *win, chtype ch);
    #define bkgdset(ch) wbkgdset(stdscr, ch)
    int wbkgd(WINDOW *win, chtype ch);
    #define bkgd(ch) wbkgd(stdscr, ch)
    chtype getbkgd(WINDOW *win);

    //https://invisible-island.net/ncurses/man/curs_bkgrnd.3x.html
       int bkgrnd( const cchar_t *wch);
       int wbkgrnd( WINDOW *win, const cchar_t *wch);
       void bkgrndset(const cchar_t *wch );
       void wbkgrndset(WINDOW *win, const cchar_t *wch);
       int getbkgrnd(cchar_t *wch);
       int wgetbkgrnd(WINDOW *win, cchar_t *wch);

    // https://invisible-island.net/ncurses/man/curs_border.3x.html
    int border(chtype ls, chtype rs, chtype ts, chtype bs,
        chtype tl, chtype tr, chtype bl, chtype br);
    int wborder(WINDOW *win, chtype ls, chtype rs,
        chtype ts, chtype bs, chtype tl, chtype tr,
        chtype bl, chtype br);
    int box(WINDOW *win, chtype verch, chtype horch);
    int hline(chtype ch, int n);
    int whline(WINDOW *win, chtype ch, int n);
    int vline(chtype ch, int n);
    int wvline(WINDOW *win, chtype ch, int n);
    int mvhline(int y, int x, chtype ch, int n);
    int mvwhline(WINDOW *, int y, int x, chtype ch, int n);
    int mvvline(int y, int x, chtype ch, int n);
    int mvwvline(WINDOW *, int y, int x, chtype ch, int n);

    // https://invisible-island.net/ncurses/man/curs_border_set.3x.html
int border_set(
          const cchar_t *ls, const cchar_t *rs,
          const cchar_t *ts, const cchar_t *bs,
          const cchar_t *tl, const cchar_t *tr,
          const cchar_t *bl, const cchar_t *br );
       int wborder_set(
          WINDOW *win,
          const cchar_t *ls, const cchar_t *rs,
          const cchar_t *ts, const cchar_t *bs,
          const cchar_t *tl, const cchar_t *tr,
          const cchar_t *bl, const cchar_t *br);
       int box_set(
          WINDOW *win,
          const cchar_t *verch,
          const cchar_t *horch);
       int hline_set(
          const cchar_t *wch, int n);
       int whline_set(
          WINDOW *win,
          const cchar_t *wch, int n);
       int mvhline_set(
          int y, int x,
          const cchar_t *wch, int n);
       int mvwhline_set(
          WINDOW *win,
          int y, int x,
          const cchar_t *wch, int n);
       int vline_set(
          const cchar_t *wch, int n);
       int wvline_set(
          WINDOW *win,
          const cchar_t *wch, int n);
       int mvvline_set(
          int y, int x,
          const cchar_t *wch, int n);
       int mvwvline_set(
          WINDOW *win,
          int y, int x,
          const cchar_t *wch, int n);

    // https://invisible-island.net/ncurses/man/curs_inopts.3x.html
        int cbreak(void);
       int nocbreak(void);
       int halfdelay(int tenths);
       int intrflush(WINDOW *win, bool bf);
       int meta(WINDOW *win, bool bf);
       int nodelay(WINDOW *win, bool bf);
       int raw(void);
       int noraw(void);
       void noqiflush(void);
       void qiflush(void);
       int notimeout(WINDOW *win, bool bf);
       void timeout(int delay);
       void wtimeout(WINDOW *win, int delay);
       int typeahead(int fd);

    //https://invisible-island.net/ncurses/man/curs_clear.3x.html
       int erase(void);
       int werase(WINDOW *win);
       int wclear(WINDOW *win);
       int clrtobot(void);
       int wclrtobot(WINDOW *win);
       int clrtoeol(void);
       int wclrtoeol(WINDOW *win);


    // https://invisible-island.net/ncurses/man/curs_outopts.3x.html
       int clearok(WINDOW *win, bool bf);
       int idlok(WINDOW *win, bool bf);
       void idcok(WINDOW *win, bool bf);
       void immedok(WINDOW *win, bool bf);
       int leaveok(WINDOW *win, bool bf);
       int setscrreg(int top, int bot);
       int wsetscrreg(WINDOW *win, int top, int bot);
       int scrollok(WINDOW *win, bool bf);
       int nl(void);
       int nonl(void);

       //https://invisible-island.net/ncurses/man/curs_overlay.3x.html

       int overlay(const WINDOW *srcwin, WINDOW *dstwin);
       int overwrite(const WINDOW *srcwin, WINDOW *dstwin);
       int copywin(const WINDOW *srcwin, WINDOW *dstwin, int sminrow,
             int smincol, int dminrow, int dmincol, int dmaxrow,
             int dmaxcol, int overlay);

// https://invisible-island.net/ncurses/man/curs_kernel.3x.html
              int def_prog_mode(void);
    int def_shell_mode(void);
       int reset_prog_mode(void);
       int reset_shell_mode(void);
       int resetty(void);
       int savetty(void);
       void getsyx(int y, int x);
       void setsyx(int y, int x);
       int ripoffline(int line, int (*init)(WINDOW *, int));
       int curs_set(int visibility);
       int napms(int ms);
    int printw(const char *, ...);
    int mvprintw(int row, int colums, const char *, ...);
    int refresh(void);
    int noecho(void);
    int echo(void);
    int clear(void);

    // https://invisible-island.net/ncurses/man/curs_terminfo.3x.html
    // TERMINAL *cur_term;

    //    const char * const boolnames[];
    //    const char * const boolcodes[];
    //    const char * const boolfnames[];
    //    const char * const numnames[];
    //    const char * const numcodes[];
    //    const char * const numfnames[];
    //    const char * const strnames[];
    //    const char * const strcodes[];
    //    const char * const strfnames[];

       int setupterm(const char *term, int filedes, int *errret);
       int setterm(const char *term);
       TERMINAL *set_curterm(TERMINAL *nterm);
       int del_curterm(TERMINAL *oterm);
       int restartterm(const char *term, int filedes, int *errret);

       char *tparm(const char *str, ...);
       int tputs(const char *str, int affcnt, int (*putc)(int));
       int putp(const char *str);

       int vidputs(chtype attrs, int (*putc)(int));
       int vidattr(chtype attrs);

       int mvcur(int oldrow, int oldcol, int newrow, int newcol);

       int tigetflag(const char *capname);
       int tigetnum(const char *capname);
       char *tigetstr(const char *capname);

       char *tiparm(const char *str, ...);

       //    https://invisible-island.net/ncurses/man/curs_util.3x.html
       const char *unctrl(chtype c);
       wchar_t *wunctrl(cchar_t *c);
       const char *keyname(int c);
       const char *key_name(wchar_t w);
       void filter(void);
       void nofilter(void);
       void use_env(bool f);
       void use_tioctl(bool f);
       int putwin(WINDOW *win, FILE *filep);
       WINDOW *getwin(FILE *filep);
       int delay_output(int ms);
       int flushinp(void);
    // https://invisible-island.net/ncurses/man/curs_delch.3x.html
              int delch(void);
       int wdelch(WINDOW *win);
       int mvdelch(int y, int x);
       int mvwdelch(WINDOW *win, int y, int x);

       // https://invisible-island.net/ncurses/man/curs_initscr.3x.html

       int endwin(void);
       bool isendwin(void);
    //    SCREEN *newterm(const char *type, FILE *outfd, FILE *infd);
    //    SCREEN *set_term(SCREEN *new);
    //    void delscreen(SCREEN* sp);

       // https://invisible-island.net/ncurses/man/curs_window.3x.html

       WINDOW *newwin(
             int nlines, int ncols,
             int begin_y, int begin_x);
       int delwin(WINDOW *win);
       int mvwin(WINDOW *win, int y, int x);
       WINDOW *subwin(WINDOW *orig,
             int nlines, int ncols,
             int begin_y, int begin_x);
       WINDOW *derwin(WINDOW *orig,
             int nlines, int ncols,
             int begin_y, int begin_x);
       int mvderwin(WINDOW *win, int par_y, int par_x);
       WINDOW *dupwin(WINDOW *win);
       void wsyncup(WINDOW *win);
       int syncok(WINDOW *win, bool bf);
       void wcursyncup(WINDOW *win);
       void wsyncdown(WINDOW *win);

       // https://invisible-island.net/ncurses/man/curs_refresh.3x.html
       int wrefresh(WINDOW *win);
       int wnoutrefresh(WINDOW *win);
       int doupdate(void);
       int redrawwin(WINDOW *win);
       int wredrawln(WINDOW *win, int beg_line, int num_lines);

// https://invisible-island.net/ncurses/man/curs_getyx.3x.html

       void getyx(WINDOW *win, int y, int x);
       void getparyx(WINDOW *win, int y, int x);
       void getbegyx(WINDOW *win, int y, int x);
        int getmaxy(WINDOW* window);
        int getmaxx(WINDOW* window);

     #define getmaxyx(win,y,x) (y = getmaxy(win), x = getmaxx(win))

    // https://invisible-island.net/ncurses/man/curs_getch.3x.html
       int wgetch(WINDOW *win);
       int mvgetch(int y, int x);
       int mvwgetch(WINDOW *win, int y, int x);
       int ungetch(int ch);
       int has_key(int ch);

       //https://invisible-island.net/ncurses/man/curs_getstr.3x.html
            int getstr(char *str);
       int getnstr(char *str, int n);
       int wgetstr(WINDOW *win, char *str);
       int wgetnstr(WINDOW *win, char *str, int n);
       int mvgetstr(int y, int x, char *str);
       int mvwgetstr(WINDOW *win, int y, int x, char *str);
       int mvgetnstr(int y, int x, char *str, int n);
       int mvwgetnstr(WINDOW *, int y, int x, char *str, int n);
        // https://invisible-island.net/ncurses/man/curs_inch.3x.html
       chtype inch(void);
       chtype winch(WINDOW *win);
       chtype mvinch(int y, int x);
       chtype mvwinch(WINDOW *win, int y, int x);

// https://invisible-island.net/ncurses/man/curs_inchstr.3x.html
int inchstr(chtype *chstr);
       int inchnstr(chtype *chstr, int n);
       int winchstr(WINDOW *win, chtype *chstr);
       int winchnstr(WINDOW *win, chtype *chstr, int n);
       int mvinchstr(int y, int x, chtype *chstr);
       int mvinchnstr(int y, int x, chtype *chstr, int n);
       int mvwinchstr(WINDOW *win, int y, int x, chtype *chstr);
       int mvwinchnstr(WINDOW *win, int y, int x, chtype *chstr, int n);

// https://invisible-island.net/ncurses/man/curs_instr.3x.html
          int instr(char *str);
       int innstr(char *str, int n);
       int winstr(WINDOW *win, char *str);
       int winnstr(WINDOW *win, char *str, int n);
       int mvinstr(int y, int x, char *str);
       int mvinnstr(int y, int x, char *str, int n);
       int mvwinstr(WINDOW *win, int y, int x, char *str);
       int mvwinnstr(WINDOW *win, int y, int x, char *str, int n);

    // https://invisible-island.net/ncurses/man/curs_insch.3x.html
        int insch(chtype ch);
       int winsch(WINDOW *win, chtype ch);
       int mvinsch(int y, int x, chtype ch);
       int mvwinsch(WINDOW *win, int y, int x, chtype ch);

    // https://invisible-island.net/ncurses/man/curs_insstr.3x.html

       int insstr(const char *str);
       int insnstr(const char *str, int n);
       int winsstr(WINDOW *win, const char *str);
       int winsnstr(WINDOW *win, const char *str, int n);
       int mvinsstr(int y, int x, const char *str);
       int mvinsnstr(int y, int x, const char *str, int n);
       int mvwinsstr(WINDOW *win, int y, int x, const char *str);
       int mvwinsnstr(WINDOW *win, int y, int x, const char *str, int n);

// https://invisible-island.net/ncurses/man/curs_touch.3x.html
     int touchwin(WINDOW *win);
       int touchline(WINDOW *win, int start, int count);
       int untouchwin(WINDOW *win);
       int wtouchln(WINDOW *win, int y, int n, int changed);
       bool is_linetouched(WINDOW *win, int line);
       bool is_wintouched(WINDOW *win);

     //  https://invisible-island.net/ncurses/man/curs_move.3x.html

    int wmove(WINDOW *win, int y, int x);
    int move(int y, int x);
// https://invisible-island.net/ncurses/man/curs_addstr.3x.html
        int addstr(const char *str);
       int addnstr(const char *str, int n);
       int waddstr(WINDOW *win, const char *str);
       int waddnstr(WINDOW *win, const char *str, int n);
       int mvaddstr(int y, int x, const char *str);
       int mvaddnstr(int y, int x, const char *str, int n);
       int mvwaddstr(WINDOW *win, int y, int x, const char *str);
       int mvwaddnstr(WINDOW *win, int y, int x, const char *str, int n);
// https://invisible-island.net/ncurses/man/curs_pad.3x.html
       WINDOW *newpad(int nlines, int ncols);
       WINDOW *subpad(WINDOW *orig, int nlines, int ncols,
             int begin_y, int begin_x);
       int prefresh(WINDOW *pad, int pminrow, int pmincol,
             int sminrow, int smincol, int smaxrow, int smaxcol);
       int pnoutrefresh(WINDOW *pad, int pminrow, int pmincol,
             int sminrow, int smincol, int smaxrow, int smaxcol);
       int pechochar(WINDOW *pad, chtype ch);
       int pecho_wchar(WINDOW *pad, const cchar_t *wch);
 // https://invisible-island.net/ncurses/man/curs_scr_dump.3x.html
       int scr_dump(const char *filename);
       int scr_restore(const char *filename);
       int scr_init(const char *filename);
       int scr_set(const char *filename);
// https://invisible-island.net/ncurses/man/curs_scroll.3x.html
        int scroll(WINDOW *win);
       int scrl(int n);
       int wscrl(WINDOW *win, int n);

       // https://invisible-island.net/ncurses/man/curs_slk.3x.html
     int slk_init(int fmt);

       int slk_set(int labnum, const char *label, int fmt);
       int slk_wset(int labnum, const wchar_t *label, int fmt);

       char *slk_label(int labnum);

       int slk_refresh(void);
       int slk_noutrefresh(void);
       int slk_clear(void);
       int slk_restore(void);
       int slk_touch(void);

       int slk_attron(const chtype attrs);
       int slk_attroff(const chtype attrs);
       int slk_attrset(const chtype attrs);

       int slk_color(short pair);

    //https://invisible-island.net/ncurses/man/curs_termcap.3x.html
        extern char PC;
       extern char * UP;
       extern char * BC;
       extern short ospeed;

       int tgetent(char *bp, const char *name);
       int tgetflag(const char *id);
       int tgetnum(const char *id);
       char *tgetstr(const char *id, char **area);
       char *tgoto(const char *cap, int col, int row);

    // Positioning

    int keypad(WINDOW *, bool);
    int getstr_(char *, int);

    // Input
    int getch(void);

    // Settings
    #define getstr(str) getstr_(str, sizeof(str));


    //-------------------------------------------//
    //------         ATTRIBUTES           -------//
    //-------------------------------------------//

    #define A_NORMAL     0x0000
    #define A_BOLD       0x0100
    #define A_UNDERLINE  0x0200
    #define A_REVERSE    0x0400
    #define A_DIM        A_BOLD
    #define A_ALTCHARSET 0x0800

    // Not supported due to space optimization (2-byte chtype)
    #define A_PROTECT    0x00
    #define A_INVIS      0x00
    #define A_STANDOUT   0x00
    #define A_BLINK      0x00

    #define A_CHARTEXT        0x00ff
    #define A_CHARTEXT_OFFSET 0

    #define A_COLOR_MASK 0xf0
    #define A_COLOR_OFFSET 4

    #define A_ATTRIBUTES_OFFSET 8

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
    // | - | - | - | - | - | - | - | - | character
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

    // https://invisible-island.net/ncurses/man/default_colors.3x.html
    int use_default_colors(void);
    int assume_default_colors(int fg, int bg);

    //-------------------------------------------//
    //------         TERMINFO             -------//
    //-------------------------------------------//

    // https://invisible-island.net/ncurses/man/curs_termattrs.3x.html
    int baudrate(void);
    char erasechar(void);
    bool has_ic(void);
    bool has_il(void);
    char killchar(void);
    char *longname(void);
    chtype termattrs(void);
    char *termname(void);




#if defined(__cplusplus)
}
#endif // __cplusplus
