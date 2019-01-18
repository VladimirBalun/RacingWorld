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

#include "../OpenGL.hpp"
#include "../../Math/Vectors/Vector3.hpp"

namespace Graphics { namespace Components {

    class Material 
    {
    public:
        Material() = default;
        Material(const Math::Vector3<GLfloat> ambient, const Math::Vector3<GLfloat> diffuse, const Math::Vector3<GLfloat> specular)
            : mAmbientColor(ambient), mDiffuseColor(diffuse), mSpecularColor(specular) {}
        Material(const Math::Vector3<GLfloat> ambient, const Math::Vector3<GLfloat> diffuse, const Math::Vector3<GLfloat> specular, GLfloat shininess)
            : mAmbientColor(ambient), mDiffuseColor(diffuse), mSpecularColor(specular), mShininess(shininess) {}
        Material(const Math::Vector3<GLfloat> ambient, const Math::Vector3<GLfloat> diffuse, const Math::Vector3<GLfloat> specular, GLfloat shininess, GLfloat opacity)
            : mAmbientColor(ambient), mDiffuseColor(diffuse), mSpecularColor(specular), mShininess(shininess), mOpacity(opacity) {}

        GLvoid setAmbientColor(const Math::Vector3<GLfloat>& ambientColor) noexcept;
        GLvoid setDiffuseColor(const Math::Vector3<GLfloat>& diffuseColor) noexcept;
        GLvoid setSpecularColor(const Math::Vector3<GLfloat>& specularColor) noexcept;
        GLvoid setShininess(GLfloat shininess) noexcept;
        GLvoid setOpacity(GLfloat opacity) noexcept;

        Math::Vector3<GLfloat> getAmbientColor() const noexcept;
        Math::Vector3<GLfloat> getDiffuseColor() const noexcept;
        Math::Vector3<GLfloat> getSpecularColor() const noexcept;
        GLfloat getShininess() const noexcept;
        GLfloat getOpacity() const noexcept;
    private:
        Math::Vector3<GLfloat> mAmbientColor;
        Math::Vector3<GLfloat> mDiffuseColor;
        Math::Vector3<GLfloat> mSpecularColor;
        GLfloat mShininess = 0.0f;
        GLfloat mOpacity = 1.0f;
    };

} }
