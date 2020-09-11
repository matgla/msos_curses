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

class AttributesShould : public mstest::Test
{
public:
    void setup() override
    {
        initscr();
        attrset(0);
    }
    void teardown() override
    {
        printf_history().clear();
        clear_flush_counter();
        clear_tcgetattr();
        clear_tcsetattr();
    }
};

MSTEST_F(AttributesShould, SetupStyle)
{
    WINDOW custom_window;
    wattrset(&custom_window, 0);
    mstest::expect_eq(custom_window.attributes, 0);
    mstest::expect_eq(stdscr->attributes, 0);

    attron(A_NORMAL);
    mstest::expect_eq(custom_window.attributes, 0);
    mstest::expect_eq(stdscr->attributes, A_NORMAL);
    wattron(&custom_window, A_NORMAL);
    mstest::expect_eq(custom_window.attributes, A_NORMAL);
    mstest::expect_eq(stdscr->attributes, A_NORMAL);
}

MSTEST_F(AttributesShould, SetupOnlyTargetedAttribute)
{
    WINDOW custom_window;
    wattrset(&custom_window, 0xF0);
    attrset(0xA0);

    attron(0x2);
    wattron(&custom_window, 0x4);
    mstest::expect_eq(custom_window.attributes, static_cast<char>(0xF4));
    mstest::expect_eq(stdscr->attributes, static_cast<char>(0xA2));

    attron(0x2);
    wattron(&custom_window, 0x4);
    mstest::expect_eq(custom_window.attributes, static_cast<char>(0xF4));
    mstest::expect_eq(stdscr->attributes, static_cast<char>(0xA2));
}

MSTEST_F(AttributesShould, TurnOffOnlyTargetedAttribute)
{
    WINDOW custom_window;
    wattrset(&custom_window, 0xFF);
    attrset(0xFF);

    attroff(0xF0);
    wattroff(&custom_window, 0xFF);
    mstest::expect_eq(custom_window.attributes, static_cast<int>(0x00));
    mstest::expect_eq(stdscr->attributes, static_cast<int>(0x0F));
}

MSTEST_F(AttributesShould, SetupColorCorrectly)
{
    WINDOW custom_window;
    wattrset(&custom_window, 0x0A);
    attrset(0x2B);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    wattron(&custom_window, COLOR_PAIR(1));

    mstest::expect_eq(custom_window.attributes, static_cast<int>(0x1A));
    mstest::expect_eq(stdscr->attributes, static_cast<int>(0x1B));

    color_set(2, NULL);
    wcolor_set(&custom_window, 3, NULL);
    mstest::expect_eq(custom_window.attributes, static_cast<int>(0x3A));
    mstest::expect_eq(stdscr->attributes, static_cast<int>(0X2B));
}

MSTEST_F(AttributesShould, SetStandout)
{
    WINDOW custom_window;
    wattrset(&custom_window, 0xFFFF2222);
    attrset(0xFFFF2222);

    standout();
    wstandout(&custom_window);

    mstest::expect_eq(custom_window.attributes, A_STANDOUT);
    mstest::expect_eq(stdscr->attributes, A_STANDOUT);
}

MSTEST_F(AttributesShould, SetStandend)
{
    WINDOW custom_window;
    wattrset(&custom_window, 0xFFFF2222);
    attrset(0xFFFF2222);

    standend();
    wstandend(&custom_window);

    mstest::expect_eq(custom_window.attributes, A_NORMAL);
    mstest::expect_eq(stdscr->attributes, A_NORMAL);
}

