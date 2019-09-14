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

#include "ModelLoader.hpp"

#include <OBJLoader.hpp>

#include "../Model.hpp"
#include "../../Managers/ResourceManager.hpp"

#define UNPACK_OBJ1_VEC2(__vector__) \
    ( (__vector__).X, (__vector__).Y )

#define UNPACK_OBJ1_VEC3(__vector__) \
    ( (__vector__).X, (__vector__).Y, (__vector__).Z )

bool Core::Resources::Loaders::OBJLoader::load(Model& model, const std::string& model_file_path) noexcept
{
    objl::Loader obj_loader{};
    const bool was_loaded = obj_loader.LoadFile(model_file_path);
    if (was_loaded)
    {
        auto model = std::make_shared<Model>();
        std::string model_name;
        for (const auto& mesh : obj_loader.LoadedMeshes)
        {


            
        }

        g_resource_manager.loadResource(model_name, model);
        return true;
    }

    return false;
}
