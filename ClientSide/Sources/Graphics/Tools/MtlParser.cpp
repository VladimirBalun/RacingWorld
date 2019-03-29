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

#define SPACE_LENGTH                 1 // _
#define LETTER_LENGTH                1 // ?
#define NEW_MATERIAL_WORD_LENGTH     6 // newmtl
#define AMBIENT_COLOR_WORD_LENGTH    2 // Ka
#define DIFFUSE_COLOR_WORD_LENGTH    2 // Kd
#define SPECULAR_COLOR_WORD_LENGTH   2 // Ks
#define SHININESS_WORD_LENGHT        2 // Ns
#define AMBIENT_TEXTURE_WORD_LENGTH  6 // map_Ka
#define DIFFUSE_TEXTURE_WORD_LENGTH  6 // map_Kd

#define MIN_NUMBER_LENGTH         5 // 0.0000
#define MIN_MATERIAL_NAME_LENGTH  LETTER_LENGTH // ?
#define MIN_SHININESS_LENGHT      MIN_NUMBER_LENGTH // 0.0000
#define MIN_COLOR_LENGTH          MIN_NUMBER_LENGTH + SPACE_LENGTH + MIN_NUMBER_LENGTH + SPACE_LENGTH + MIN_NUMBER_LENGTH // 0.0000 0.0000 0.0000
#define MIN_FILE_EXTENSION_LENGTH LETTER_LENGTH + (LETTER_LENGTH * 3) // .???
#define MIN_TEXTURE_NAME_LENGTH   LETTER_LENGTH + MIN_FILE_EXTENSION_LENGTH // ?.???

enum class ParserState
{
    UNKNOWN = 0,
    NEW_MATERIAL,
    MATERIAL_AMBIENT_COLOR,
    MATERIAL_DIFFUSE_COLOR,
    MATERIAL_SPECULAR_COLOR,
    MATERIAL_SHININESS,
    MATERIAL_AMBIENT_TEXTURE,
    MATERIAL_DIFFUSE_TEXTURE,
};

enum class ParserSignals
{
    ABSENT = 0,
    FOUND_MATERIAL,
    FOUND_MATERIAL_AMBIENT_COLOR,
    FOUND_MATERIAL_DIFFUSE_COLOR,
    FOUND_MATERIAL_SPECULAR_COLOR,
    FOUND_MATERIAL_SHININESS,
    FOUND_MATERIAL_AMBIENT_TEXTURE,
    FOUND_MATERIAL_DIFFUSE_TEXTURE,
};

GLvoid Graphics::Tools::MtlParser::parse(const String& currentDirectory, const String& mtlFileName,
    MaterialsData& materials, Memory::Allocators::LinearAllocator& allocator) noexcept
{
    const String buffer(Utils::readFile(mtlFileName, allocator), allocator);
    if (!buffer) 
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Materials for model was not read.");
    }

    ParserState parserState = ParserState::UNKNOWN;
    char* iterator = const_cast<char*>(buffer.getData());
    while (*iterator != '\0')
    {
        switch (parserState)
        {
            case ParserState::NEW_MATERIAL:
            {
                materials.material.push(Components::Material());
                materials.name.push(parseName(iterator, allocator));
                parserState = ParserState::UNKNOWN;
                iterator += NEW_MATERIAL_WORD_LENGTH + SPACE_LENGTH + MIN_MATERIAL_NAME_LENGTH;
                break;
            }
            case ParserState::MATERIAL_AMBIENT_COLOR:
            {
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setSpecularColor(parseColor(iterator));
                iterator += AMBIENT_COLOR_WORD_LENGTH + SPACE_LENGTH + MIN_COLOR_LENGTH;
                break;
            }
            case ParserState::MATERIAL_DIFFUSE_COLOR:
            {
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setSpecularColor(parseColor(iterator));
                iterator += DIFFUSE_COLOR_WORD_LENGTH + SPACE_LENGTH + MIN_COLOR_LENGTH;
                break;
            }
            case ParserState::MATERIAL_SPECULAR_COLOR:
            {
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setSpecularColor(parseColor(iterator));
                iterator += SPECULAR_COLOR_WORD_LENGTH + SPACE_LENGTH + MIN_COLOR_LENGTH;
                break;
            }
            case ParserState::MATERIAL_SHININESS:
            {
                parserShininess(iterator);
                parserState = ParserState::UNKNOWN;
                iterator += SHININESS_WORD_LENGHT + SPACE_LENGTH + MIN_SHININESS_LENGHT;
                break;
            }
            case ParserState::UNKNOWN:
            {
                iterator += LETTER_LENGTH;
            }
        }
    }
}

String Graphics::Tools::MtlParser::parseName(const char* iterator, Memory::Allocators::LinearAllocator& allocator) noexcept
{
    std::size_t nameLength = 0;
    const char* tmpIterator = iterator;
    while ( (*tmpIterator != ' ') || (*tmpIterator != '\n') )
    {
        tmpIterator++;
        nameLength++;
    }
    return String(iterator, nameLength, allocator);
}

GLfloat Graphics::Tools::MtlParser::parserShininess(const char* iterator) noexcept
{
    static GLfloat shininess = 0.0f;
    sscanf_s(iterator, "%f", &shininess);
    return shininess;
}

Math::Vector3f Graphics::Tools::MtlParser::parseColor(const char* iterator) noexcept
{
    static GLfloat r = 0.0f;
    static GLfloat g = 0.0f;
    static GLfloat b = 0.0f;
    sscanf_s(iterator, "%f %f %f", &r, &g, &b);
    return Math::Vector3f(r, g, b);
}
