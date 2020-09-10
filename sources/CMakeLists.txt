# This file is part of MSOS project. This is simple OS for embedded development devices.
# Copyright (C) 2020 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

add_library(msos_curses)

target_sources(msos_curses
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/curses.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/curses.cpp
)

target_include_directories(msos_curses PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_options(msos_curses
    PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:${MSOS_CURSES_CXX_COMPILER_FLAGS}>
        $<$<COMPILE_LANGUAGE:C>:${MSOS_CURSES_C_COMPILER_FLAGS}>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
)

target_link_options(msos_curses
    PUBLIC
        ${MSOS_CURSES_LINKER_FLAGS}
)

target_link_libraries(msos_curses
    PRIVATE
        hal_flags
        msos_os_sys
        msos_libc
)
