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

#include "Camera.hpp"

#define FOV_MIN_SIZE    15.0f
#define FOW_MAX_SIZE    45.0f
#define PITCH_MIN_ANGLE -89.0f
#define PITCH_MAX_ANGLE 89.0f

GLvoid Graphics::SceneGraph::Camera::setSpeed(GLfloat speed) noexcept
{
    mSpeed = speed / 1000;
}

GLvoid Graphics::SceneGraph::Camera::moveLeft() noexcept
{
    Math::Vector3f rightDirection = Math::cross(mForwardDirection, mUpDirection);
    rightDirection.normalize();
    rightDirection.mul(mSpeed);
    mPosition.sub(rightDirection);
}

GLvoid Graphics::SceneGraph::Camera::moveRight() noexcept
{
    Math::Vector3f rightDirection = Math::cross(mForwardDirection, mUpDirection);
    rightDirection.normalize();
    rightDirection.mul(mSpeed);
    mPosition.add(rightDirection);
}

GLvoid Graphics::SceneGraph::Camera::moveForward() noexcept
{
    mPosition.add(mForwardDirection * mSpeed);
}

GLvoid Graphics::SceneGraph::Camera::moveBackward() noexcept
{
    mPosition.sub(mForwardDirection * mSpeed);
}

GLvoid Graphics::SceneGraph::Camera::turn(GLint xOffset, GLint yOffset) noexcept
{
    GLfloat sensitivity = 0.05f;
    mYawAngle += xOffset * sensitivity;
    mPitchAngle += yOffset * sensitivity;

    if (mPitchAngle > 89.0f)
        mPitchAngle = 89.0f;
    if (mPitchAngle < -89.0f)
        mPitchAngle = -89.0f;

    GLfloat pitchAnglePerRadians = Math::radians(mPitchAngle);
    GLfloat yawAnglePerRadians = Math::radians(mYawAngle);
    GLfloat pitchAngleCosine = cos(pitchAnglePerRadians);
    mForwardDirection.setX(pitchAngleCosine * cos(yawAnglePerRadians));
    mForwardDirection.setY(sin(pitchAnglePerRadians));
    mForwardDirection.setZ(pitchAngleCosine * sin(yawAnglePerRadians));
    mForwardDirection.normalize();
}

GLvoid Graphics::SceneGraph::Camera::scale(GLint value) noexcept
{
    mFov += value;
    if (mFov < FOV_MIN_SIZE)
        mFov = FOV_MIN_SIZE;
    if (mFov > FOW_MAX_SIZE)
        mFov = FOW_MAX_SIZE;
}

const Math::Vector3f& Graphics::SceneGraph::Camera::getPosition() const noexcept
{
    return mPosition;
}

const Math::Matrix4x4f& Graphics::SceneGraph::Camera::getViewMatrix() const noexcept
{
    static Math::Matrix4x4f viewMatrix;
    Math::setLookAt(viewMatrix, mPosition, mPosition + mForwardDirection, mUpDirection);
    return viewMatrix;
}

const Math::Matrix4x4f& Graphics::SceneGraph::Camera::getProjectionMatrix() const noexcept
{
    static Math::Matrix4x4f perspectiveMatrix;
    const std::uint16_t windowWidth = Configuration::Window::windowWidth;
    const std::uint16_t windowHeight = Configuration::Window::windowHeight;
    Math::setPerspectiveMatrix(perspectiveMatrix, mFov, static_cast<GLfloat>(windowWidth / windowHeight), 0.1f, 100.f);
    return perspectiveMatrix;
}
