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

#include <string>
#include <sstream>
#include <iostream>

#include "../OpenGL.hpp"
#include "../../Utils/FileSystem.hpp"
#include "../../Math/Vector2.hpp"
#include "../../Math/Vector3.hpp"
#include "../../Math/Vector4.hpp"
#include "../../Math/Matrix2x2.hpp"
#include "../../Math/Matrix3x3.hpp"
#include "../../Math/Matrix4x4.hpp"

namespace Graphics { namespace Utils {

    class ShaderProgram 
    {
    public:
        explicit ShaderProgram(const char* vShaderFileName, const char* fShaderFileName);
        ~ShaderProgram();
        void destroyProgram();
        void destroyProgramID(unsigned int idProgram);
        GLvoid setProgram();
        GLvoid unsetProgram();
        GLuint getProgram();

        GLuint getAttribLocation(const char* name);
        GLuint getUniformLocation(const char* name) const;

        void setInt(const char* name, int value) const;
        void setBool(const char* name, bool value) const;
        void setFloat(const char* name, float value) const;

        void setVector2(const char* name, float v0, float v1) const;
        void setVector3(const char* name, float v0, float v1, float v2) const;
        void setVector4(const char* name, float v0, float v1, float v2, float v3) const;

        void setVector2(const char* name, const Math::Vector2<float> &value) const;
        void setVector3(const char* name, const Math::Vector3<float> &value) const;
        void setVector4(const char* name, const Math::Vector4<float> &value) const;

        void setMatrix2(const char* name, const Math::Matrix2x2<float> &value) const;
        void setMatrix3(const char* name, const Math::Matrix3x3<float> &value) const;
        void setMatrix4(const char* name, const Math::Matrix4x4<float> &value) const;


    private:
        GLuint _compileShader(const char* shaderSourcCode, GLint shaderType);
        GLvoid _linkShaders(GLuint vertexShader, GLuint fragmentShader);
    private:
        GLuint mProgram;
    };

}}
