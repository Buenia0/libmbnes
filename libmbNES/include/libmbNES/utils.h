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

#ifndef LIBMBNES_UTILS
#define LIBMBNES_UTILS

#include <iostream>
#include <cstdint>
#include <vector>
#include "libmbnes_api.h"
using namespace std;

namespace nes
{
    class LIBMBNES_API mbNESFrontend
    {
	public:
	    mbNESFrontend()
	    {

	    }

	    ~mbNESFrontend()
	    {

	    }

	    virtual bool init() = 0;
	    virtual void shutdown() = 0;
	    virtual void runapp() = 0;
	    virtual vector<uint8_t> loadfile(string filename) = 0;
    };
};

#endif // LIBMBNES_UTILS