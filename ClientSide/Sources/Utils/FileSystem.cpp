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

#include "FileSystem.hpp"

std::vector<char> Utils::readFile(const std::string& filename) noexcept
{
    const boost::filesystem::path full_path = filename;
    boost::filesystem::ifstream input_stream(filename);
    if (!input_stream.is_open())
    {
        LOG_WARNING("File was not opened for reading.");
        return std::vector<char>{};
    }

    const std::size_t file_size = static_cast<std::size_t>(boost::filesystem::file_size(full_path));
    std::vector<char> buffer(file_size + 1);
    input_stream.read(buffer.data(), file_size);
    return buffer;
}
