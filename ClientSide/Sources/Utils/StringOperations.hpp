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

#include <cstring>

#include "../Memory/Allocators/Allocator.hpp"

namespace Utils {

    template<typename ... SourceStrings, typename = std::enable_if_t<(std::is_convertible_v<SourceStrings, const char *> && ...)>>
    void concatenateStringsToString(char* destinationString, std::size_t lenghtDestinationString, SourceStrings ... sourceStrings) noexcept
    {
        for (const char* currentString : { sourceStrings ... })
            strcat_s(destinationString, lenghtDestinationString, currentString);
    }

    template<typename ... SourceStrings, typename = std::enable_if_t<(std::is_convertible_v<SourceStrings, const char *> && ...)>>
    void concatenateStringsToEmptyString(char* destinationString, std::size_t lenghtDestinationString, SourceStrings ... sourceStrings) noexcept
    {
        std::fill(destinationString, destinationString + lenghtDestinationString, 0);
        for (const char* currentString : { sourceStrings ... })
            strcat_s(destinationString, lenghtDestinationString, currentString);
    }

    template<typename AllocatorType, typename ... SourceStrings, typename = std::enable_if_t<(std::is_convertible_v<SourceStrings, const char *> && ...)>>
    char* createStringFromStrings(std::size_t lengthString, AllocatorType& allocator, SourceStrings ... sourceStrings) noexcept
    {
        char* newString = reinterpret_cast<char*>(allocator.allocate(lengthString + 1));
        Utils::concatenateStringsToEmptyString(newString, lengthString + 1, sourceStrings ...);
        return newString;
    }

    inline void getParentPathFromString(char* fullPath) noexcept
    {
        char* lastSlash = strrchr(fullPath, '\\');
        if (lastSlash)
            *lastSlash = 0;
    }

    template<typename AllocatorType>
    const char* getPathWithoutFilename(const char* fullPath, AllocatorType& allocator) noexcept
    {
        const std::size_t fullPathLength = strlen(fullPath);
        const char* lastSlash = strrchr(fullPath, '\\');
        if (lastSlash)
        {
            const std::size_t lengthPathWithoutFileName = (std::size_t)(lastSlash - fullPath + 2);
            const void* memoryForString = allocator.allocate(lengthPathWithoutFileName);
            const char* pathWithoutFileName = static_cast<const char*>(memoryForString);
            memcpy((void*) pathWithoutFileName, (void*) fullPath, lengthPathWithoutFileName - 1);
            return pathWithoutFileName;
        }
        else
        {
            LOG_WARNING("Could not get path without filename.");
            return nullptr;
        }
    }

}
