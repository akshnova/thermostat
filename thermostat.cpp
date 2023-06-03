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



#include "pch.hpp"
#include <glad/glad.h>

#include "windowing/window.hpp"
#include "widgets/thermoWidgets.hpp"

const char* title = "ThermoStat simulation";

class imguiHandler : public window::inputHandler, public imguiLayer {

public:
    float sliderV=0.0f;
    core mainCore;
    thermoStat thermo;

    virtual void imguiRender() override {

        // imgui ui script
        ImGui::Begin("Stats", NULL, ImGuiWindowFlags_NoMove);
        ImGui::SetWindowSize(ImVec2(0, 0));
        ImGui::SetWindowPos(ImVec2(0, 30));
        if(!mainCore.changed) mainCore.changed = ImGui::VSliderFloat("env", ImVec2(40, 400), &mainCore.env, -10.0f, 110.0f); 
        else ImGui::VSliderFloat("env", ImVec2(40, 400), &mainCore.env, -10.0f, 110.0f);
        ImGui::SameLine();
        ImGui::VSliderInt("cooling", ImVec2(40, 400), &mainCore.isCooling, 0, 1); ImGui::SameLine();
        ImGui::VSliderInt("heating", ImVec2(40, 400), &mainCore.isHeating, 0, 1); ImGui::SameLine();
        ImGui::VSliderFloat("temp", ImVec2(40, 400), &mainCore.temp, -10.0f, 110.0f); ImGui::SameLine();
        ImGui::End();

        ImGui::Begin("ThermoStat", NULL, ImGuiWindowFlags_NoMove);
        ImGui::SetWindowSize(ImVec2(0, 0));
        ImGui::SetWindowPos(ImVec2(370, 0));
        ImGui::Checkbox("Enable", &thermo.active);
        // ImGui::LabelText("Required Temperature", "");
        ImGui::VSliderFloat("Required Temp",  ImVec2(40, 400), &thermo.reqTem, -10.0f, 110.0f);
        ImGui::End();

    };

    void inputLoop(){
        // processs inputs
        while (display->run)
        {
            processEvents();
            mainCore.simulate();
        }   
    };
    
    void resized() override { glViewport(0, 0, width, height); }
};

int main(){

    window::windowConfig cfg{
        .width = 500,
        .height = 500,
        .title = title,
        .resizable = false,
        .handler = &window::defaultInputHandler
    };


    window* win = new window(cfg);
    imguiHandler hand;
    win->setActive();
    win->switchHandler(&hand);

    envMod en;
    hand.mainCore.modifiers.push_back(&en);
    hand.mainCore.modifiers.push_back(&hand.thermo);
    win->layers.push_back(&hand);
    hand.inputLoop();

    return 0;
};
