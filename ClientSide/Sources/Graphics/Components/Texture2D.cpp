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

#include "Texture2D.hpp"

Graphics::Components::Texture2D::Texture2D(const std::vector<char>&& image_data, GLuint width, GLuint height) noexcept
    : m_width(width), m_height(height)
{
    glGenTextures(1, &m_texture_idD);

#ifdef _DEBUG
    if (m_texture_idD == 0)
        LOG_WARNING("ID for texture was not generated.");
#endif // _DEBUG

    glBindTexture(GL_TEXTURE_2D, m_texture_idD);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data.data());
    glBindTexture(GL_TEXTURE_2D, NULL);
}

GLuint Graphics::Components::Texture2D::getID() const noexcept
{
    return m_texture_idD;
}

GLuint Graphics::Components::Texture2D::getWidth() const noexcept
{
    return m_width;
}

GLuint Graphics::Components::Texture2D::getHeight() const noexcept
{
    return m_height;
}
