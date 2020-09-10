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

#include <string_view>

#include <unistd.h>

#include "msos/libc/printf.hpp"

#include "curses.h"

class OutputShould : public mstest::Test
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

MSTEST_F(OutputShould, PrintToStdout)
{
    int a = 10;
    const char* b = "Some value";
    const char* expected_text = "Some print: 10, Some value";
    printw("Some print: %d, %s", a, b);
    mstest::expect_false(printf_history().empty());
    auto last_call = printf_history().back();
    mstest::expect_eq(std::string_view(last_call.data), expected_text);

    printw("Other");
    last_call = printf_history().back();
    mstest::expect_eq(std::string_view(last_call.data), "Other");

}

MSTEST_F(OutputShould, FlushStdoutWithRefresh)
{
    refresh();
    mstest::expect_eq(last_flush().counter, 1);
    mstest::expect_eq(last_flush().file, stdout);
    refresh();
    mstest::expect_eq(last_flush().counter, 2);
    mstest::expect_eq(last_flush().file, stdout);
}

MSTEST_F(OutputShould, DisableEcho)
{
    noecho();
    mstest::expect_eq(last_tcsetattr().fd, STDIN_FILENO);
    mstest::expect_false(last_tcsetattr().termio.c_lflag & ECHO);
    mstest::expect_eq(last_tcsetattr().action, TCSANOW);
}

MSTEST_F(OutputShould, EnableEcho)
{
    echo();
    mstest::expect_eq(last_tcsetattr().fd, STDIN_FILENO);
    mstest::expect_true(last_tcsetattr().termio.c_lflag & ECHO);
    mstest::expect_eq(last_tcsetattr().action, TCSANOW);
}

std::string string_as_number(std::string_view data)
{
    std::stringstream ss;
    size_t i = 0;
    ss << "(";
    for (auto b : data)
    {
        ss << static_cast<int>(b);
        if (++i < data.size())
        {
            ss << ", ";
        }
    }
    ss << ")";
    return ss.str();
}

MSTEST_F(OutputShould, Clear)
{
    clear();
    auto last_call = printf_history().back();
    mstest::expect_eq(last_call.str(), "\033[H\033[J", &string_as_number);
}

MSTEST_F(OutputShould, InitColorPair)
{
    mstest::expect_eq(0, init_pair(1, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(1, init_pair(10, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(-1, init_pair(10, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(2, init_pair(100, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(3, init_pair(2, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(4, init_pair(3, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(5, init_pair(4, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(6, init_pair(5, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(7, init_pair(6, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(8, init_pair(7, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(9, init_pair(8, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(10, init_pair(9, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(11, init_pair(15, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(12, init_pair(11, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(13, init_pair(18, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(14, init_pair(120, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(15, init_pair(30, COLOR_BLACK, COLOR_RED));
    mstest::expect_eq(-1, init_pair(1, COLOR_BLACK, COLOR_RED));
}
