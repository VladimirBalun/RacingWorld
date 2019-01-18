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

#include "../Tools/HardwareBuffers.hpp"
#include "../Tools/ShaderProgram.hpp"

namespace Graphics { namespace Components
{
    enum TypeRender
    {
        TR_WIRE  = 0x1B01,
        TR_SOLID = 0x1B02,
        TR_POINT = 0x1B00,
    };

    class SimpleMesh
    {
    public:
        SimpleMesh();
        void createCube(float size);
        void createTetrahedron(float size);
        void drawMesh(TypeRender tr);
        ~SimpleMesh();
    private:
        Graphics::Tools::HardwareBuffers* mesh;
        Graphics::Tools::ShaderProgram *shader;
        int positionLocation;
    };
 } }