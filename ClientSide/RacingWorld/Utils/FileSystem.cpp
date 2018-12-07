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

#include "FileSystem.h"

std::string read_file(const std::string& file_name)
{
    std::stringstream buffer;
    std::ifstream input_stream(file_name, std::ifstream::badbit);
    try
    {
        buffer << input_stream.rdbuf();
        input_stream.close();
        return buffer.str();
    }
    catch (const std::ifstream::failure& e)
    {
        LOG_WARNING("File: \"" + file_name + "\" was not read. Cause:" + e.what());
        return "";
    }
}
