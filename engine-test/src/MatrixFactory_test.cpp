#include "catch.hpp"
#include "engine.h"
#include "MathUtils.h"

using namespace engine;

TEST_CASE("Test MatrixFactory class", "[MatrixFactory]")
{
	vec3 v(1, 2, 3);
	vec3 ex(1, 0, 0);
	vec3 ey(0, 1, 0);
	vec3 ez(0, 0, 1);

	vec2 v2(1, 1);
	vec3 v3(1, 1, 1);
	vec4 v4(1, 1, 1, 1);

	SECTION("Dual Matrix")
	{
		mat3 A = MatrixFactory::dualMatrix(v);
		mat3 A2 = MatrixFactory::squaredDualMatrix(v);

		REQUIRE(A * A == A2);
	}

	SECTION("Rotation")
	{
		mat3 R = MatrixFactory::mat3Rotation(deg2rad(90), ez);
		vec3 vrot = R * ex;

		REQUIRE(vrot == ey);
	}

	SECTION("Scale")
	{
		mat2 m2 = MatrixFactory::mat2Scale(2, 2);
		mat3 m3 = MatrixFactory::mat3Scale(2, 2, 2);
		mat4 m4 = MatrixFactory::mat4Scale(2, 2, 2);

		REQUIRE(m2 * v2 == 2 * v2);
		REQUIRE(m3 * v3 == 2 * v3);
		REQUIRE(m4 * v4 == vec4(2, 2, 2, 1));
	}
}