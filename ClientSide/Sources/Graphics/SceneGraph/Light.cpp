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

#include "Light.hpp"

GLvoid Graphics::SceneGraph::Light::move(Math::Vector3f&& alignment) noexcept 
{
    m_position.add(alignment);
}

const Math::Vector3<GLfloat>& Graphics::SceneGraph::Light::getPosition() const noexcept
{
    return m_position;
}

const Math::Vector3<GLfloat>& Graphics::SceneGraph::Light::getAmbientColor() const noexcept
{
    return m_ambient_color;
}

const Math::Vector3<GLfloat>& Graphics::SceneGraph::Light::getDiffuseColor() const noexcept
{
    return m_diffuse_color;
}

const Math::Vector3<GLfloat>& Graphics::SceneGraph::Light::getSpecularColor() const noexcept
{
    return m_specular_color;
}
