#     Digital Thermostat - simulate thermostat
#     Copyright (C) 2023  Akshay Bansod <akshayb@gmx.com>

#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.

#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.

#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <https://www.gnu.org/licenses/>.

set(imgui_path "deps/imgui")

file(GLOB imgui_sources ${imgui_path}/*.cpp)

# imgui backends
list(APPEND imgui_sources
    ${imgui_path}/backends/imgui_impl_glfw.cpp
    ${imgui_path}/backends/imgui_impl_opengl3.cpp
)


add_library(imgui ${imgui_sources})
target_include_directories(imgui PUBLIC ${imgui_path} ${imgui_path}/backends)
target_link_libraries(imgui PRIVATE glfw)
set_target_properties(imgui PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/deps/imgui"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/deps/imgui"
    BINARY_DIR "${CMAKE_BINARY_DIR}/deps/imgui"
)
