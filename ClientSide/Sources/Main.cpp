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

#include <WinSock2.h>

#include "WindowSystem/Window.hpp"
#include "Network/NetworkManager.hpp"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, INT cmdShow)
{
#ifdef _DEBUG
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    FILE* outStream;
    freopen_s(&outStream, "CON", "w", stdout);
    if (!outStream)
        LOG_ERROR("Console was not attached to process.");
#endif

    Network::NetworkManager& network_manager = Network::NetworkManager::getInstance();
    const bool was_connected = network_manager.connect();
    if (!was_connected)
    {
        LOG_ERROR("Connection with server was not set.");
        return EXIT_FAILURE;
    }

    const bool was_login = network_manager.login();
    if (!was_login)
    {
        LOG_ERROR("Login on the server is failure.");
        return EXIT_FAILURE;
    }

    WindowSystem::Window window(instance, cmdShow);
    window.showWindow("RacingWorld");
    return EXIT_SUCCESS;
}
