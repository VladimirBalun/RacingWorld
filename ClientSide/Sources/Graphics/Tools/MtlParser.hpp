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
        Vector<const char*> name;
        Vector<Components::Material> material;
    };

    class MtlParser
    {
    public:
        static void parse(const String& currentDirectory, const String& mtlFileName,
            MaterialsData& materials, Memory::Allocators::LinearAllocator& allocator) noexcept;
    private:
        static void parseMaterial(const String& currentDirectory, char* iterator, MaterialsData& materials) noexcept;
        static GLfloat parserShininess(char* line) noexcept;
        static void parseColor(char* line, Math::Vector3f& color) noexcept;
    };

} }