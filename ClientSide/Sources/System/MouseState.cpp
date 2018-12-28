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

#include "MouseState.hpp"

void Platforms::MouseState::pressLeftButton() noexcept 
{
    mIsPressedLeftButton = true;
}

void Platforms::MouseState::releaseLeftButton() noexcept
{
    mIsPressedLeftButton = false;
}

void Platforms::MouseState::pressRightButton() noexcept
{
    mIsPressedRightButton = true;
}

void Platforms::MouseState::releaseRightButton() noexcept
{
    mIsPressedRightButton = false;
}

bool Platforms::MouseState::isPressedLeftButton() const noexcept
{
    return mIsPressedLeftButton;
}

bool Platforms::MouseState::isPressedRightButton() const noexcept
{
    return mIsPressedRightButton;
}
