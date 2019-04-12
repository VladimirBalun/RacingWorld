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

#pragma once

#include "BmpReader.hpp"
#include "../Components/Material.hpp"
#include "../../Utils/FileSystem.hpp"
#include "../../Math/Vectors/Vector3.hpp"
#include "../../Utils/DataStructures/Vector.hpp"
#include "../../Utils/DataStructures/String.hpp"
#include "../../Memory/Allocators/LinearAllocator.hpp"

namespace Graphics { namespace Tools {

    // DOD design
    struct MaterialsData
    {
        // TODO: need to calculate capacity for vectors
        Vector<String> name;
        Vector<Components::Material> material;
    };

    // State machine
    class MtlParser
    {
    public:
        explicit MtlParser(const String& currentDirectory, const String& mtlFileName)
            : mCurrentDirectory(currentDirectory), mMtlFileName(mtlFileName), mAllocator(1000) {}
        GLvoid parse(MaterialsData& materials) noexcept;
    private:
        GLuint getCountMaterials(char* mtlFileData) noexcept;
        String parseName(const char* iterator) noexcept;
        Components::Texture2D parseTexture(const char* iterator) noexcept;
        Math::Vector3f parseColor(const char* iterator) noexcept;
        GLfloat parseShininess(const char* iterator) noexcept;
    private:
        const String& mMtlFileName;
        const String& mCurrentDirectory;
        Memory::Allocators::LinearAllocator mAllocator;
    };

} }