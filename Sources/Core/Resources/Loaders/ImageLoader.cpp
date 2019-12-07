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

#include "PrecompiledHeader.hpp"
#include "ImageLoader.hpp"

#include <SOIL.h>

#include "../Image.hpp"

bool Core::Resources::Loaders::ImageLoader::load(Image& image, std::string_view image_path) noexcept
{
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = SOIL_load_image(image_path.data(), &image_width, &image_height, 0, SOIL_LOAD_RGB);
    if (image_data)
    {
        image.setData(image_data);
        image.setWidth(static_cast<std::uint16_t>(image_width));
        image.setHeight(static_cast<std::uint16_t>(image_height));
        return true;
    }

    return false;
}
