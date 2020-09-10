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

#include "msos/libc/printf.hpp"

#include <cstring>
#include <unistd.h>

std::vector<PrintfCall>& printf_history()
{
    static std::vector<PrintfCall> calls;
    return calls;
}

int _printf(const char* format, ...)
{
    static_cast<void>(format);
    va_list arg;
    va_start (arg, format);
    UsartWriter writer{};
    int done = __vfprintf_(writer, STDOUT_FILENO, format, arg, 0);
    va_end (arg);
    return done;
}

namespace
{
    FlushHistory flush_call = {
        .file = nullptr,
        .counter = 0
    };

    TcGetAttrHistory tcgetattr_call = {
        .fd = 0,
        .termio = {}
    };

    TcSetAttrHistory tcsetattr_call = {
        .fd = 0,
        .termio = {},
        .action = 0
    };
}

int _fflush(FILE * stream)
{
    if (flush_call.file == stream)
    {
        ++flush_call.counter;
    }
    else
    {
        flush_call.file = stream;
        flush_call.counter = 1;
    }
    return 0;
}


FlushHistory last_flush()
{
    return flush_call;
}

void clear_flush_counter()
{
    flush_call = {
        .file = nullptr,
        .counter = 0
    };
}

void set_tcgetattr(struct termios *termios_p)
{
    std::memcpy(&tcgetattr_call.termio, termios_p, sizeof(termios));
}


int _tcgetattr(int fildes, struct termios *termios_p)
{
    tcgetattr_call.fd = fildes;
    std::memcpy(termios_p, &tcgetattr_call.termio, sizeof(termios));
    return 0;
}

int _tcsetattr(int fildes, int action, struct termios *termios_p)
{
    tcsetattr_call.fd = fildes;
    tcsetattr_call.action = action;
    std::memcpy(&tcsetattr_call.termio, termios_p, sizeof(termios));
    return 0;
}

TcGetAttrHistory last_tcgetattr()
{
    return tcgetattr_call;
}

void clear_tcgetattr()
{
    tcgetattr_call = {
        .fd = 0,
        .termio = {}
    };
}

TcSetAttrHistory last_tcsetattr()
{
    return tcsetattr_call;
}

void clear_tcsetattr()
{
    tcsetattr_call = {
        .fd = 0,
        .termio = {},
        .action = 0
    };
}
