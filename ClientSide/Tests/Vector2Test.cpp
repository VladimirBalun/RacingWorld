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
