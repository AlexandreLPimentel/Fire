#include "catch.hpp"
#include "vector.h"

using namespace engine;


TEST_CASE("Test vec2 class", "[vec2]")
{
	vec2 v1;
	vec2 v2(1, 2);
	vec2 v3(2, 4);
	vec2 v4(2, 4);

	SECTION("vec2 default constructor")
	{
		REQUIRE(v1.x == 0);
		REQUIRE(v1.y == 0);
	}

	SECTION("vec2 constructor with args")
	{
		REQUIRE(v2.x == 1);
		REQUIRE(v2.y == 2);
		vec2 t(v2);
		REQUIRE(v2.x == t.x);
		REQUIRE(v2.y == t.y);
	}

	SECTION("vec2 operator=")
	{
		v1 = v2;
		REQUIRE(v1.x == v2.x);
		REQUIRE(v1.y == v2.y);
	}

	SECTION("vec2 operator==")
	{
		REQUIRE(v1 == v1);
		REQUIRE(!(v1 == v2));
		REQUIRE(v3 == v4);
	}

	SECTION("vec2 operator!=")
	{
		REQUIRE(!(v1 != v1));
		REQUIRE(v1 != v2);
		REQUIRE(!(v3 != v4));
	}

	SECTION("vec2 operator+")
	{
		REQUIRE(v1 + v1 == v1);
		REQUIRE(v1 + v2 == v2);
		REQUIRE(v2 + v3 == v3 + v2);
		REQUIRE(v2 + v3 == vec2(v3.x + v2.x, v3.y + v2.y));
	}

	SECTION("vec2 operator-")
	{
		REQUIRE(v1 - v1 == v1);
		REQUIRE(v1 - v2 == vec2(-v2.x, -v2.y));
		REQUIRE(v2 - v3 != v3 - v2);
		REQUIRE(v2 - v3 == vec2(v2.x - v3.x, v2.y - v3.y));
	}

	SECTION("vec2 symmetric operator")
	{
		REQUIRE(-v2 == vec2(-v2.x, -v2.y));
		REQUIRE(-v1 == vec2());
	}

	SECTION("vec2 operator*")
	{
		REQUIRE(v1 * 1 == vec2());
		REQUIRE(v1 * 0 == vec2());
		REQUIRE(v2 * 0 == vec2());
		REQUIRE(v2 * 1 == v2);
		REQUIRE(v2 * 2 == vec2(2, 4));
		REQUIRE(v2 * 2 == 2 * v2);
	}

	SECTION("vec2 operator/")
	{
		REQUIRE(v1 / 1 == vec2());
		REQUIRE(v2 / 1 == v2);
		REQUIRE(v2 / 2 == vec2(.5f, 1));
	}

	SECTION("vec2 operator+=")
	{
		v1 += v2;
		REQUIRE(v1 == v2);
		v2 += v3;
		REQUIRE(v2 == vec2(3, 6));
	}

	SECTION("vec2 operator-=")
	{
		v1 -= v2;
		REQUIRE(v1 == -v2);
		v2 -= v3;
		REQUIRE(v2 == vec2(-1, -2));
	}

	SECTION("vec2 operator*=")
	{
		v1 *= 2;
		REQUIRE(v1 == vec2());
		v2 *= 2;
		REQUIRE(v2 == vec2(2, 4));
	}

	SECTION("vec2 operator/=")
	{
		v1 /= 2;
		REQUIRE(v1 == vec2());
		v2 /= 2;
		REQUIRE(v2 == vec2(.5f, 1));
	}

	SECTION("vec2 dot")
	{
		REQUIRE(dot(v1, v1) == 0);
		REQUIRE(dot(v1, v2) == 0);
		REQUIRE(dot(v2, v2) == v2.x * v2.x + v2.y * v2.y);
		REQUIRE(dot(v2, v3) == v2.x * v3.x + v2.y * v3.y);
		REQUIRE(dot(v2, v3) == dot(v3, v2));
		REQUIRE(dot(vec2(1, 0), vec2(0, 1)) == 0);
	}

	SECTION("vec2 norm")
	{
		REQUIRE(norm(v1) == 0);
		REQUIRE(norm(v2) == sqrt(v2.x * v2.x + v2.y * v2.y));
	}

	SECTION("vec2 normalize")
	{
		float n = norm(v2);
		REQUIRE(normalize(v2) == vec2(v2.x / n, v2.y / n));
		REQUIRE_THROWS(normalize(vec4()));
	}

	SECTION("vec2 quadrance")
	{
		REQUIRE(quadrance(v2) == v2.x * v2.x + v2.y * v2.y);
	}
}
