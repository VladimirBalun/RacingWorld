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

#include "../Helpers/Macroses.hpp"

namespace Core { namespace Resources {

    struct IResource;

    class Text;
    class Model;
    class Sound;
    class Texture;
    class Material;

    FWD_DECL_SMART_PTRS_FOR_STRUCT(IResource)

    FWD_DECL_SMART_PTRS_FOR_CLASS(Text)
    FWD_DECL_SMART_PTRS_FOR_CLASS(Model)
    FWD_DECL_SMART_PTRS_FOR_CLASS(Sound)
    FWD_DECL_SMART_PTRS_FOR_CLASS(Texture)
    FWD_DECL_SMART_PTRS_FOR_CLASS(Material)

}}
