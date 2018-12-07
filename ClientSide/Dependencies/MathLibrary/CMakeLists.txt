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

project (MathLibrary)

file (GLOB_RECURSE SOURCES "Sources/*.cpp")
file (GLOB_RECURSE HEADERS "Include/*.h" "Include/*.hpp") 

source_group ("Headers" FILES ${HEADERS})
source_group ("Sources" FILES ${SOURCES})

set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library (${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_include_directories (${PROJECT_NAME} PRIVATE ./Include/Math)
set_target_properties (${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../../Bin)
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ../../../Bin)
set_target_properties (${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ../../../Bin)
set_target_properties (${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../Libs)
set_target_properties (${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ../../../Libs)
set_target_properties (${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ../../../Libs)
set_target_properties (${PROJECT_NAME} PROPERTIES FOLDER "Libraries")
