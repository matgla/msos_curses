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

#include <mstest/mstest.hpp>

#include "curses.h"

#include "msos/libc/printf.hpp"

class ColorsShould : public mstest::Test
{
public:
    void teardown() override
    {
        printf_history().clear();
        clear_flush_counter();
        clear_tcgetattr();
        clear_tcsetattr();
    }
};

MSTEST_F(ColorsShould, InitColorPairs)
{
    mstest::expect_eq(OK, init_pair(1, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(OK, init_pair(2, COLOR_GREEN, COLOR_RED));
    mstest::expect_eq(OK, init_pair(3, COLOR_CYAN, COLOR_BLUE));
    mstest::expect_eq(OK, init_pair(8, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(OK, init_pair(9, COLOR_BLACK, COLOR_RED));

    short fg, bg;
    mstest::expect_eq(OK, pair_content(1, &fg, &bg));
    mstest::expect_eq(fg, COLOR_BLACK);
    mstest::expect_eq(bg, COLOR_RED);
    mstest::expect_eq(OK, pair_content(3, &fg, &bg));
    mstest::expect_eq(fg, COLOR_CYAN);
    mstest::expect_eq(bg, COLOR_BLUE);
}

MSTEST_F(ColorsShould, FailWhenPairIdOutOfRange)
{
    mstest::expect_eq(ERR, init_pair(0, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(ERR, init_pair(COLOR_PAIRS, COLOR_BLACK, COLOR_RED));
}

MSTEST_F(ColorsShould, FailWhenGetPairOutOfRange)
{
    short foreground;
    short background;
    mstest::expect_eq(ERR, pair_content(0, &foreground, &background));
    mstest::expect_eq(ERR, pair_content(COLOR_PAIRS, &foreground, &background));
}

