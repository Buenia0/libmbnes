#!/bin/bash

if [[ ! -f "libmbNES.a" ]]; then
	echo "Run this script from the directory where you built libmbNES."
	exit 1
fi

mkdir -p dist

if [ -d "mbNES-SDL2" ]; then
	for lib in $(ldd mbNES-SDL2/mbNES-SDL2.exe | grep mingw | sed "s/.*=> //" | sed "s/(.*)//"); do
		cp "${lib}" dist
	done
	cp mbNES-SDL2/mbNES-SDL2.exe dist
fi