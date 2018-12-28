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

GLvoid Graphics::Utils::Texture::setID(GLuint id) noexcept 
{
    mID = id;
}

GLuint Graphics::Utils::Texture::getID() const noexcept
{
    return mID;
}

GLuint Graphics::Utils::Texture::getWidth() const noexcept
{
    return mWidth;
}

GLuint Graphics::Utils::Texture::getHeight() const noexcept
{
    return mHeight;
}

const std::vector<GLubyte>& Graphics::Utils::Texture::getImageData() const noexcept
{
    return mImageData;
}