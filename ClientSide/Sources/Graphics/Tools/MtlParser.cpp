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

#include "MtlParser.hpp"

void Graphics::Tools::MtlParser::parse(const String& currentDirectory, const String& mtlFileName,
    MaterialsData& materials, Memory::Allocators::LinearAllocator& allocator) noexcept
{
    const String buffer(Utils::readFile(mtlFileName, allocator), allocator);
    if (!buffer) 
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Materials for model was not read.");
    }

    char* symbolIterator = const_cast<char*>(buffer.getData());
}

void Graphics::Tools::MtlParser::parseMaterial(const String& currentDirectory, char* iterator, MaterialsData& materials) noexcept
{
    while (*iterator != '\0')
    {
        if (strncmp(iterator, "newmtl ", 7) == 0)
        {

        }
        iterator++;
    }
}

GLfloat Graphics::Tools::MtlParser::parserShininess(char* line) noexcept
{
    static GLfloat shininess = 0.0f;
    sscanf_s(line, "%f", &shininess);
    return shininess;
}

void Graphics::Tools::MtlParser::parseColor(char* line, Math::Vector3f& color) noexcept
{
    static GLfloat r = 0.0f;
    static GLfloat g = 0.0f;
    static GLfloat b = 0.0f;
    sscanf_s(line, "%f %f %f", &r, &g, &b);
    color.setX(r);
    color.setY(g);
    color.setZ(b);
}
