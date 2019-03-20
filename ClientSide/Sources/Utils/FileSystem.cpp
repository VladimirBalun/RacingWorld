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

char* Utils::readFile(const char* fullFileName, Memory::Allocators::LinearAllocator& allocator) noexcept
{
    FILE* inputStream = NULL;
    fopen_s(&inputStream, fullFileName, "rb");
    if (!inputStream)
    {
        LOG_WARNING("File was not opened.");
        return nullptr;
    }

    std::fseek(inputStream, 0, SEEK_END);
    long fileSize = std::ftell(inputStream) + 1;
    std::rewind(inputStream);

    char* buffer = reinterpret_cast<char*>(allocator.allocate(fileSize));
    std::size_t countReadSymbols = std::fread(buffer, sizeof(char), fileSize, inputStream);
    buffer[countReadSymbols] = '\0';
    std::fclose(inputStream);

    return buffer;
}

bool Utils::writeFile(const char* fileName, const char* data) noexcept
{
	FILE * outputStream = NULL;
	fopen_s(&outputStream, fileName, "a");
	if (!outputStream) 
	{
		LOG_WARNING("File was not opened for writing.");
		return false;
	}

	int countWritedBytes = fprintf(outputStream, "%s\n", data);
	fclose(outputStream);
	return countWritedBytes >= 0;
}

bool Utils::createFile(const char* fileName) noexcept
{
    return CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL) != INVALID_HANDLE_VALUE;
}

bool Utils::removeFile(const char* fileName) noexcept
{
    return DeleteFile(fileName) != 0;
}

bool Utils::copyFile(const char* fromfileName, const char* tofileName) noexcept
{
    return CopyFile(fromfileName, tofileName, FALSE) != 0;
}

bool Utils::moveFile(const char* fileName, const char* newfileName) noexcept
{
    return MoveFile(fileName, newfileName) != 0;
}

bool Utils::renameFile(const char* oldfileName, const char* newfileName) noexcept
{
    return rename(oldfileName, newfileName) == 0;
}

bool Utils::createSymLink(const char* fileName, const char* linkName) noexcept
{
    return CreateSymbolicLink(linkName, fileName, 0) != 0;
}

bool Utils::createHardLink(const char* fileName, const char* linkName) noexcept
{
    return CreateHardLink(linkName, fileName, NULL) != 0;
}
