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

cmake_minimum_required (VERSION 3.8)

include (${PROJECT_CMAKE_DIR}/ProjectConfiguration.cmake)

project (${GAME_NAME})

file (GLOB_RECURSE GRAPHICS_SRC "Graphics/*.hpp" "Graphics/*.cpp")
file (GLOB_RECURSE UTILS_SRC "Utils/*.hpp" "Utils/*.cpp")
file (GLOB_RECURSE PLATFORMS_SRC "Platforms/*.hpp" "Platforms/*.cpp")
file (GLOB_RECURSE PLATFORMS_WINDOW_SYSTEM_SRC "Platforms/WindowSystem/*.hpp" "Platforms/WindowSystem/*.cpp")
file (GLOB_RECURSE PLATFORMS_NETWORK_SRC "Platforms/Network/*.hpp" "Platforms/Network/*.cpp")

source_group ("Graphics" FILES ${GRAPHICS_SRC})
source_group ("Utils" FILES ${UTILS_SRC})
source_group ("Platforms" FILES ${PLATFORMS_SRC})
source_group ("WindowSystem" FILES ${PLATFORMS_WINDOW_SYSTEM_SRC})
source_group ("Network" FILES ${PLATFORMS_NETWORK_SRC})

add_executable (${PROJECT_NAME} WIN32 ${GRAPHICS_SRC} ${UTILS_SRC} ${PLATFORMS_SRC} ${PLATFORMS_WINDOW_SYSTEM_SRC} ${PLATFORMS_NETWORK_SRC})
target_link_libraries (${PROJECT_NAME} wsock32.lib opengl32.lib glu32.lib ${PROJECT_LIBS_DIR}/${MATH_LIBRARY_NAME}.lib ${PROJECT_LIBS_DIR}/${MEMORY_LIBRARY_NAME}.lib)
target_include_directories (${PROJECT_NAME} PRIVATE 
    ${PROJECT_DEPENDENCIES_DIR}/OpenGL/Include 
    ${PROJECT_DEPENDENCIES_DIR}/${MATH_LIBRARY_NAME}/Include
    ${PROJECT_DEPENDENCIES_DIR}/${MEMORY_LIBRARY_NAME}/Include
)
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Game")
add_dependencies (${PROJECT_NAME} ${MATH_LIBRARY_NAME}.lib ${MEMORY_LIBRARY_NAME}.lib)
