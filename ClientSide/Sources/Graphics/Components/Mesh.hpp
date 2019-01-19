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

#include <tuple>
#include <vector>

#include "../OpenGL.hpp"
#include "../../Math/Vectors.hpp"

namespace Graphics { namespace Components {

    class Mesh
    {
        typedef GLint VertexIndex;
        typedef GLint TextureIndex;
        typedef GLint NormalIndex;
    public:
        Mesh() = default;
        Mesh(std::vector<Math::Vector3<GLfloat>>&& normals,
            std::vector<Math::Vector4<GLfloat>>&& vertexes,
            std::vector<Math::Vector2<GLfloat>>&& textureCoordinates, 
            std::vector<std::tuple<VertexIndex, TextureIndex, NormalIndex>>&& indexes)
            : mNormals(std::move(normals)), mVertexes(std::move(vertexes)), mTextureCoordinates(std::move(textureCoordinates)), mIndexes(indexes) {}

        std::vector<Math::Vector3<GLfloat>>& getNormals() noexcept;
        std::vector<Math::Vector4<GLfloat>>& getVertexes() noexcept;
        std::vector<Math::Vector2<GLfloat>>& getTextureCoordinates() noexcept;
        std::vector<std::tuple<VertexIndex, TextureIndex, NormalIndex>>& getIndexes() noexcept;
    private:
        std::vector<Math::Vector3<GLfloat>> mNormals;
        std::vector<Math::Vector4<GLfloat>> mVertexes;
        std::vector<Math::Vector2<GLfloat>> mTextureCoordinates;
        std::vector<std::tuple<VertexIndex, TextureIndex, NormalIndex>> mIndexes;
    };

}}
