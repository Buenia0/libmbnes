cmake_minimum_required(VERSION 3.15)
project(libmbnes)

# Require C++17 (and position independent code)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_SDL2 "Enables the SDL2 frontend (requires SDL2)." ON)

set(LIBMBNES_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libmbNES/include")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libmbNES/include/libmbNES")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(LIBMBNES_API_HEADERS
	libmbNES/include/libmbNES/libmbnes_api.h
	libmbNES/include/libmbNES/utils.h
	libmbNES/include/libmbNES/mmu.h
	libmbNES/include/libmbNES/libmbnes.h)

set(LIBMBNES
	libmbNES/src/core/mmu.cpp
	libmbNES/src/core/libmbnes.cpp)

if (BUILD_SDL2 STREQUAL "ON")
	message(STATUS "Building mbNES-SDL2...")
	add_subdirectory(mbNES-SDL2)
endif()

add_library(mbNES ${LIBMBNES} ${LIBMBNES_API_HEADERS})
target_include_directories(mbNES PUBLIC ${LIBMBNES_INCLUDE_DIR})
target_compile_definitions(mbNES PRIVATE LIBMBNES_STATIC=1 _CRT_SECURE_NO_WARNINGS=1)
add_library(libmbNES ALIAS mbNES)

if (WIN32)
    message(STATUS "Operating system is Windows.")
    if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
	target_compile_options(mbNES PRIVATE -Wall)
	message(STATUS "Compiler is MinGW.")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
	message(WARNING "MSVC support is HIGHLY experimental, and may not even compile correctly, so be EXTREMELY careful here!")
	target_compile_options(mbNES PRIVATE /W4)
	message(STATUS "Compiler is MSVC.")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	message(WARNING "Clang support on Windows is HIGHLY experimental, and may not even compile correctly, so be EXTREMELY careful here!")
	target_compile_options(mbNES PRIVATE -Wall)
	message(STATUS "Compiler is Clang.")
    else()
	message(SEND_ERROR "Compiler not supported.")
	return()
    endif()
elseif(UNIX AND NOT APPLE)
    message(STATUS "Operating system is Linux.")
    if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
	target_compile_options(mbNES PRIVATE -Wall)
	message(STATUS "Compiler is GCC.")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	target_compile_options(mbNES PRIVATE -Wall)
	message(STATUS "Compiler is Clang.")
    else()
	message(SEND_ERROR "Compiler not supported.")
	return()
    endif()
elseif(APPLE)
    message(STATUS "Operating system is Mac.")
    if (CMAKE_CXX_COMPILER_ID STREQUAL AppleClang)
	target_compile_options(mbNES PRIVATE -Wall)
	message(STATUS "Compiler is AppleClang.")
    else()
	message(SEND_ERROR "Compiler not supported.")
	return()
    endif()
else()
    message(SEND_ERROR "Operating system not supported.")
    return()
endif()
