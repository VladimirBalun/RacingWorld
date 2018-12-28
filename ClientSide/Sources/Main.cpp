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

#include "System/WindowSystem/Window.hpp"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define WINDOW_TITLE "RacingWorld"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, INT cmdShow)
{
    #ifdef _DEBUG
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        freopen("CON", "w", stdout);
    #endif

    try 
    {
        Platforms::WindowSystem::Window window(instance, cmdShow);
        window.showWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) 
    {
        LOG_ERROR(e.what());
        return EXIT_FAILURE;
    }
    catch (...) 
    {
        LOG_ERROR("Unknown error.");
        return EXIT_FAILURE;
    }
}
