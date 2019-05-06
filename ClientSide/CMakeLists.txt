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
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (PROJECT_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build)
set (PROJECT_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set (PROJECT_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
set (PROJECT_TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Tests)
set (PROJECT_BENCHMARKS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Benchmarks)
set (PROJECT_DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies)

enable_testing()

add_subdirectory (Sources)
add_subdirectory (Tests)
add_subdirectory (Benchmarks)
