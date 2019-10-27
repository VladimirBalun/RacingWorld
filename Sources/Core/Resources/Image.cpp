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
#include "Image.hpp"

#include <boost/filesystem/convenience.hpp>
#include <SOIL.h>

#include "Helpers/Debug.hpp"
#include "Loaders/ImageLoader.hpp"

void Core::Resources::Image::setWidth(std::uint16_t width) noexcept
{
    m_width = width;
}

void Core::Resources::Image::setHeight(std::uint16_t height) noexcept
{
    m_height = height;
}

void Core::Resources::Image::setData(unsigned char* data) noexcept
{
    m_data = data;
}

std::uint16_t Core::Resources::Image::getWidth() const noexcept
{
    return m_width;
}

std::uint16_t Core::Resources::Image::getHeight() const noexcept
{
    return m_height;
}

const unsigned char* Core::Resources::Image::getData() const noexcept
{
    return m_data;
}

bool Core::Resources::Image::load(const std::string& image_path) noexcept
{
    using ImageLoader = std::function<bool(Image&, const std::string&)>;
    static const std::unordered_map<std::string_view, ImageLoader> available_loaders = {
        { ".png", std::bind(&Loaders::PNGLoader::load, std::placeholders::_1, std::placeholders::_2) },
        { ".jpg", std::bind(&Loaders::JPGLoader::load, std::placeholders::_1, std::placeholders::_2) }
    };

    const std::string extension = boost::filesystem::extension(image_path);
    const auto& it = available_loaders.find(extension);
    if (it != end(available_loaders))
    {
        if (const ImageLoader& image_loader = it->second)
        {
            return image_loader(*this, image_path);
        }
    }
    else
    {
        LOG_WARNING("Unsupported extension for image loaders: " + image_path);
    }

    return false;
}

Core::Resources::Image::~Image()
{
    SOIL_free_image_data(m_data);
}
