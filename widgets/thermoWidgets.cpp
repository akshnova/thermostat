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

#include "thermoWidgets.hpp"
using namespace std::chrono;

float conduction = 0.01f;

void core::simulate()
{

    for(modifier* mod : modifiers) mod->eval(*this);

    temp += (env - temp) * conduction;
    if(isCooling) temp += (cooling - temp) * conduction;
    if(isHeating) temp += (heating - temp) * conduction;


    milliseconds now, delay;
    now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    delay = dT - (now - lastT);
    std::this_thread::sleep_for(delay);
    lastT = now;
}


void envMod::eval(core& cr){
    
    if(cr.changed) { base = cr.env; cr.changed = false; };

    float percent = 0.0f, newVal, diff;
    
    if (index == 9)
    {
        percent = ((float)rand() / (float)RAND_MAX) - 0.5f;
        newVal = base + range * percent;

        diff = (newVal - lastVal) / 10.0f;
        for (int index = 0; index < 10; index++)
            interpolations[index] = lastVal + index * diff;

        lastVal = newVal;
        index = 0;
    }

    // calculate the change in temperature

    cr.env = interpolations[index++];
};

void thermoStat::eval(core &cr)
{
    if(!active) return;

    if(cr.temp > reqTem) {
        cr.isCooling = true;
        cr.isHeating = false;
        cr.cooling  = -10.0f;
        cr.heating = 0.0f;
    }
    else{
        cr.isCooling = false;
        cr.isHeating = true;
        cr.cooling  = 0.0f;
        cr.heating = 110.f;
    }

}
