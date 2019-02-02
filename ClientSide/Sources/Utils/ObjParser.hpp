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

#include "FileSystem.hpp"
#include "../Memory/LinearAllocator.hpp"
#include "../Graphics/Components/Mesh.hpp"

namespace Utils {

    class ObjParser 
    {
    public:
        static Graphics::Components::Mesh parse(const char* objFileName, Memory::LinearAllocator& allocator) noexcept;
    private:
        static void parseVertices(const char* line, Math::Vector4f* vertices) noexcept;
        static void parseTextureCoordinates(const char* line, Math::Vector2f* textureCoordinates) noexcept;
        static void parseNormals(const char* line, Math::Vector3f* normals) noexcept;
        static void parseFaceElementIndexes(const char* line, Math::Vector3i* faceElementIndexes) noexcept;
        static Graphics::Components::Mesh createMesh(const Math::Vector4f* vertices, const Math::Vector2f* textureCoordinates,
            const Math::Vector3f* normals, const Math::Vector3i* faceElementIndexes, std::size_t countFaceElementIndexes, Memory::LinearAllocator& allocator) noexcept;
    };

}
