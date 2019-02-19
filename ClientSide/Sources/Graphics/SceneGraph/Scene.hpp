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

#include "Node.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "SceneGraphBuilder.hpp"
#include "../OpenGL.hpp"
#include "../Managers/MeshManager.hpp"
#include "../Managers/ShaderManager.hpp"
#include "../../WindowSystem/WindowEventListener.hpp"
#include "../../Memory/Allocators/LinearAllocator.hpp"

namespace Graphics { namespace SceneGraph {

    class Scene
    {
    public:
        explicit Scene(HDC& windowContext): 
            mWindowContext(windowContext), 
            mSceneGraphAllocator(ONE_VIRTUAL_PAGE), 
            mSceneLight({ 1.2f, 1.0f, 2.0f }, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }) {}
        GLvoid init(GLint sceneWidth, GLint sceneHeight);
        GLvoid render();
        GLvoid update();
    private:
        Node* mRootNode = nullptr;
        HDC& mWindowContext;
        Light mSceneLight;
        Camera mSceneCamera;
        Managers::MeshManager mMeshManager;
        Managers::ShaderManager mShaderManager;
        Memory::Allocators::LinearAllocator mSceneGraphAllocator;
    };

} }
