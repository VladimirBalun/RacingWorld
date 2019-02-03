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

#include "../Components/Mesh.hpp"
#include "../../Math/Matrices/Matrix4x4.hpp"
#include "../../Memory/IAllocatable.hpp"

namespace Graphics { namespace SceneGraph {

    class Node : public Memory::IAllocatable
    {
    public:
        GLvoid removeChildren() noexcept;
        GLvoid addChild(Node* child) noexcept;
        GLvoid setMesh(Components::Mesh mesh) noexcept;
        GLvoid setTransformation(const Math::Matrix4x4<GLfloat>& transformation) noexcept;

        Components::Mesh& getMesh() noexcept;
        GLboolean isExistMesh() const noexcept;
        GLboolean isExistChildren() const noexcept;
        Math::Matrix4x4<GLfloat>& getTransformation() noexcept;
        GLvoid childrenForEach(GLvoid(*callback)(Node* child)) noexcept;
    private:
        Components::Mesh mMesh;
        Node* mChild = nullptr;
        Node* mNextNode = nullptr;
        Math::Matrix4x4<GLfloat> mTransformation;
    };

}}
