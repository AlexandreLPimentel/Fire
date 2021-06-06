#include "catch.hpp"
#include "engine.h"

using namespace engine;

TEST_CASE("Test vec4 class", "[vec4]")
{
	vec4 ex(1, 0, 0, 0);
	vec4 ey(0, 1, 0, 0);
	vec4 v1;
	vec4 v2(1, 2, 3, 0);
	vec4 v3(3, 2, 1, 0);

	SECTION("vec4 constructors")
	{
		REQUIRE(v1.x == 0);
		REQUIRE(v1.y == 0);
		REQUIRE(v1.z == 0);
		REQUIRE(v1.w == 0);

		REQUIRE(v2.x == 1);
		REQUIRE(v2.y == 2);
		REQUIRE(v2.z == 3);
		REQUIRE(v2.w == 0);

		vec4 t(v2);
		REQUIRE(v2.x == t.x);
		REQUIRE(v2.y == t.y);
		REQUIRE(v2.z == t.z);
		REQUIRE(v2.w == t.w);
	}

	SECTION("vec4 operator=")
	{
		v1 = v2;
		REQUIRE(v1.x == v2.x);
		REQUIRE(v1.y == v2.y);
		REQUIRE(v1.z == v2.z);
		REQUIRE(v1.w == v2.w);
	}

	SECTION("vec4 operator==")
	{
		REQUIRE(v1 == v1);
		REQUIRE(v1 == vec4());
		REQUIRE(!(v1 == v2));
	}

	SECTION("vec4 operator!=")
	{
		REQUIRE(!(v1 != v1));
		REQUIRE(!(v1 != vec4()));
		REQUIRE(v1 != v2);
	}

	SECTION("vec4 operator+")
	{
		REQUIRE(v1 + v1 == v1);
		REQUIRE(v1 + v2 == v2);
		REQUIRE(v2 + v2 == vec4(2, 4, 6, 0));
	}

	SECTION("vec4 operator-")
	{
		REQUIRE(v1 - v1 == v1);
		REQUIRE(v1 - v2 == vec4(-v2.x, -v2.y, -v2.z, 0));
		REQUIRE(v2 - v2 == vec4());
	}

	SECTION("vec4 symmetric operator")
	{
		-v2 == vec4(-v2.x, -v2.y, -v2.z, 0);
		-v1 == vec4();
	}

	SECTION("vec4 operator*")
	{
		REQUIRE(v1 * 1 == vec4());
		REQUIRE(v1 * 0 == vec4());
		REQUIRE(v2 * 0 == vec4());
		REQUIRE(v2 * 1 == v2);
		REQUIRE(v2 * 2 == vec4(2, 4, 6, 0));
		REQUIRE(v2 * 2 == 2 * v2);
	}

	SECTION("vec4 operator/")
	{
		REQUIRE(v1 / 1 == vec4());
		REQUIRE(v2 / 1 == v2);
		REQUIRE(v2 / 2 == vec4(.5f, 1, 3 / 2.0f, 0));
	}

	SECTION("vec4 operator+=")
	{
		v1 += v2;
		REQUIRE(v1 == v2);
		v2 += vec4(1, 1, 1, 1);
		REQUIRE(v2 == vec4(2, 3, 4, 1));
	}

	SECTION("vec4 operator-=")
	{
		v1 -= v2;
		REQUIRE(v1 == -v2);
		v2 -= v2;
		REQUIRE(v2 == vec4());
	}

	SECTION("vec4 operator*=")
	{
		v1 *= 2;
		REQUIRE(v1 == vec4());
		v2 *= 2;
		REQUIRE(v2 == vec4(2, 4, 6, 0));
	}

	SECTION("vec4 operator/=")
	{
		v1 /= 2;
		REQUIRE(v1 == vec4());
		v2 /= 2;
		REQUIRE(v2 == vec4(.5f, 1, 3.f / 2, 0));
	}

	SECTION("vec4 dot")
	{
		REQUIRE(dot(v1, v1) == 0);
		REQUIRE(dot(v1, v2) == 0);
		REQUIRE(dot(v2, v2) == v2.x * v2.x + v2.y * v2.y + v2.z * v2.z + v2.w * v2.w);
		REQUIRE(dot(v2, v3) == v2.x * v3.x + v2.y * v3.y + v2.z * v3.z + v2.w * v3.w);
		REQUIRE(dot(v2, v3) == dot(v3, v2));
		REQUIRE(dot(ex, ey) == 0);
	}

	SECTION("vec4 norm")
	{
		REQUIRE(norm(v1) == 0);
		REQUIRE(norm(v2) == sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z));
	}

	SECTION("vec4 normalize")
	{
		float n = norm(v2);
		REQUIRE(normalize(v2) == vec4(v2.x / n, v2.y / n, v2.z / n, v2.w / n));
		REQUIRE_THROWS(normalize(vec4()));
	}

	SECTION("vec4 quadrance")
	{
		REQUIRE(quadrance(v2) == v2.x * v2.x + v2.y * v2.y + v2.z * v2.z + v2.w * v2.w);
	}
}