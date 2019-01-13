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
#include "../Tools/HardwareBuffers.hpp"
#include "../Tools/ShaderProgram.hpp"
#include "../Components/SimpleMesh.hpp"
#include "../../Utils/Configuration.hpp"
#include "../../Math/Matrices/Matrix4x4.hpp"
#include "../../Math/Matrices/Matrices4x4.hpp"
#include "../../Math/Vectors/Vector3.hpp"

#include "ShaderManager.hpp"

    struct Matrix4fz {
        float m[4][4];
    };

namespace Graphics { namespace SceneGraph {

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

        Tools::ShaderProgram* prog;
        Tools::ShaderProgram* prog2;
        Tools::HardwareBuffers* obj1;
        Tools::HardwareBuffers* obj2;
        Components::SimpleMesh* mesh;

        Math::Matrix4x4f matpos, matPerspect, matRot;