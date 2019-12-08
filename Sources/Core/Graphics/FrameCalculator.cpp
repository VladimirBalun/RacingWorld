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
#include "FrameCalculator.hpp"

#include <GLFW/glfw3.h>

void Core::Graphics::FrameCalculator::onChangingFrame() noexcept
{
    const float current_time = static_cast<float>(glfwGetTime());
    m_deltaTime = current_time - m_lastFrameTime;
    m_lastFrameTime = current_time;
}

float Core::Graphics::FrameCalculator::getDeltaTime() const noexcept
{
    return m_deltaTime;
}
