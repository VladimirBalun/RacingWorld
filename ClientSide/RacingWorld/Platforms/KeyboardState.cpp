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

#include "KeyboardState.h"

void Platforms::KeyboardState::pressKeyW() noexcept 
{
    _isPressedKeyW = true;
}

void Platforms::KeyboardState::releaseKeyW() noexcept
{
    _isPressedKeyW = false;
}

void Platforms::KeyboardState::pressKeyS() noexcept
{
    _isPressedKeyS = true;
}

void Platforms::KeyboardState::releaseKeyS() noexcept
{
    _isPressedKeyS = false;
}

void Platforms::KeyboardState::pressKeyA() noexcept
{
    _isPressedKeyA = true;
}

void Platforms::KeyboardState::releaseKeyA() noexcept
{
    _isPressedKeyA = false;
}

void Platforms::KeyboardState::pressKeyD() noexcept
{
    _isPressedKeyD = true;
}

void Platforms::KeyboardState::releaseKeyD() noexcept
{
    _isPressedKeyD = false;
}

bool Platforms::KeyboardState::isPressedKeyW() const noexcept
{
    return _isPressedKeyW;
}

bool Platforms::KeyboardState::isPressedKeyS() const noexcept
{
    return _isPressedKeyS;
}

bool Platforms::KeyboardState::isPressedKeyA() const noexcept
{
    return _isPressedKeyA;
}

bool Platforms::KeyboardState::isPressedKeyD() const noexcept
{
    return _isPressedKeyD;
}
