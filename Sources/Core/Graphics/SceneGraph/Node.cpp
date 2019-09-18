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

#include "Node.hpp"

#include <glm/gtc/matrix_transform.hpp>

void Core::Graphics::SceneGraph::Node::addChild(NodeSPtr node) noexcept
{
    m_children.push_back(node);
}

void Core::Graphics::SceneGraph::Node::removeChild(NodeSPtr node) noexcept
{
    const auto it = std::find(begin(m_children), end(m_children), node);
    if (it != end(m_children))
    {
        m_children.erase(it);
    }
}

void Core::Graphics::SceneGraph::Node::move(const glm::vec3& position) noexcept
{
    glm::translate(m_transformation, position);
}

void Core::Graphics::SceneGraph::Node::move(const glm::vec4& position) noexcept
{
    glm::translate(m_transformation, glm::vec3{ position.x, position.y, position.z });
}

bool Core::Graphics::SceneGraph::Node::isExistChildren() const noexcept
{
    return m_children.empty();
}

bool Core::Graphics::SceneGraph::Node::isExitChild(NodeSPtr node) const noexcept
{
    const auto it = std::find(begin(m_children), end(m_children), node);
    return it != end(m_children);
}

const Core::Graphics::SceneGraph::Mesh* Core::Graphics::SceneGraph::Node::getMesh() const noexcept
{
    return m_mesh;
}

std::deque<Core::Graphics::SceneGraph::NodeSPtr>::iterator Core::Graphics::SceneGraph::Node::childrenBegin() noexcept
{
    return begin(m_children);
}

std::deque<Core::Graphics::SceneGraph::NodeSPtr>::iterator Core::Graphics::SceneGraph::Node::childrenEnd() noexcept
{
    return end(m_children);
}

const std::string& Core::Graphics::SceneGraph::Node::getShaderProgram() const noexcept
{
    return m_shader_program;
}

const glm::mat4x4& Core::Graphics::SceneGraph::Node::getTransformation() const noexcept
{
    return m_transformation;
}
