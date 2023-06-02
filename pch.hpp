//     Digital Thermostat - simulate thermostat
//     Copyright (C) 2023  Akshay Bansod <akshayb@gmx.com>

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <algorithm>

// more stl headers here


// build configuration specific code
#ifndef NDEBUG
    // logging enabled in debug mode onlu
    #define LG(...) std::cout << __VA_ARGS__


#else
    #define LG(...)
#endif


// platform specific code
#ifdef _WIN32

// add apple specific code here
#elif defined(_APPLE)

// add linux specific code here
#elif defined(_LINUX)

#endif
