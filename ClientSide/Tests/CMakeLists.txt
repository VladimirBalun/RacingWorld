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

project (RacingWorldUnitTests)

set (TESTS VectorsTest Vector2Test Vector3Test Vector4Test Matrix2x2Test Matrix3x3Test Matrix4x4Test)

foreach (TEST ${TESTS})
    add_executable (${TEST} ./Math/${TEST}.cpp)
    target_include_directories (${TEST} PRIVATE ${PROJECT_SOURCES_DIR}/Math)
    target_include_directories (${TEST} PRIVATE ${PROJECT_DEPENDENCIES_DIR}/Catch/Include)
    set_target_properties (${TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
    set_target_properties (${TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BIN_DIR})
    set_target_properties (${TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BIN_DIR})
    set_target_properties (${TEST} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_BIN_DIR})
    set_target_properties (${TEST} PROPERTIES FOLDER "Tests")

    add_test (${TEST} ${TEST})
endforeach ()
