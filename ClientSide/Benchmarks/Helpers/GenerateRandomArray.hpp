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
#include <random>

template <typename Type>
void fillArray(Type * array, std::size_t array_size)
{
    std::random_device rd;

    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(0, 25);

    for (std::size_t i = 0; i < array_size; i++)
		array[i] = std::move(Type(float(dist(e2)), float(dist(e2)), float(dist(e2))));
}