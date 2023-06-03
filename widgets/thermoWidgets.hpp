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

#ifndef THERMO_WIDGETS_HPP
#define THERMO_WIDGET_HPP


#include "pch.hpp"
#include "imguiLayer/imguiLayer.hpp"
using namespace std::chrono;

class modifier;

class core {

    public:
    std::list<modifier*> modifiers;

    // temperature states of different parameters
    float env=0, temp=0.0f, cooling=0.0f, heating=0.0f;
    int isCooling = 0, isHeating = 0;
    bool changed = false;

    std::chrono::milliseconds lastT = duration_cast<milliseconds>(system_clock::now().time_since_epoch()), dT = std::chrono::milliseconds(100);

    void simulate();
};


struct modifier{
    virtual void eval(core& cr) = 0;
};

class envMod : public modifier{
public:
    float base = 25.0f, lastVal = 0.0f, interpolations[10], range = 10.0f;
    int index = 0;
    void eval(core& cr) override;
};

class thermoStat : public modifier{
public:
    bool active = false;
    float reqTem = 10.0f;
    void eval(core& cr) override;
};
#endif // THERMO_WIDGET_HPP
