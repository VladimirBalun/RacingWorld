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
#include "Vectors/Vector4.hpp"

TEST_CASE("Tests for Vector4", "[Vector4]")
{

	SECTION("Addition of the vectors")
	{
		Math::Vector4i first(1, 3, 4, 1);
		Math::Vector4i second(2, 4, 6, 0);
		REQUIRE((first + second) == Math::Vector4i(3, 7, 10, 1));
	}

	SECTION("Subtraction of the vectors")
	{
		Math::Vector4i first(2, 3, 5, 1);
		Math::Vector4i second(1, 2, 3, 1);
		REQUIRE((first - second) == Math::Vector4i(1, 1, 2, 1));
	}

	SECTION("Multiplication vector on scalar")
	{
		Math::Vector4i vector(1, 3, 4, 1);
		REQUIRE((vector * 2) == Math::Vector4i(2, 6, 8, 1));
	}

	SECTION("Converting vector to array")
	{
		Math::Vector4i vector(1, 3, 2, 1);
		int array[Math::Vector4i::VECTOR_SIZE] = { 0 };
		vector.toArray(array);
		REQUIRE(vector.getX() == array[0]);
		REQUIRE(vector.getY() == array[1]);
		REQUIRE(vector.getZ() == array[2]);
		REQUIRE(vector.getW() == array[3]);
	}

}
