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

#define MIN_NUMBER_LENGTH         6 // 0.0000
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

GLvoid Graphics::Tools::MtlParser::parse(MaterialsData& materials) noexcept
{
    const String buffer(Utils::readFile(mMtlFileName, mAllocator), mAllocator);
    if (!buffer) 
    {
        EventSystem::EventManager& eventManager = EventSystem::EventManager::getInstance();
        eventManager.notifyGlobalError("Materials for model was not read.");
    }

    // TODO: need to add transaction table
    ParserState parserState = ParserState::UNKNOWN;
    GLuint countMaterials = getCountMaterials(buffer);
    char* iterator = const_cast<char*>(buffer.getData());
    while (*iterator != '\0')
    {
        switch (parserState)
        {
            case ParserState::UNKNOWN:
                if (strncmp(iterator, "newmtl ", NEW_MATERIAL_WORD_LENGTH + SPACE_LENGTH) == 0)
                {
                    parserState = ParserState::NEW_MATERIAL;
                    iterator += NEW_MATERIAL_WORD_LENGTH + SPACE_LENGTH;
                }
                else if (strncmp(iterator, "Ka ", AMBIENT_COLOR_WORD_LENGTH + SPACE_LENGTH) == 0)
                {
                    parserState = ParserState::MATERIAL_AMBIENT_COLOR;
                    iterator += AMBIENT_COLOR_WORD_LENGTH + SPACE_LENGTH;
                }
                else if (strncmp(iterator, "Kd ", DIFFUSE_COLOR_WORD_LENGTH + SPACE_LENGTH) == 0)
                {
                    parserState = ParserState::MATERIAL_DIFFUSE_COLOR;
                    iterator += DIFFUSE_COLOR_WORD_LENGTH + SPACE_LENGTH;
                }
                else if (strncmp(iterator, "Ks ", SPECULAR_COLOR_WORD_LENGTH + SPACE_LENGTH) == 0)
                {
                    parserState = ParserState::MATERIAL_SPECULAR_COLOR;
                    iterator += SPECULAR_COLOR_WORD_LENGTH + SPACE_LENGTH;
                }
                else if (strncmp(iterator, "Ns ", SHININESS_WORD_LENGHT + SPACE_LENGTH) == 0)
                {
                    parserState = ParserState::MATERIAL_SHININESS;
                    iterator += SHININESS_WORD_LENGHT + SPACE_LENGTH;
                }
                else if (strncmp(iterator, "map_Ka ", AMBIENT_TEXTURE_WORD_LENGTH + SPACE_LENGTH) == 0)
                {
                    parserState = ParserState::MATERIAL_AMBIENT_TEXTURE;
                    iterator += AMBIENT_TEXTURE_WORD_LENGTH + SPACE_LENGTH;
                }
                else if (strncmp(iterator, "map_Kd ", DIFFUSE_TEXTURE_WORD_LENGTH + SPACE_LENGTH) == 0)
                {
                    parserState = ParserState::MATERIAL_DIFFUSE_TEXTURE;
                    iterator += DIFFUSE_TEXTURE_WORD_LENGTH + SPACE_LENGTH;
                }
                else
                {
                    iterator += LETTER_LENGTH;
                }
                break;
            case ParserState::NEW_MATERIAL:
                parserState = ParserState::UNKNOWN;
                materials.material.push(Components::Material());
                materials.name.push(parseName(iterator));
                iterator += MIN_MATERIAL_NAME_LENGTH;
                break;
            case ParserState::MATERIAL_AMBIENT_COLOR:
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setAmbientColor(parseColor(iterator));
                iterator += MIN_COLOR_LENGTH;
                break;
            case ParserState::MATERIAL_DIFFUSE_COLOR:
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setDiffuseColor(parseColor(iterator));
                iterator += MIN_COLOR_LENGTH;
                break;
            case ParserState::MATERIAL_SPECULAR_COLOR:
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setSpecularColor(parseColor(iterator));
                iterator += MIN_COLOR_LENGTH;
                break;
            case ParserState::MATERIAL_SHININESS:
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setShininess(parseShininess(iterator));
                iterator += MIN_SHININESS_LENGHT;
                break;
            case ParserState::MATERIAL_AMBIENT_TEXTURE:
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setAmbientTexture(parseTexture(iterator));
                iterator += MIN_TEXTURE_NAME_LENGTH;
                break;
            case ParserState::MATERIAL_DIFFUSE_TEXTURE:
                parserState = ParserState::UNKNOWN;
                materials.material.getBack().setDiffuseTexture(parseTexture(iterator));
                iterator += MIN_TEXTURE_NAME_LENGTH;
                break;
        }
    }
}

GLuint Graphics::Tools::MtlParser::getCountMaterials(const String& mtlFileData) noexcept
{
    GLuint countMaterials = 0;
    char* iterator = const_cast<char*>(mtlFileData.getData());
    while ((*iterator != '\0') && (*iterator != '\n'))
    {
        if (strncmp(iterator, "#mtlc ", 6) == 0)
            sscanf_s(iterator + 6, "%u", &countMaterials);
        iterator++;
    }
    return countMaterials;
}

String Graphics::Tools::MtlParser::parseName(const char* iterator) noexcept
{
    std::size_t nameLength = 0;
    const char* tmpIterator = iterator;
    while ( (*tmpIterator != ' ') && (*tmpIterator != '\r') && (*tmpIterator != '\n') )
    {
        tmpIterator++;
        nameLength++;
    }
    return String(iterator, nameLength, mAllocator);
}

Graphics::Components::Texture2D Graphics::Tools::MtlParser::parseTexture(const char* iterator) noexcept
{
    GLuint textureWidth = 0;
    GLuint textureHeight = 0;
    const String textureName(parseName(iterator));
    String texturePath(mCurrentDirectory, mAllocator);
    texturePath.append(textureName);
    const String imageData(reinterpret_cast<const char*>(BmpReader::read(texturePath, textureWidth, textureHeight, mAllocator)), mAllocator);
    return Components::Texture2D(imageData, textureWidth, textureHeight);
}

GLfloat Graphics::Tools::MtlParser::parseShininess(const char* iterator) noexcept
{
    GLfloat shininess = 0.0f;
    sscanf_s(iterator, "%f", &shininess);
    return shininess;
}

Math::Vector3f Graphics::Tools::MtlParser::parseColor(const char* iterator) noexcept
{
    GLfloat r = 0.0f;
    GLfloat g = 0.0f;
    GLfloat b = 0.0f;
    sscanf_s(iterator, "%f %f %f", &r, &g, &b);
    return Math::Vector3f(r, g, b);
}
