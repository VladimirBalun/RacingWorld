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

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Graphics {

// Singleton
class Camera
{
public:
    explicit Camera() = default;

    GLvoid moveForward(GLfloat length);
    GLvoid moveBack(GLfloat length);
    GLvoid moveLeft(GLfloat length);
    GLvoid moveRight(GLfloat length);

    GLvoid turnUp(GLfloat angle);
    GLvoid turnDown(GLfloat angle);
    GLvoid turnLeft(GLfloat angle);
    GLvoid turnRight(GLfloat angle);
private:
    static Camera* camera;
};

}