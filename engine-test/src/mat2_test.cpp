#include "catch.hpp"
#include "engine.h"

using namespace engine;

TEST_CASE("Test mat2 class", "[mat2]")
{
	mat2 m1;
	mat2 A(
		1, 2,
		3, 4);
	mat2 B(
		2, 2,
		4, 5);
	mat2 C(
		1, 4,
		3, 3);
	mat2 id(
		1, 0,
		0, 1);
	vec2 v1(1, 2);

	SECTION("mat2 constructors")
	{
		for (int i = 0; i < mat2::MAT_SIZE; ++i)
		{
			REQUIRE(m1.data[i] == 0);
		}

		REQUIRE(A.data[0] == 1);
		REQUIRE(A.data[1] == 3);
		REQUIRE(A.data[2] == 2);
		REQUIRE(A.data[3] == 4);
	}

	SECTION("mat2 operator=")
	{
		m1 = A;
		REQUIRE(m1.data[0] == 1);
		REQUIRE(m1.data[1] == 3);
		REQUIRE(m1.data[2] == 2);
		REQUIRE(m1.data[3] == 4);
	}

	SECTION("mat2 operator==")
	{
		REQUIRE(m1 == m1);
		REQUIRE(A == A);
		REQUIRE(!(m1 == A));
	}

	SECTION("mat2 operator!=")
	{
		REQUIRE(!(m1 != m1));
		REQUIRE(!(A != A));
		REQUIRE(m1 != A);
	}

	SECTION("mat2 operator+")
	{
		REQUIRE((m1 + A) == A);
		REQUIRE((A + A) == mat2(2, 4, 6, 8));
	}

	SECTION("mat2 operator-")
	{
		REQUIRE((m1 - A) == mat2(-1, -2, -3, -4));
		REQUIRE((A - A) == mat2());
	}

	SECTION("mat2 operator-")
	{
		REQUIRE(-A == mat2(-1, -2, -3, -4));
		REQUIRE(-m1 == mat2());
	}

	SECTION("mat2 operator* mat2")
	{
		REQUIRE(id * id == id);
		REQUIRE(m1 * id == m1);
		REQUIRE(A * id == A);
	}

	SECTION("mat2 operator* vec2")
	{
		REQUIRE(id * v1 == v1);
		REQUIRE(A * v1 == vec2(5, 11));
	}

	SECTION("mat2 operator* scalar")
	{
		REQUIRE(id * 2 == mat2(2, 0, 0, 2));
		REQUIRE(A * 2 == mat2(2, 4, 6, 8));
	}

	SECTION("mat2 determinant")
	{
		REQUIRE(determinant(id) == 1);
		REQUIRE(determinant(m1) == 0);
		REQUIRE(determinant(A) == -2);
	}

	SECTION("mat2 transpose")
	{
		REQUIRE(transpose(id) == id);
		REQUIRE(transpose(m1) == m1);
		REQUIRE(transpose(A) == mat2(1, 3, 2, 4));
	}

	SECTION("mat2 properties")
	{
		REQUIRE(inverse(inverse(A)) == A);
		REQUIRE(transpose(inverse(A)) == inverse(transpose(A)));
		// inverse
		REQUIRE(inverse(2 * A) == .5f * inverse(A));
		REQUIRE(inverse(id) == id);
		REQUIRE(inverse(A) * A == id);
		// transpose
		REQUIRE(transpose(transpose(A)) == A);
		REQUIRE(transpose(A + B) == transpose(A) + transpose(B));
		REQUIRE(transpose(2 * A) == 2 * transpose(A));
		REQUIRE(transpose(A * B) == transpose(B) * transpose(A));
		REQUIRE(determinant(transpose(A)) == determinant(A));
		// comutativity
		REQUIRE(A + B == B + A);
		REQUIRE(A * B != B * A);
		// associativity
		REQUIRE((A * B) * C == A * (B * C));
		REQUIRE((A + B) + C == A + (B + C));
		// distributivity
		REQUIRE(A * (B + C) == A * B + A * C);
		REQUIRE((B + C) * A == B * A + C * A);
		REQUIRE(2 * (B + C) == 2 * B + 2 * C);
		REQUIRE((4 + 3) * A == 4 * A + 3 * A);
	}
}