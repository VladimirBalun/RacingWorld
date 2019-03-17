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
#include "Vectors.hpp"

TEST_CASE("Tests for Vectors", "[Vectors]")
{

	SECTION("Vector multiplication of the 3D vectors")
	{
		Math::Vector3i first3(1, 2, 2);
		Math::Vector3i second3(2, 1, 3);
		Math::Vector3i mul3 = Math::cross(first3, second3);
		REQUIRE(mul3.getX() == 4);
		REQUIRE(mul3.getY() == 1);
		REQUIRE(mul3.getZ() == -3);
	}

	SECTION("Vector multiplication of the 4D vectors")
	{
		Math::Vector4i first4(4, 0, 1, 1);
		Math::Vector4i second4(0, 1, 3, 0);
		Math::Vector4i mul4 = Math::cross(first4, second4);
		REQUIRE(mul4.getX() == -1);
		REQUIRE(mul4.getY() == -12);
		REQUIRE(mul4.getZ() == 4);
	}

	SECTION("Normalization of the 2D vector")
	{
		Math::Vector2i vector2(3, 4);
		vector2.normalize();
		REQUIRE(vector2.getX() == (3 / 5));
		REQUIRE(vector2.getY() == (4 / 5));
	}

	SECTION("Normalization of the 3D vector")
	{
		Math::Vector3i vector3(0, 3, 4);
		vector3.normalize();
		REQUIRE(vector3.getX() == 0);
		REQUIRE(vector3.getY() == (3 / 5));
		REQUIRE(vector3.getZ() == (4 / 5));
	}

	SECTION("Normalization of the 4D vector")
	{
		Math::Vector4i vector4(1, 0, 0, 1);
		vector4.normalize();
		REQUIRE(vector4.getX() == 1);
		REQUIRE(vector4.getY() == 0);
		REQUIRE(vector4.getZ() == 0);
		REQUIRE(vector4.getW() == 1);
	}

	SECTION("Scalar multiplication of the 2D vectors")
	{
		Math::Vector2i first2(1, 3);
		Math::Vector2i second2(2, 2);
		REQUIRE(Math::dot(first2, second2) == 8);
	}

	SECTION("Scalar multiplication of the 3D vectors")
	{
		Math::Vector3i first3(0, 2, 1);
		Math::Vector3i second3(1, 2, 4);
		REQUIRE(Math::dot(first3, second3) == 8);
	}

	SECTION("Scalar multiplication of the 4D vectors")
	{
		Math::Vector4i first4(3, 4, 0, 1);
		Math::Vector4i second4(1, 2, 1, 0);
		REQUIRE(Math::dot(first4, second4) == 11);
	}

}
