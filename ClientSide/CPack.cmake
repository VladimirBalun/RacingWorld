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

install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION Bin)
install (FILES ../ServerSide/game/target/GameServer.jar DESTINATION Bin)
install (DIRECTORY ./Resources DESTINATION ./)

set (CPACK_GENERATOR NSIS)
set (CPACK_PACKAGE_NAME "RacingWorld")
set (CPACK_PACKAGE_VENDOR "Vladimir Balun")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "RacingWorld - is a multiplayer online 3D game about racing.")
set (CPACK_PACKAGE_VERSION "0.1.0")
set (CPACK_PACKAGE_VERSION_MAJOR "0")
set (CPACK_PACKAGE_VERSION_MINOR "1")
set (CPACK_PACKAGE_VERSION_PATCH "0")
set (CPACK_PACKAGE_INSTALL_DIRECTORY "RacingWorld")
SET (CPACK_NSIS_MODIFY_PATH ON)

INCLUDE(CPack)