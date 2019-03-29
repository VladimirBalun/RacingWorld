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

#include "Texture2D.hpp"
#include "../OpenGL.hpp"
#include "../../Math/Vectors/Vector3.hpp"

namespace Graphics { namespace Components {

    class Material 
    {
    public:
        explicit Material() noexcept = default;
        explicit Material(const Math::Vector3<GLfloat>& ambient, const Math::Vector3<GLfloat>& diffuse,
            const Math::Vector3<GLfloat>& specular, GLfloat shininess = 32.0f) noexcept
            : mAmbientColor(ambient), mDiffuseColor(diffuse), mSpecularColor(specular), mShininess(shininess) {}
        explicit Material(const Math::Vector3<GLfloat>& ambient, const Math::Vector3<GLfloat>& diffuse,
            const Math::Vector3<GLfloat>& specular, const Texture2D& texture, GLfloat shininess = 32.0f) noexcept
            : mAmbientColor(ambient), mDiffuseColor(diffuse), mSpecularColor(specular), mTexture(texture), mShininess(shininess) {}
        GLboolean isInitialized() const noexcept;
        GLboolean isExistTexture() const noexcept;
        GLvoid setAmbientColor(const Math::Vector3<GLfloat>& color) noexcept;
        GLvoid setDiffuseColor(const Math::Vector3<GLfloat>& color) noexcept;
        GLvoid setSpecularColor(const Math::Vector3<GLfloat>& color) noexcept;
        const Math::Vector3<GLfloat>& getAmbientColor() const noexcept;
        const Math::Vector3<GLfloat>& getDiffuseColor() const noexcept;
        const Math::Vector3<GLfloat>& getSpecularColor() const noexcept;
        const Texture2D& getTexture() const noexcept;
        GLfloat getShininess() const noexcept;
    private:
        Math::Vector3<GLfloat> mAmbientColor;
        Math::Vector3<GLfloat> mDiffuseColor;
        Math::Vector3<GLfloat> mSpecularColor;
        GLfloat mShininess = 0.0F;
        Texture2D mTexture;
    };

} }
