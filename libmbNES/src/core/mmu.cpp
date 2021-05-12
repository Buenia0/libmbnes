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

#include "mmu.h"
using namespace nes;
using namespace std;

namespace nes
{
    MMU::MMU()
    {

    }

    MMU::~MMU()
    {

    }

    void MMU::init()
    {
	cout << "MMU::Initialized" << endl;
    }

    void MMU::shutdown()
    {
	rom.clear();
	cout << "MMU::Shutting down..." << endl;
    }

    bool MMU::loadROM(vector<uint8_t> data)
    {
	if (data.empty())
	{
	    cout << "Error: could not load ROM" << endl;
	    return false;
	}

	if (data.size() < 16)
	{
	    cout << "Error: invalid size" << endl;
	    return false;
	}

	if (!checknesheader(data))
	{
	    cout << "Error: invalid iNES file" << endl;
	    return false;
	}

	bool isnes2 = (((data[7] >> 2) & 0x3) == 2);

	// TODO: NES 2.0 support
	if (isnes2)
	{
	    cout << "Error: NES 2.0 is unimplemented" << endl;
	    return false;
	}

	uint16_t mapperLo = (data[6] >> 4);
	uint16_t mapperHi = (data[7] >> 4);

	uint16_t mapperNum = ((mapperHi << 8) | mapperLo);

	// TODO: Implement other NES mappers
	if (mapperNum != 0)
	{
	    cout << "Invalid mapper of " << dec << (int)mapperNum << endl;
	    return false;
	}

	// Fetch size of PRG ROM (in 16 KB units)
	int prgRomSize = data[4];

	// TODO: Implement PRG ROM sizes larger than 16KB
	if (prgRomSize != 1)
	{
	    cout << "Invalid PRG ROM size of " << dec << prgRomSize << endl;
	    return false;
	}

	// PRG ROM starts after the 16-byte header
	// and (if present) the 512-byte trainer
	size_t romOffs = 16;

	// Detect any trainer data in the ROM...
	bool istrainer = ((data[6] >> 2) & 0x1);

	// ...and skip over it if it's there
	if (istrainer)
	{
	    romOffs += 512;
	}

	// Set offset to beginning of PRG ROM data...
	auto romBegin = data.begin() + romOffs;

	// ...calculate the PRG ROM size...
	int romSize = (prgRomSize * 16 * 1024);

	// ...and copy the appropriate data over
	rom = vector<uint8_t>(romBegin, (romBegin + romSize));

	cout << "Size of ROM: " << dec << (int)(rom.size() >> 10) << " KB" << endl;
	return true;
    }

    bool MMU::checknesheader(vector<uint8_t> data)
    {
	bool result = (data[0] == 0x4E);
	result &= (data[1] == 0x45);
	result &= (data[2] == 0x53);
	result &= (data[3] == 0x1A);
	return result;
    }
}