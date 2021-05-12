/*
    This file is part of libmbnes.
    Copyright (C) 2021 BueniaDev.

    libmbnes is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libmbnes is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libmbnes.  If not, see <https://www.gnu.org/licenses/>.
*/

    
#ifndef LIBMBNES_API_H
#define LIBMBNES_API_H

#if defined(_MSC_VER) && !defined(LIBMBNES_STATIC)
    #ifdef LIBMBNES_EXPORTS
        #define LIBMBNES_API __declspec(dllexport)
    #else
        #define LIBMBNES_API __declspec(dllimport)
    #endif // LIBMBNES_EXPORTS
#else
    #define LIBMBNES_API
#endif // _MSC_VER

#endif // LIBMBNES_API_H
