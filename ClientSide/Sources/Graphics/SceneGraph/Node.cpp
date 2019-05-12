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

GLvoid Graphics::SceneGraph::Node::removeChildren() noexcept
{
    m_children.clear();
}

GLvoid Graphics::SceneGraph::Node::addChild(const std::shared_ptr<Node>& child) noexcept
{
    m_children.push_front(child);
}

GLvoid Graphics::SceneGraph::Node::setMesh(const Components::Mesh& mesh) noexcept
{
    m_mesh = mesh;
}

GLvoid Graphics::SceneGraph::Node::setTransformation(const Math::Matrix4x4<GLfloat>& transformation) noexcept
{
    m_transformation = transformation;
}

const std::optional<Graphics::Components::Mesh>& Graphics::SceneGraph::Node::getMesh() noexcept
{
    return m_mesh;
}

GLboolean Graphics::SceneGraph::Node::isExistChildren() const noexcept
{
    return !m_children.empty();
}

Math::Matrix4x4<GLfloat>& Graphics::SceneGraph::Node::getTransformation() noexcept 
{
    return m_transformation;
}

GLvoid Graphics::SceneGraph::Node::childrenForEach(std::function<GLvoid(std::shared_ptr<Node>& child)> callback) noexcept
{
    for (auto& child : m_children) 
    {
        callback(child);
    }
}
