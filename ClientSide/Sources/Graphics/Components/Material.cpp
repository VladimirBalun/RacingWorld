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

#include "Material.hpp"

GLvoid Graphics::Components::Material::setAmbientColor(const Math::Vector3<GLfloat>& ambientColor) noexcept
{
    mAmbientColor = ambientColor;
}

GLvoid Graphics::Components::Material::setDiffuseColor(const Math::Vector3<GLfloat>& diffuseColor) noexcept
{
    mDiffuseColor = diffuseColor;
}

GLvoid Graphics::Components::Material::setSpecularColor(const Math::Vector3<GLfloat>& specularColor) noexcept
{
    mSpecularColor = specularColor;
}

GLvoid Graphics::Components::Material::setShininess(GLfloat shininess) noexcept
{
    if (shininess < 0.0f)
        mShininess = 0.0f;
    else if (shininess > 1000.0f)
        mShininess = 1000.0f;
    else
        mShininess = shininess;
}

GLvoid Graphics::Components::Material::setOpacity(GLfloat opacity) noexcept
{
    if (opacity < 0.0f)
        mOpacity = 0.0f;
    else if (opacity > 1.0f)
        mOpacity = 1.0f;
    else
        mOpacity = opacity;
}

Math::Vector3<GLfloat> Graphics::Components::Material::getAmbientColor() const noexcept
{
    return mAmbientColor;
}

Math::Vector3<GLfloat> Graphics::Components::Material::getDiffuseColor() const noexcept
{
    return mDiffuseColor;
}

Math::Vector3<GLfloat> Graphics::Components::Material::getSpecularColor() const noexcept
{
    return mSpecularColor;
}

GLfloat Graphics::Components::Material::getShininess() const noexcept
{
    return mShininess;
}

GLfloat Graphics::Components::Material::getOpacity() const noexcept
{
    return mOpacity;
}
