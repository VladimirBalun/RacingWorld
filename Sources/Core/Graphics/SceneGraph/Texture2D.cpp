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

#include "PrecompiledHeader.hpp"
#include "Texture2D.hpp"

#include <glew.h>

#include "../../Helpers/Debug.hpp"

Core::Graphics::SceneGraph::Texture2D::Texture2D(std::uint16_t width, std::uint16_t height, const unsigned char* data) noexcept
{
    if (data)
    {
        generateTextureIdentifier();
        bind();
        setTextureParameters();
        fillTextureData(width, height, data);
        unbind();
    }
    else
    {
        LOG_WARNING("Incorrect texture data for creating.");
    }
}

void Core::Graphics::SceneGraph::Texture2D::generateTextureIdentifier() noexcept
{
    glGenTextures(1, &m_texture_id);
#ifdef _DEBUG
    LOG_WARNING_IF(m_texture_id == 0, "ID for texture was not generated.");
#endif // _DEBUG
}

void Core::Graphics::SceneGraph::Texture2D::setTextureParameters() const noexcept
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Core::Graphics::SceneGraph::Texture2D::fillTextureData(std::uint16_t width, std::uint16_t height, const unsigned char* data) const noexcept
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Core::Graphics::SceneGraph::Texture2D::bind() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Core::Graphics::SceneGraph::Texture2D::unbind() const noexcept
{
    glBindTexture(GL_TEXTURE_2D, NULL);
}

void Core::Graphics::SceneGraph::Texture2D::free() noexcept
{
#ifdef _DEBUG
    unsigned int result = 0u;
#endif // _DEBUG

    glDeleteTextures(1, &m_texture_id);
#ifdef _DEBUG
    LOG_WARNING_IF((result = glGetError()) == GL_INVALID_VALUE, "Texture data were not deleted.");
#endif // _DEBUG

    m_texture_id = 0;
}
