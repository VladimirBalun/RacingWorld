#
# Copyright 2018 Vladimir Balun
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required (VERSION 3.10)

project (RacingWorld)
set (CMAKE_CXX_STANDARD 17)

file (GLOB_RECURSE GRAPHICS_SRC "Graphics/*.hpp" "Graphics/*.cpp")
file (GLOB_RECURSE GR_SRC "Graphics/SceneGraph/*.hpp" "Graphics/SceneGraph/*.cpp")
file (GLOB_RECURSE UTILS_SRC "Utils/*.hpp" "Utils/*.cpp")
file (GLOB_RECURSE MATH_SRC "Math/*.hpp" "Math/*.cpp")
file (GLOB_RECURSE MEMORY_SRC "Memory/*.hpp" "Memory/*.cpp")
file (GLOB_RECURSE SYSTEM_SRC "System/*.hpp" "System/*.cpp")
file (GLOB_RECURSE NETWORK_SRC "Network/*.hpp" "Network/*.cpp")

source_group ("" FILES Main.cpp)
source_group (Graphics FILES ${GRAPHICS_SRC})
source_group (Utils FILES ${UTILS_SRC})
source_group (Math FILES ${MATH_SRC})
source_group (Memory FILES ${MEMORY_SRC})
source_group (System FILES ${SYSTEM_SRC})
source_group (Network FILES ${NETWORK_SRC})

add_executable (${PROJECT_NAME} WIN32 
    Main.cpp
    ${GRAPHICS_SRC} 
    ${UTILS_SRC}
    ${MATH_SRC}
    ${MEMORY_SRC}
    ${SYSTEM_SRC}
    ${NETWORK_SRC}
)
target_link_libraries (${PROJECT_NAME} wsock32.lib opengl32.lib glu32.lib)
target_include_directories (${PROJECT_NAME} PRIVATE ${PROJECT_DEPENDENCIES_DIR}/OpenGL/Include)
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_BIN_DIR})
