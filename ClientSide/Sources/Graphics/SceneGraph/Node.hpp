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

#include <memory>
#include <functional>
#include <forward_list>

#include "../Components/Mesh.hpp"
#include "../../Math/Matrices/Matrix4x4.hpp"

namespace Graphics { namespace SceneGraph {

    class Node
    {
    public:
        GLvoid removeChildren() noexcept;
        GLvoid addChild(const std::shared_ptr<Node>& child) noexcept;
        GLvoid setMesh(const Components::Mesh& mesh) noexcept;
        GLvoid setTransformation(const Math::Matrix4x4<GLfloat>& transformation) noexcept;
        const std::optional<Components::Mesh>& getMesh() noexcept;
        GLboolean isExistChildren() const noexcept;
        Math::Matrix4x4<GLfloat>& getTransformation() noexcept;
        GLvoid childrenForEach(std::function<GLvoid(std::shared_ptr<Node>& child)> callback) noexcept;
    private:
        std::optional<Components::Mesh> m_mesh{};
        Math::Matrix4x4<GLfloat> m_transformation{};
        std::forward_list<std::shared_ptr<Node>> m_children{};
    };

}}
