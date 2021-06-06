#include "catch.hpp"
#include "engine.h"

using namespace engine;

TEST_CASE("Test vec3 class", "[vec3]")
{
	vec3 ex(1, 0, 0);
	vec3 ey(0, 1, 0);
	vec3 ez(0, 0, 1);
	vec3 v1;
	vec3 v2(1, 2, 3);
	vec3 v3(3, 2, 1);

	SECTION("vec3 constructors")
	{
		REQUIRE(v1.x == 0);
		REQUIRE(v1.y == 0);
		REQUIRE(v1.z == 0);
		REQUIRE(v2.x == 1);
		REQUIRE(v2.y == 2);
		REQUIRE(v2.z == 3);
		vec3 t(v2);
		REQUIRE(v2.x == t.x);
		REQUIRE(v2.y == t.y);
		REQUIRE(v2.z == t.z);
	}

	SECTION("vec3 operator=")
	{
		v1 = v2;
		REQUIRE(v1.x == v2.x);
		REQUIRE(v1.y == v2.y);
		REQUIRE(v1.z == v2.z);
	}

	SECTION("vec3 operator==")
	{
		REQUIRE(v1 == v1);
		REQUIRE(v1 == vec3());
		REQUIRE(!(v1 == v2));
	}

	SECTION("vec3 operator!=")
	{
		REQUIRE(!(v1 != v1));
		REQUIRE(!(v1 != vec3()));
		REQUIRE(v1 != v2);
	}

	SECTION("vec3 operator+")
	{
		REQUIRE(v1 + v1 == v1);
		REQUIRE(v1 + v2 == v2);
		REQUIRE(v2 + v2 == vec3(2, 4, 6));
	}

	SECTION("vec3 operator-")
	{
		REQUIRE(v1 - v1 == v1);
		REQUIRE(v1 - v2 == vec3(-v2.x, -v2.y, -v2.z));
		REQUIRE(v2 - v2 == vec3());
	}

	SECTION("vec3 symmetric operator")
	{
		-v2 == vec3(-v2.x, -v2.y, -v2.z);
		-v1 == vec3();
	}

	SECTION("vec3 operator*")
	{
		REQUIRE(v1 * 1 == vec3());
		REQUIRE(v1 * 0 == vec3());
		REQUIRE(v2 * 0 == vec3());
		REQUIRE(v2 * 1 == v2);
		REQUIRE(v2 * 2 == vec3(2, 4, 6));
		REQUIRE(v2 * 2 == 2 * v2);
	}

	SECTION("vec3 operator/")
	{
		REQUIRE(v1 / 1 == vec3());
		REQUIRE(v2 / 1 == v2);
		REQUIRE(v2 / 2 == vec3(.5f, 1, 3 / 2.0f));
	}

	SECTION("vec3 operator+=")
	{
		v1 += v2;
		REQUIRE(v1 == v2);
		v2 += vec3(1, 1, 1);
		REQUIRE(v2 == vec3(2, 3, 4));
	}

	SECTION("vec3 operator-=")
	{
		v1 -= v2;
		REQUIRE(v1 == -v2);
		v2 -= v2;
		REQUIRE(v2 == vec3());
	}

	SECTION("vec3 operator*=")
	{
		v1 *= 2;
		REQUIRE(v1 == vec3());
		v2 *= 2;
		REQUIRE(v2 == vec3(2, 4, 6));
	}

	SECTION("vec3 operator/=")
	{
		v1 /= 2;
		REQUIRE(v1 == vec3());
		v2 /= 2;
		REQUIRE(v2 == vec3(.5f, 1, 3.f / 2));
	}

	SECTION("vec3 dot")
	{
		REQUIRE(dot(v1, v1) == 0);
		REQUIRE(dot(v1, v2) == 0);
		REQUIRE(dot(v2, v2) == v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
		REQUIRE(dot(v2, v3) == v2.x * v3.x + v2.y * v3.y + v2.z * v3.z);
		REQUIRE(dot(v2, v3) == dot(v3, v2));
		REQUIRE(dot(ex, ey) == 0);
	}

	SECTION("vec3 norm")
	{
		REQUIRE(norm(v1) == 0);
		REQUIRE(norm(v2) == sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z));
	}

	SECTION("vec3 normalize")
	{
		float n = norm(v2);
		REQUIRE(normalize(v2) == vec3(v2.x / n, v2.y / n, v2.z / n));
		REQUIRE_THROWS(normalize(vec3()));
	}

	SECTION("vec3 quadrance")
	{
		REQUIRE(quadrance(v2) == v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	}

	SECTION("vec3 cross")
	{
		REQUIRE(cross(ex, ey) == ez);
		REQUIRE(cross(ey, ex) == -ez);
	}
}