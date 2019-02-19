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

GLvoid Graphics::SceneGraph::Camera::moveLeft(GLfloat speed)
{
    Math::Vector3f rightDirection = Math::cross(mForwardDirection, mUpDirection);
    rightDirection.normalize();
    mPosition.sub(rightDirection * speed);
}

GLvoid Graphics::SceneGraph::Camera::moveRight(GLfloat speed)
{
    Math::Vector3f rightDirection = Math::cross(mForwardDirection, mUpDirection);
    rightDirection.normalize();
    mPosition.add(rightDirection * speed);
}

GLvoid Graphics::SceneGraph::Camera::moveForward(GLfloat speed)
{
    mPosition.add(mForwardDirection * speed);
}

GLvoid Graphics::SceneGraph::Camera::moveBackward(GLfloat speed)
{
    mPosition.sub(mForwardDirection * speed);
}

GLvoid Graphics::SceneGraph::Camera::turn(GLint xOffset, GLint yOffset)
{
    GLfloat sensitivity = 0.05f; // TODO: need speed calculation by FPS
    mYawAngle += xOffset * sensitivity;
    mPitchAngle += yOffset * sensitivity;

    if (mPitchAngle > 89.0f)
        mPitchAngle = 89.0f;
    if (mPitchAngle < -89.0f)
        mPitchAngle = -89.0f;

    mForwardDirection.setX(cos(Math::radians(mPitchAngle)) * cos(Math::radians(mYawAngle)));
    mForwardDirection.setY(sin(Math::radians(mPitchAngle)));
    mForwardDirection.setZ(cos(Math::radians(mPitchAngle)) * sin(Math::radians(mYawAngle)));
    mForwardDirection.normalize();
}

GLvoid Graphics::SceneGraph::Camera::scale(GLint value)
{
    mFov += value;
    if (mFov < FOV_MIN_SIZE)
        mFov = FOV_MIN_SIZE;
    if (mFov > FOW_MAX_SIZE)
        mFov = FOW_MAX_SIZE;
}

Math::Vector3f Graphics::SceneGraph::Camera::getPosition()
{
    return mPosition;
}

Math::Matrix4x4f Graphics::SceneGraph::Camera::getViewMatrix()
{
    Math::Matrix4x4f viewMatrix;
    Math::setLookAt(viewMatrix, mPosition, mPosition + mForwardDirection, mUpDirection);
    return viewMatrix;
}

Math::Matrix4x4f Graphics::SceneGraph::Camera::getProjectionMatrix()
{
    Math::Matrix4x4f perspectiveMatrix;
    Math::setPerspectiveMatrix(perspectiveMatrix, mFov, (GLfloat)800 / 600, 0.1f, 100.f);
    return perspectiveMatrix;
}
