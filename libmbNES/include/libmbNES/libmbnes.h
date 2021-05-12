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

#ifndef LIBMBNES_CORE
#define LIBMBNES_CORE

#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include "utils.h"
#include "mmu.h"
using namespace nes;
using namespace std;

namespace nes
{
    class LIBMBNES_API NESCore
    {
	public:
	    NESCore();
	    ~NESCore();

	    unique_ptr<MMU> coremmu;

	    mbNESFrontend *front = NULL;

	    bool initcore();
	    bool loadROM(string filename);

	    void setfrontend(mbNESFrontend *cb);

	    void init();
	    void shutdown();

	    void runcore();
	    void runapp();
    };
};

#endif // LIBMBNES_CORE