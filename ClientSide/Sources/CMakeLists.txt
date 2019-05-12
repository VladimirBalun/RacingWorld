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

find_package(Boost 1.60 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file (GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

foreach (FILE ${SOURCES})
    get_filename_component (PARENT_DIR "${FILE}" DIRECTORY)
    string (REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string (REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set (GROUP "${GROUP}")
    elseif ("${FILE}" MATCHES ".*\\.hpp")
       set (GROUP "${GROUP}")
    endif ()

    source_group ("${GROUP}" FILES "${FILE}")
endforeach ()

add_executable (${PROJECT_NAME} WIN32 ${SOURCES})
target_link_libraries (${PROJECT_NAME} wsock32.lib opengl32.lib)
target_include_directories (${PROJECT_NAME} PRIVATE ${PROJECT_DEPENDENCIES_DIR}/OpenGL/Include)
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Game")
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BIN_DIR})
set_target_properties (${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_BIN_DIR})

include (CPack.cmake)