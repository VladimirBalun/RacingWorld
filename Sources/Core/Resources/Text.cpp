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
#include "Text.hpp"

#include "Loaders/TextLoader.hpp"

std::string_view Core::Resources::Text::getData() const noexcept
{
    return m_text_data;
}

bool Core::Resources::Text::load(std::string_view text_path) noexcept
{
    return Loaders::TextLoader::load(*this, text_path);
}

void Core::Resources::Text::setData(std::string&& data) noexcept
{
    m_text_data = std::move(data);
}
