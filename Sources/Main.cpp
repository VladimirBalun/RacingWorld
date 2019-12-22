/*
 * Copyright 2018 Vladimir Balun
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "PrecompiledHeader.hpp"
#include "Core/Managers.hpp"
#include "Game/Application.hpp"

int main(int argc, char** argv)
{
    try
    {
        Core::Managers::initialize();
        Game::Application application(860, 600, "RacingWorld");
        application.start();
        return EXIT_SUCCESS;
    }
    catch (std::exception& e)
    {
        LOG_ERROR(STR("Caught exception: ") + e.what());
        return EXIT_FAILURE;
    }
    catch (...)
    {
        LOG_ERROR("Caught unknown exception.");
        return EXIT_FAILURE;
    }
}
