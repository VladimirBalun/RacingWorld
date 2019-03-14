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

#include "TextureManager.hpp"

GLvoid Graphics::Managers::TextureManager::initializeTextures() noexcept 
{
    Memory::Allocators::LinearAllocator mTexturesAllocator(ONE_VIRTUAL_PAGE);
    mTextures[FONT_TEXTURE] = createTexture(mTexturesAllocator, "Font.bmp");
}

Graphics::Components::Texture2D Graphics::Managers::TextureManager::createTexture(Memory::Allocators::LinearAllocator& allocator, const char* textureName) const noexcept
{
    const char* texturesPath = Configuration::getTexturesPath();
    char* texturePath = Utils::createStringFromStrings(strlen(texturesPath) + strlen(textureName) + 1,
        std::bind(&Memory::Allocators::LinearAllocator::allocate, &allocator, std::placeholders::_1), texturesPath, textureName);
    
    GLuint textureWidth = 0;
    GLuint textureHeight = 0;
    unsigned char* data = Tools::BmpReader::read(texturePath, textureWidth, textureHeight, allocator);
    return Components::Texture2D(data, textureWidth, textureHeight);
}

const Graphics::Components::Texture2D& Graphics::Managers::TextureManager::getTexture(ETextureType meshType) noexcept
{
    return mTextures[meshType];
}
