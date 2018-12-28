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

#include "KeyboardState.hpp"

void Platforms::KeyboardState::pressKeyW() noexcept 
{
    mIsPressedKeyW = true;
}

void Platforms::KeyboardState::releaseKeyW() noexcept
{
    mIsPressedKeyW = false;
}

void Platforms::KeyboardState::pressKeyS() noexcept
{
    mIsPressedKeyS = true;
}

void Platforms::KeyboardState::releaseKeyS() noexcept
{
    mIsPressedKeyS = false;
}

void Platforms::KeyboardState::pressKeyA() noexcept
{
    mIsPressedKeyA = true;
}

void Platforms::KeyboardState::releaseKeyA() noexcept
{
    mIsPressedKeyA = false;
}

void Platforms::KeyboardState::pressKeyD() noexcept
{
    mIisPressedKeyD = true;
}

void Platforms::KeyboardState::releaseKeyD() noexcept
{
    mIisPressedKeyD = false;
}

bool Platforms::KeyboardState::isPressedKeyW() const noexcept
{
    return mIsPressedKeyW;
}

bool Platforms::KeyboardState::isPressedKeyS() const noexcept
{
    return mIsPressedKeyS;
}

bool Platforms::KeyboardState::isPressedKeyA() const noexcept
{
    return mIsPressedKeyA;
}

bool Platforms::KeyboardState::isPressedKeyD() const noexcept
{
    return mIisPressedKeyD;
}
