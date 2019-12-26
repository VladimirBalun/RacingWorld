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

#include "Helpers/Macroses.hpp"

namespace Core::Resources 
{

    struct IResource;

    class Map;
    class Text;
    class Model;
    class Sound;
    class Image;
    class Material;

    using VertexShader = Text;
    using FragmentShader = Text;

    DECL_SMART_PTRS(IResource)

    DECL_SMART_PTRS(Map)
    DECL_SMART_PTRS(Text)
    DECL_SMART_PTRS(Model)
    DECL_SMART_PTRS(Sound)
    DECL_SMART_PTRS(Image)
    DECL_SMART_PTRS(Material)

    DECL_SMART_PTRS_BY_TYPEDEF(Text, VertexShader)
    DECL_SMART_PTRS_BY_TYPEDEF(Text, FragmentShader)

}
