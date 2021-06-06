#include "catch.hpp"
#include "engine.h"

using namespace engine;

TEST_CASE("Test mat4 class", "[mat4]")
{
	mat4 Z;
	mat4 A(
		1, 3, 2, 0,
		1, 0, 0, 0,
		1, 2, 2, 0,
		0, 0, 0, 1);
	mat4 B(
		0, 0, 5, 0,
		7, 5, 0, 0,
		2, 1, 1, 0,
		0, 0, 0, 1);
	mat4 C(
		1, 1, 1, 0,
		1, -1, 1, 0,
		1, -1, 2, 0,
		0, 0, 0, 1);
	mat4 id(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	vec4 v1(1, 2, 3, 1);

	SECTION("mat4 constructors")
	{
		for (int i = 0; i < mat4::MAT_SIZE; ++i)
		{
			REQUIRE(Z.data[i] == 0);
		}

		REQUIRE(A.data[0] == 1);
		REQUIRE(A.data[1] == 1);
		REQUIRE(A.data[2] == 1);
		REQUIRE(A.data[3] == 0);

		REQUIRE(A.data[4] == 3);
		REQUIRE(A.data[5] == 0);
		REQUIRE(A.data[6] == 2);
		REQUIRE(A.data[7] == 0);

		REQUIRE(A.data[8] == 2);
		REQUIRE(A.data[9] == 0);
		REQUIRE(A.data[10] == 2);
		REQUIRE(A.data[11] == 0);

		REQUIRE(A.data[12] == 0);
		REQUIRE(A.data[13] == 0);
		REQUIRE(A.data[14] == 0);
		REQUIRE(A.data[15] == 1);
	}

	SECTION("mat4 operator=")
	{
		Z = A;
		REQUIRE(Z.data[0] == 1);
		REQUIRE(Z.data[1] == 1);
		REQUIRE(Z.data[2] == 1);
		REQUIRE(Z.data[3] == 0);

		REQUIRE(Z.data[4] == 3);
		REQUIRE(Z.data[5] == 0);
		REQUIRE(Z.data[6] == 2);
		REQUIRE(Z.data[7] == 0);

		REQUIRE(Z.data[8] == 2);
		REQUIRE(Z.data[9] == 0);
		REQUIRE(Z.data[10] == 2);
		REQUIRE(Z.data[11] == 0);

		REQUIRE(Z.data[12] == 0);
		REQUIRE(Z.data[13] == 0);
		REQUIRE(Z.data[14] == 0);
		REQUIRE(Z.data[15] == 1);
	}

	SECTION("mat4 operator==")
	{
		REQUIRE(Z == Z);
		REQUIRE(A == A);
		REQUIRE(!(Z == A));
	}

	SECTION("mat4 operator!=")
	{
		REQUIRE(!(Z != Z));
		REQUIRE(!(A != A));
		REQUIRE(Z != A);
	}

	SECTION("mat4 operator+")
	{
		REQUIRE((Z + A) == A);
		REQUIRE((A + A) == mat4(2, 6, 4, 0, 2, 0, 0, 0, 2, 4, 4, 0, 0, 0, 0, 2));
	}

	SECTION("mat4 operator-")
	{
		REQUIRE((Z - A) == mat4(-1, -3, -2, 0, -1, 0, 0, 0, -1, -2, -2, 0, 0, 0, 0, -1));
		REQUIRE((A - A) == mat4());
	}

	SECTION("mat4 operator-")
	{
		REQUIRE(-A == mat4(-1, -3, -2, 0, -1, 0, 0, 0, -1, -2, -2, 0, 0, 0, 0, -1));
		REQUIRE(-Z == mat4());
	}

	SECTION("mat4 operator* mat4")
	{
		REQUIRE(id * id == id);
		REQUIRE(Z * id == Z);
		REQUIRE(A * id == A);
	}

	SECTION("mat4 operator* vec2")
	{
		REQUIRE(id * v1 == v1);
		REQUIRE(A * v1 == vec4(13, 1, 11, 1));
	}

	SECTION("mat4 operator* scalar")
	{
		REQUIRE(id * 2 == mat4(2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2));
		REQUIRE(A * 2 == mat4(2, 6, 4, 0, 2, 0, 0, 0, 2, 4, 4, 0, 0, 0, 0, 2));
	}

	SECTION("mat4 determinant")
	{
		REQUIRE(determinant(id) == 1);
		REQUIRE(determinant(Z) == 0);
		REQUIRE(determinant(A) == -2);
	}

	SECTION("mat4 transpose")
	{
		REQUIRE(transpose(id) == id);
		REQUIRE(transpose(Z) == Z);
		REQUIRE(transpose(A) == mat4(1, 1, 1, 0, 3, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 1));
	}

	SECTION("mat4 properties")
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
