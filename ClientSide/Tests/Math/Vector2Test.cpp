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

#define CATCH_CONFIG_MAIN
#include "Catch.hpp"
#include "Vectors/Vector2.hpp"

TEST_CASE("Tests for Vector2", "[Vector2]")
{

    SECTION("Addition of the vectors")
    {
        Math::Vector2i first(1, 5);
        Math::Vector2i second(5, 1);
        REQUIRE((first + second) == Math::Vector2i(6, 6));
    }

    SECTION("Subtraction of the vectors")
    {
        Math::Vector2i first(1, 5);
        Math::Vector2i second(5, 1);
        REQUIRE((first - second) == Math::Vector2i(-4, 4));
    }

    SECTION("Multiplication vector on scalar")
    {
        Math::Vector2i vector(2, 5);
        REQUIRE((vector * 2) == Math::Vector2i(4, 10));
    }

    SECTION("Converting vector to array")
    {
        Math::Vector2i vector(1, 3);
        int array[Math::Vector2i::VECTOR_SIZE] = { 0 };
        vector.toArray(array);
        REQUIRE(vector.getX() == array[0]);
        REQUIRE(vector.getY() == array[1]);
    }

}
