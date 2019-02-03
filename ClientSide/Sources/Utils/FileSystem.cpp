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

char* Utils::readFile(const char* fullFileName, std::function<void*(std::size_t, std::size_t)> allocateFunction) noexcept
{
    FILE* file = NULL;
    fopen_s(&file, fullFileName, "rb");
    if (!file)
    {
        LOG_WARNING("File was not opened.");
        return nullptr;
    }

    std::fseek(file, 0, SEEK_END);
    std::size_t fileSize = std::ftell(file) + 1;
    std::rewind(file);

    char* buffer = reinterpret_cast<char*>(allocateFunction(fileSize, 0));
    std::size_t countReadSymbols = std::fread(buffer, sizeof(char), fileSize, file);
    buffer[countReadSymbols] = '\0';
    std::fclose(file);
    return buffer;
}
