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

#include "libmbnes.h"
using namespace nes;
using namespace std;

namespace nes
{
    NESCore::NESCore()
    {
	coremmu = make_unique<MMU>();
    }

    NESCore::~NESCore()
    {

    }

    void NESCore::init()
    {
	coremmu->init();
	cout << "mbNES::Initialized" << endl;
    }

    void NESCore::shutdown()
    {
	if (front != NULL)
	{
	    front->shutdown();
	}

	coremmu->shutdown();

	cout << "mbNES::Shutting down..." << endl;
    }

    void NESCore::setfrontend(mbNESFrontend *cb)
    {
	front = cb;
	cout << "Setting frontend..." << endl;
    }

    bool NESCore::loadROM(string filename)
    {
	cout << "mbNES::Loading ROM " << filename << "..." << endl;

	if (front != NULL)
	{
	    return coremmu->loadROM(front->loadfile(filename));
	}

	return false;
    }

    bool NESCore::initcore()
    {
	init();

	if (front != NULL)
	{
	    front->init();
	}

	return true;
    }

    void NESCore::runcore()
    {
	// TODO: Implement main loop
	return;
    }

    void NESCore::runapp()
    {
	if (front != NULL)
	{
	    front->runapp();
	}
    }
};