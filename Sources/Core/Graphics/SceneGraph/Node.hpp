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

#include <deque>
#include <functional>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "../../Helpers/Macroses.hpp"

namespace Core { namespace Graphics { namespace SceneGraph {

    FWD_DECL_SMART_PTRS_FOR_CLASS(Node)

    class Node
    {
    public:
        template<typename... Args>
        void emplaceChild(Args... args);
        void addChild(NodeSPtr node) noexcept;
        void removeChild(NodeSPtr node) noexcept;
        void move(const glm::vec3& position) noexcept;
        void move(const glm::vec4& position) noexcept;
        bool isExistChildren() const noexcept;
        bool isExitChild(NodeSPtr node) const noexcept;
        void childrenForEach(std::function<void(NodeSPtr)> function) noexcept;
        const glm::mat4x4& getTransformation() const noexcept;
    private:
        std::deque<NodeSPtr> m_children{};
        glm::mat4x4 m_transformation{ 1.0f };
    };

    template<typename... Args>
    void Node::emplaceChild(Args... args)
    {
        const auto node = std::make_shared<Node>(std::forward<Args>(args)...);
        m_children.push_back(node);
    }

}}}
