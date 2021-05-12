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

#ifndef LIBMBNES_MMU
#define LIBMBNES_MMU

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include "libmbnes_api.h"
#include "utils.h"
using namespace std;

namespace nes
{
    class LIBMBNES_API MMU
    {
	public:
	    MMU();
	    ~MMU();

	    void init();
	    void shutdown();

	    vector<uint8_t> rom;

	    bool loadROM(vector<uint8_t> data);

	private:
	    bool checknesheader(vector<uint8_t> data);
    };
};

#endif // LIBMBNES_MMU