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

#include <forward_list>

#include "Mesh.hpp"
#include "../../Math/Matrix4x4.hpp"

namespace Graphics { namespace SceneGraph {

    class Node
    {
    public:
        Node(const Mesh& mesh) : mMesh(mesh) {}
        GLvoid removeChildren() noexcept;
        GLvoid addChild(const Node& child) noexcept;
        const Math::Matrix4x4<GLfloat>& getTransformation() noexcept;
        GLvoid setTransformation(const Math::Matrix4x4<GLfloat>& transformation) noexcept;
    private:
        Mesh mMesh;
        std::forward_list<Node> mChildren;
        Math::Matrix4x4<GLfloat> mTransformation;
    };

}}
