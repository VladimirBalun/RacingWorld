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

#include "BmpReader.hpp"

#define BMP_HEADER_SIZE 54

#define WIDTH_POSITION 18
#define HEIGHT_POSITION 22

// TODO: at the moment read only 24x bit bmp images, need to add reading other formats
unsigned char* Graphics::Tools::BmpReader::read(const char* bmpFileName, GLuint& width, GLuint& height, Memory::Allocators::LinearAllocator& allocator) noexcept
{
    FILE* inputStream;
    fopen_s(&inputStream, bmpFileName, "rb");
    if (!inputStream)
    {
        LOG_WARNING("File was not opened.");
        return nullptr;
    }

    unsigned char info[BMP_HEADER_SIZE];
    fread(info, sizeof(unsigned char), BMP_HEADER_SIZE, inputStream);

    width = *(GLuint*)&info[WIDTH_POSITION];
    height = *(GLuint*)&info[HEIGHT_POSITION];

    GLuint size = 3 * width * height;
    unsigned char* data = static_cast<unsigned char*>(allocator.allocate(size));
    fread(data, sizeof(unsigned char), size, inputStream);
    fclose(inputStream);

    return data;
}
