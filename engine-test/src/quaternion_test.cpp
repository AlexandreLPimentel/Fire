#include "catch.hpp"
#include <cassert>
#include "engine.h"
#include <iostream>

using namespace engine;

TEST_CASE("Test Quaternion class", "[Quaternion]")
{
#define HEADER(X) std::cout<<std::endl<<(X)<<std::endl<<std::endl;

	SECTION("TEST 1 : Rotation of 90 degrees about the y-axis")
	{
		vec3 axis(0.0f, 1.0f, 0.0f);
		Quaternion q(90.0f, axis);
		Print("   q", q);

		Quaternion vi(vec4(0.0f, 7.0f, 0.0f, 0.0f));
		Print("  vi", vi);

		Quaternion qe(vec4(0.0f, 0.0f, 0.0f, -7.0f));
		Print("  qe", qe);

		Quaternion qinv = inverse(q);
		qinv.clean();
		Print("qinv", qinv);

		Quaternion qf = q * vi * qinv;
		Print("  qf", qf);

		REQUIRE(qf == qe);
	}

	SECTION("TEST 2 : Rotation of 90 degrees about the y-axis with matrix")
	{
		vec3 axis = { 0.0f, 1.0f, 0.0f };
		Quaternion q(90.0f, axis);
		Print(" q", q);

		vec4 vi = { 7.0f, 0.0f, 0.0f, 1.0f };
		std::cout << "vi " << vi << std::endl;

		vec4 ve = { 0.0f, 0.0f, -7.0f, 1.0f };
		std::cout << "ve " << ve << std::endl;

		mat4 m = q.GLMatrix();
		std::cout << " M " << m << std::endl;

		vec4 vf = m *vi;
		std::cout << "vf " << vf << std::endl;

		REQUIRE(vf == ve);
	}

	SECTION("TEST 3 : Yaw 900 = Roll 180 + Pitch 180")
	{

		vec3 axis_x = { 1.0f, 0.0f, 0.0f };
		vec3 axis_y = { 0.0f, 1.0f, 0.0f };
		vec3 axis_z = { 0.0f, 0.0f, 1.0f };

		Quaternion qyaw900(900.0f, axis_y);
		Print("  qyaw900", qyaw900);

		Quaternion qroll180(180.0f, axis_x);
		Print(" qroll180", qroll180);
		Quaternion qpitch180(180.0f, axis_z);
		Print("qpitch180", qpitch180);
		Quaternion qrp = qpitch180 * qroll180;
		Print("      qrp", qrp);
		Quaternion qpr = qroll180 * qpitch180;
		Print("      qpr", qpr);

		Quaternion qi = { 0.0f, 1.0f, 0.0f, 0.0f }; // x-axis
		Print("       qi", qi);
		Quaternion qe = { 0.0f, -1.0f, 0.0f, 0.0f };
		Print("       qe", qe);

		Quaternion qyaw900inv = inverse(qyaw900);
		Quaternion qfy = qyaw900 * qi * qyaw900inv;
		Print("       qy", qfy);
		REQUIRE(qe == qfy);

		Quaternion qrpinv = inverse(qrp);
		Quaternion qfrp = qrp * qi * qrpinv;
		Print("     qfrp", qfrp);
		REQUIRE(qe == qfrp);

		Quaternion qprinv = inverse(qpr);
		Quaternion qfpr = qpr * qi * qprinv;
		Print("     qfpr", qfpr);
		REQUIRE(qe == qfpr);
	}

	SECTION("TEST 4: Q <-> (angle, axis)")
	{
		float thetai = 45.0f;
		vec3 axis_i = { 0.0f, 1.0f, 0.0f };
		Quaternion q(thetai, axis_i);
		std::cout << thetai << " ";
		std::cout << "axis_i " << axis_i << std::endl;

		float thetaf;
		vec3 axis_f;
		q.toAngleAxis(thetaf, axis_f);
		std::cout << thetaf << " ";
		std::cout << "axis_f " << axis_f << std::endl;

		REQUIRE(fabs(thetai - thetaf) < EPSILON);
		REQUIRE(axis_i == axis_f);
	}

	SECTION("TEST 5: LERP")
	{
		vec3 axis = { 0.0f, 1.0f, 0.0f };
		Quaternion q0(0.0f, axis);
		Print("       q0", q0);
		Quaternion q1(90.0f, axis);
		Print("       q1", q1);
		Quaternion qe(30.0f, axis);
		Print("       qe", qe);

		Quaternion qLerp0 = Lerp(q0, q1, 0.0f);
		Print("  lerp(0)", qLerp0);
		REQUIRE(qLerp0 == q0);

		Quaternion qLerp1 = Lerp(q0, q1, 1.0f);
		Print("  lerp(1)", qLerp1);
		REQUIRE(qLerp1 == q1);

		Quaternion qlerp = Lerp(q0, q1, 1 / 3.0f);
		Print("lerp(1/3)", qlerp);
		PrintAngleAxis("lerp(1/3)", qlerp);

		REQUIRE(qlerp == qe);
	}

	SECTION("TEST 6: SLERP")
	{
		vec3 axis = { 0.0f, 1.0f, 0.0f };
		Quaternion q0(0.0f, axis);
		Print("        q0", q0);
		Quaternion q1(90.0f, axis);
		Print("        q1", q1);
		Quaternion qe(30.0f, axis);
		Print("        qe", qe);

		Quaternion qSlerp0 = Slerp(q0, q1, 0.0f);
		Print("  slerp(0)", qSlerp0);
		REQUIRE(qSlerp0 == q0);

		Quaternion qSlerp1 = Slerp(q0, q1, 1.0f);
		Print("  slerp(1)", qSlerp1);
		REQUIRE(qSlerp1 == q1);

		Quaternion qslerp = Slerp(q0, q1, 1 / 3.0f);
		Print("slerp(1/3)", qslerp);
		PrintAngleAxis("slerp(1/3)", qslerp);

		REQUIRE(qslerp == qe);
	}
}
