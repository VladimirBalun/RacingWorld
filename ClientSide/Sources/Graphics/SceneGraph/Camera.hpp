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

#pragma once

#include "../OpenGL.hpp"
#include "../../Math/Math.hpp"
#include "../../Utils/Configuration.hpp"

namespace Graphics { namespace SceneGraph {

    class Camera 
    {
    public:
        GLvoid moveLeft(GLfloat speed) noexcept;
        GLvoid moveRight(GLfloat speed) noexcept;
        GLvoid moveForward(GLfloat speed) noexcept;
        GLvoid moveBackward(GLfloat speed) noexcept;
        GLvoid turn(GLint xOffset, GLint yOffset) noexcept;
        GLvoid scale(GLint value) noexcept;
        const Math::Vector3f& getPosition() const noexcept;
        const Math::Matrix4x4f& getViewMatrix() const noexcept;
        const Math::Matrix4x4f& getProjectionMatrix() const noexcept;
    private:
        GLfloat mFov = 45.0f;
        GLfloat mYawAngle = -90.0f;
        GLfloat mPitchAngle = 0.0f;
        Math::Vector3f mPosition = { 0.0f, 0.0f, 3.0f };
        Math::Vector3f mUpDirection = { 0.0f, 1.0f, 0.0f };
        Math::Vector3f mForwardDirection = { 0.0f, 0.0f, -1.0f };
    };

} }
