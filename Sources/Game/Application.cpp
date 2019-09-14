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

#include "Application.hpp"

#include "Identifiers.hpp"
#include "../Core/Managers/SoundManager.hpp"

Game::Application::Application(int window_width, int window_height, const std::string& window_title) noexcept
    : m_window(window_width, window_height, window_title)
{
}

void Game::Application::start()
{
    g_sound_manager.playMusic(ID::g_background_sound);
    m_window.show();
}
