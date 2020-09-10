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

#include <stdarg.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <string_view>

#include <termio.h>

#include "msos/usart_printer.hpp"

struct PrintfCall
{
    int fd;
    char data[1000];

    std::string_view str() const
    {
        return std::string_view(data);
    }
};

std::vector<PrintfCall>& printf_history();

struct FlushHistory
{
    FILE* file;
    int counter;
};

struct TcGetAttrHistory
{
    int fd;
    struct termios termio;
};

struct TcSetAttrHistory
{
    int fd;
    struct termios termio;
    int action;
};

FlushHistory last_flush();
void clear_flush_counter();

TcGetAttrHistory last_tcgetattr();
void clear_tcgetattr();

TcSetAttrHistory last_tcsetattr();
void clear_tcsetattr();

template <typename T>
int __vfprintf_(T& writer, int fd, const char* format, va_list argptr,
                    unsigned int mode_flags)
{
    static_cast<void>(writer);
    static_cast<void>(mode_flags);
    printf_history().push_back(PrintfCall{
        .fd = fd,
        .data = {}
    });

    vsnprintf(printf_history().back().data, 1000, format, argptr);

    return 0;
}

int _printf(const char* format, ...);
int _fflush(FILE * stream);

int _tcgetattr(int fildes, struct termios *termios_p);
int _tcsetattr(int fildes, int modifier, struct termios *termios_p);

void set_tcgetattr(struct termios *termios_p);

#define printf _printf
#define fflush _fflush
#define tcgetattr _tcgetattr
#define tcsetattr _tcsetattr
