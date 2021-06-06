#include "catch.hpp"
#include "engine.h"

using namespace engine;

TEST_CASE("Test mat3 class", "[mat3]")
{
	mat3 Z;
	mat3 A(
		1, 3, 2,
		1, 0, 0,
		1, 2, 2);
	mat3 B(
		0, 0, 5,
		7, 5, 0,
		2, 1, 1);
	mat3 C(
		1, 1, 1,
		1, -1, 1,
		1, -1, 2);
	mat3 id(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	vec3 v1(1, 2, 3);

	SECTION("mat3 constructors")
	{
		for (int i = 0; i < mat3::MAT_SIZE; ++i)
		{
			REQUIRE(Z.data[i] == 0);
		}

		REQUIRE(A.data[0] == 1);
		REQUIRE(A.data[1] == 1);
		REQUIRE(A.data[2] == 1);

		REQUIRE(A.data[3] == 3);
		REQUIRE(A.data[4] == 0);
		REQUIRE(A.data[5] == 2);

		REQUIRE(A.data[6] == 2);
		REQUIRE(A.data[7] == 0);
		REQUIRE(A.data[8] == 2);
	}

	SECTION("mat3 operator=")
	{
		Z = A;
		REQUIRE(Z.data[0] == 1);
		REQUIRE(Z.data[1] == 1);
		REQUIRE(Z.data[2] == 1);

		REQUIRE(Z.data[3] == 3);
		REQUIRE(Z.data[4] == 0);
		REQUIRE(Z.data[5] == 2);

		REQUIRE(Z.data[6] == 2);
		REQUIRE(Z.data[7] == 0);
		REQUIRE(Z.data[8] == 2);
	}

	SECTION("mat3 operator==")
	{
		REQUIRE(Z == Z);
		REQUIRE(A == A);
		REQUIRE(!(Z == A));
	}

	SECTION("mat3 operator!=")
	{
		REQUIRE(!(Z != Z));
		REQUIRE(!(A != A));
		REQUIRE(Z != A);
	}

	SECTION("mat3 operator+")
	{
		REQUIRE((Z + A) == A);
		REQUIRE((A + A) == mat3(2, 6, 4, 2, 0, 0, 2, 4, 4));
	}

	SECTION("mat3 operator-")
	{
		REQUIRE((Z - A) == mat3(-1, -3, -2, -1, 0, 0, -1, -2, -2));
		REQUIRE((A - A) == mat3());
	}

	SECTION("mat3 operator-")
	{
		REQUIRE(-A == mat3(-1, -3, -2, -1, 0, 0, -1, -2, -2));
		REQUIRE(-Z == mat3());
	}

	SECTION("mat3 operator* mat3")
	{
		REQUIRE(id * id == id);
		REQUIRE(Z * id == Z);
		REQUIRE(A * id == A);
	}

	SECTION("mat3 operator* vec2")
	{
		REQUIRE(id * v1 == v1);
		REQUIRE(A * v1 == vec3(13, 1, 11));
	}

	SECTION("mat3 operator* scalar")
	{
		REQUIRE(id * 2 == mat3(2, 0, 0, 0, 2, 0, 0, 0, 2));
		REQUIRE(A * 2 == mat3(2, 6, 4, 2, 0, 0, 2, 4, 4));
	}

	SECTION("mat3 determinant")
	{
		REQUIRE(determinant(id) == 1);
		REQUIRE(determinant(Z) == 0);
		REQUIRE(determinant(A) == -2);
	}

	SECTION("mat3 transpose")
	{
		REQUIRE(transpose(id) == id);
		REQUIRE(transpose(Z) == Z);
		REQUIRE(transpose(A) == mat3(1, 1, 1, 3, 0, 2, 2, 0, 2));
	}

	SECTION("mat3 properties")
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
