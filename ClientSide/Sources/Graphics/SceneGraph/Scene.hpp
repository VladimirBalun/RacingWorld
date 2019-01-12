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

#include <string>

#include "Node.hpp"
#include "../OpenGL.hpp"
#include "../Utils/ShaderProgram.hpp"
#include "../../Utils/Configuration.hpp"
#include "../Models/SimpleMesh.hpp"
#include "../../Math/Matrix4x4.hpp"
#include "../../Math/Matrices4x4.hpp"
#include "../../Math/Vector3.hpp"
#include "VertexBuffers.hpp"

namespace Graphics { namespace SceneGraph {

    struct Matrix4fz {
        float m[4][4];
    };

    class Scene
    {
    public:
        explicit Scene(HDC& windowContext, GLint sceneWidth, GLint sceneHeight)
            : mWindowContext(windowContext), mSceneWidth(sceneWidth), mSceneHeight(sceneHeight) {}
        GLvoid initScene();
        GLvoid renderScene();
        GLvoid updateScene();
    private:
        HDC& mWindowContext;
        GLint mSceneWidth;
        GLint mSceneHeight;

        Graphics::Utils::ShaderProgram* prog;
        Graphics::Utils::ShaderProgram* prog2;
        Graphics::SceneGraph::HardwareBuffers* obj1;
        Graphics::SceneGraph::HardwareBuffers* obj2;
        Graphics::SimpleMesh::SimpleMesh* mesh;

        Math::Matrix4x4f matpos, matPerspect, matRot;

    };

}}
