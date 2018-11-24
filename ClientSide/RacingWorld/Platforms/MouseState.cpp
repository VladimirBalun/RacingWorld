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

#include "MouseState.h"

void Platforms::MouseState::pressLeftButton() noexcept 
{
    _isPressedLeftButton = true;
}

void Platforms::MouseState::releaseLeftButton() noexcept
{
    _isPressedLeftButton = false;
}

void Platforms::MouseState::pressRightButton() noexcept
{
    _isPressedRightButton = true;
}

void Platforms::MouseState::releaseRightButton() noexcept
{
    _isPressedRightButton = false;
}

bool Platforms::MouseState::isPressedLeftButton() const noexcept
{
    return _isPressedLeftButton;
}

bool Platforms::MouseState::isPressedRightButton() const noexcept
{
    return _isPressedRightButton;
}
