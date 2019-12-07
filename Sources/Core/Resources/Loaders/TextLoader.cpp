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
#include "TextLoader.hpp"

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

#include "../Text.hpp"
#include "../../Helpers/Debug.hpp"

bool Core::Resources::Loaders::TextLoader::load(Text& text, std::string_view text_file_path) noexcept
{
    boost::filesystem::ifstream input_stream(text_file_path.data());
    if (!input_stream.is_open())
    {
        LOG_WARNING("Text file '" + STR(text_file_path) + "' was not opened for reading.");
        return false;
    }

    const auto file_size = static_cast<std::size_t>(boost::filesystem::file_size(text_file_path.data()));
    std::string buffer{};
    buffer.resize(file_size + 1);
    input_stream.read(buffer.data(), file_size);
    text.setData(std::move(buffer));

    return true;
}

