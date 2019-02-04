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
    while (mChild)
    {
        Node* tmpPoiner = mChild;
        mChild = mChild->mNextNode;
        tmpPoiner = nullptr;
    }
}

GLvoid Graphics::SceneGraph::Node::addChild(Node* child) noexcept
{
    child->mNextNode = mNextNode;
    mChild = child;
}

GLvoid Graphics::SceneGraph::Node::setMesh(Components::Mesh mesh) noexcept
{
    mMesh = mesh;
}

GLvoid Graphics::SceneGraph::Node::setTransformation(const Math::Matrix4x4<GLfloat>& transformation) noexcept
{
    mTransformation = transformation;
}

Graphics::Components::Mesh& Graphics::SceneGraph::Node::getMesh() noexcept
{
    return mMesh;
}

GLboolean Graphics::SceneGraph::Node::isExistMesh() const noexcept
{
    return mMesh.isInitialized();
}

GLboolean Graphics::SceneGraph::Node::isExistChildren() const noexcept
{
    return mChild != nullptr;
}

Math::Matrix4x4<GLfloat>& Graphics::SceneGraph::Node::getTransformation() noexcept 
{
    return mTransformation;
}

GLvoid Graphics::SceneGraph::Node::childrenForEach(GLvoid(*callback)(Node* child)) noexcept
{
    Node* iterator = mChild;
    while (iterator) 
    {
        callback(iterator);
        iterator = iterator->mNextNode;
    }
}
