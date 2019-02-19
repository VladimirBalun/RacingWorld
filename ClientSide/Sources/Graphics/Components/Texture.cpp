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

#include "Texture.hpp"

Graphics::Components::Texture::Texture(const char* imageData, GLuint width, GLuint height)
    : mWidth(width), mHeight(height) 
{
    glGenTextures(1, &mTextureID);

#ifdef _DEBUG
    if (mTextureID == 0)
        LOG_WARNING("ID for texture was not generated.");
#endif // _DEBUG

    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, NULL);
}

GLuint Graphics::Components::Texture::getID() const noexcept
{
    return mTextureID;
}

GLuint Graphics::Components::Texture::getWidth() const noexcept
{
    return mWidth;
}

GLuint Graphics::Components::Texture::getHeight() const noexcept
{
    return mHeight;
}
