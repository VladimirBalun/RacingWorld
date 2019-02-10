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

#define FOV_MIN_SIZE 1.0f
#define FOW_MAX_SIZE 45.0f

Graphics::SceneGraph::Camera& Graphics::SceneGraph::Camera::getInstance()
{
    static Camera instance;
    return instance;
}

GLvoid Graphics::SceneGraph::Camera::moveLeft() 
{
    Math::Vector3f rightDirection = Math::cross(mForwardDirection, mUpDirection);
    rightDirection.normalize();
    mPosition.sub(rightDirection * mSpeed);
}

GLvoid Graphics::SceneGraph::Camera::moveRight()
{
    Math::Vector3f rightDirection = Math::cross(mForwardDirection, mUpDirection);
    rightDirection.normalize();
    mPosition.add(rightDirection * mSpeed);
}

GLvoid Graphics::SceneGraph::Camera::moveForward()
{
    mPosition.add(mForwardDirection * mSpeed);
}

GLvoid Graphics::SceneGraph::Camera::moveBackward()
{
    mPosition.sub(mForwardDirection * mSpeed);
}

GLvoid Graphics::SceneGraph::Camera::scale(GLfloat value)
{
    mFov += value;
    if (mFov < FOV_MIN_SIZE)
        mFov = FOV_MIN_SIZE;
    if (mFov > FOW_MAX_SIZE)
        mFov = FOW_MAX_SIZE;
}

GLvoid Graphics::SceneGraph::Camera::setSpeed(GLfloat speed)
{
    mSpeed = speed;
}
