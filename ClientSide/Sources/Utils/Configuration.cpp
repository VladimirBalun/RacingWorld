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

#include "Configuration.hpp"

const char* Configuration::Network::SERVER_ADDRESS = "127.0.0.1";

const std::wstring Configuration::Player::PLAYER_EMAIL = L"player@gmail.com";
const std::wstring Configuration::Player::PLAYER_PASSWORD = L"difficult_password";
const Math::Vector3<float> Configuration::Player::PLAYER_START_POSITION = { 15.0f, 15.0f, 15.0f };
const Math::Vector3<float> Configuration::Player::PLAYER_START_DIRECTION = { 0.0f, 1.0f, 0.0f };
