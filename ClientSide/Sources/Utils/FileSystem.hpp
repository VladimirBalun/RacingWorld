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

#include <cstdio>
#include <Windows.h>
#include <functional>

#include "Debug.hpp"
#include "../Memory/Allocators/Allocator.hpp"

namespace Utils {

    char* readFile(const char* fileName, std::function<void*(std::size_t, std::size_t)> allocateFunction) noexcept;

    bool createFile(const char* fileName) noexcept;
    bool removeFile(const char* fileName) noexcept;
    bool copyFile(const char* fromfileName, const char* tofileName) noexcept;
    bool moveFile(const char* fileName, const char* newfileName) noexcept;
    bool renameFile(const char* oldfileName, const char* newfileName) noexcept;

    bool createSymLink(const char* fileName, const char* linkName) noexcept;
    bool createHardLink(const char* fileName, const char* linkName) noexcept;

}
