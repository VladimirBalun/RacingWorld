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
#include "Vectors/Vector3.hpp"

TEST_CASE("Tests for Vector3", "[Vector3]")
{

	SECTION("Addition of the vectors")
	{
		Math::Vector3i first(1, 3, 2);
		Math::Vector3i second(2, 4, 6);
		REQUIRE((first + second) == Math::Vector3i(3, 7, 8));
	}

	SECTION("Subtraction of the vectors")
	{
		Math::Vector3i first(2, 3, 5);
		Math::Vector3i second(1, 2, 3);
		REQUIRE((first - second) == Math::Vector3i(1, 1, 2));
	}

	SECTION("Multiplication vector in scalar")
	{
		Math::Vector3i vector(1, 3, 4);
		REQUIRE((vector * 2) == Math::Vector3i(2, 6, 8));
	}

	SECTION("Converting vector to array")
	{
		Math::Vector3i vector(1, 3, 2);
		int array[Math::Vector3i::VECTOR_SIZE] = { 0 };
		vector.toArray(array);
		REQUIRE(vector.getX() == array[0]);
		REQUIRE(vector.getY() == array[1]);
		REQUIRE(vector.getZ() == array[2]);
	}

}
