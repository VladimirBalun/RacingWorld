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

Input::MouseState::MouseState()
{
#ifdef _DEBUG
    if (!mXPosition.is_lock_free() || !mYPosition.is_lock_free())
        LOG_WARNING("Operations with 'int' are not lock free on current platform.");
    if (!mIsPressedLeftButton.is_lock_free() || !mIsPressedRightButton.is_lock_free())
        LOG_WARNING("Operations with 'bool' are not lock free on current platform.");
#endif // _DEBUG
}

void Input::MouseState::setPosition(int xPos, int yPos) noexcept
{
    mLastXPosition.store(mXPosition);
    mLastYPosition.store(mYPosition);
    mXPosition.store(xPos);
    mYPosition.store(yPos);
}

int Input::MouseState::getAndUnsetXDisplacementOffset() noexcept
{
    int offset = mXPosition - mLastXPosition;
    mLastXPosition.store(mXPosition);
    return offset;
}

int Input::MouseState::getAndUnsetYDisplacementOffset() noexcept
{
    int offset = mLastYPosition - mYPosition;
    mLastYPosition.store(mYPosition);
    return offset;
}

void Input::MouseState::setWheelOffset(int value) noexcept
{
    mWheelOffset.fetch_add(value);
}

int Input::MouseState::getAndUnsetWheelOffset() noexcept
{
    int offset = mWheelOffset;
    mWheelOffset.store(0);
    return offset;
}

void Input::MouseState::pressLeftButton() noexcept
{
    mIsPressedLeftButton.store(true);
}

void Input::MouseState::releaseLeftButton() noexcept
{
    mIsPressedLeftButton.store(false);
}

void Input::MouseState::pressRightButton() noexcept
{
    mIsPressedRightButton.store(true);
}

void Input::MouseState::releaseRightButton() noexcept
{
    mIsPressedRightButton.store(false);
}

bool Input::MouseState::isPressedLeftButton() const noexcept
{
    return mIsPressedLeftButton.load();
}

bool Input::MouseState::isPressedRightButton() const noexcept
{
    return mIsPressedRightButton.load();
}
