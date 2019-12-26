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

namespace objl
{
    struct Material;
}

namespace Core::Resources
{

    class Model;

    namespace Loaders
    {

        class OBJLoader
        {
        public:
            static bool load(Model& model, std::string_view model_file_path) noexcept;
        private:
            static void loadMaterial(const objl::Material& material, const std::string& material_path) noexcept;
            static void tryLoadImage(const std::string& image_filename, const std::string& image_path) noexcept;
        };

    }

}
