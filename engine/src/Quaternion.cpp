#include "Quaternion.h"
#include "MathUtils.h"
#include "matrix.h"
#include "vector.h"
#include <ostream>
#include <string>
#include <iostream>

using namespace engine;

Quaternion::Quaternion(GLfloat theta, vec3 axis)
{
	vec3 axisn = normalize(axis);

	float a = deg2rad(theta);

	data.w = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	data.x = axisn.x * s;
	data.y = axisn.y * s;
	data.z = axisn.z * s;

	clean();
	*this = normalize(*this);
}

Quaternion::Quaternion() :
	data(vec4(0, 0, 0, 1)) {}

Quaternion::Quaternion(const vec4& q)
{
	data = q;
}

Quaternion::Quaternion(const Quaternion& q)
{
	data = q.data;
}

Quaternion::Quaternion(const GLfloat t, const GLfloat x, const GLfloat y, const GLfloat z)
{
	data.x = x;
	data.y = y;
	data.z = z;
	data.w = t;
}

void Quaternion::clean()
{
	if (fabs(data.w) < EPSILON) data.w = 0.0f;
	if (fabs(data.x) < EPSILON) data.x = 0.0f;
	if (fabs(data.y) < EPSILON) data.y = 0.0f;
	if (fabs(data.z) < EPSILON) data.z = 0.0f;
}

float engine::quadrance(const Quaternion& q)
{
	return quadrance(q.data);
}

float engine::norm(const Quaternion& q)
{
	return sqrt(quadrance(q));
}

Quaternion engine::normalize(const Quaternion& q)
{
	float s = 1 / norm(q);
	return q * s;
}

Quaternion engine::conjugate(const Quaternion& q)
{
	Quaternion qconj(q.data.w, -q.data.x, -q.data.y, -q.data.z);
	return qconj;
}

Quaternion engine::inverse(const Quaternion& q)
{
	return conjugate(q) * (1.0f / quadrance(q));
}

Quaternion engine::operator+(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion q(q1.data + q2.data);
	return q;
}

Quaternion engine::operator*(const Quaternion& q, const float s)
{
	Quaternion qs(q.data * s);
	return qs;
}

Quaternion engine::operator*(const Quaternion& q0, const Quaternion& q1)
{
	Quaternion q;
	q.data.w = q0.data.w * q1.data.w - q0.data.x * q1.data.x - q0.data.y * q1.data.y - q0.data.z * q1.data.z;
	q.data.x = q0.data.w * q1.data.x + q0.data.x * q1.data.w + q0.data.y * q1.data.z - q0.data.z * q1.data.y;
	q.data.y = q0.data.w * q1.data.y + q0.data.y * q1.data.w + q0.data.z * q1.data.x - q0.data.x * q1.data.z;
	q.data.z = q0.data.w * q1.data.z + q0.data.z * q1.data.w + q0.data.x * q1.data.y - q0.data.y * q1.data.x;
	return q;
}

mat4 Quaternion::GLMatrix()
{
	Quaternion qn = normalize(*this);

	float xx = qn.data.x * qn.data.x;
	float xy = qn.data.x * qn.data.y;
	float xz = qn.data.x * qn.data.z;
	float xt = qn.data.x * qn.data.w;
	float yy = qn.data.y * qn.data.y;
	float yz = qn.data.y * qn.data.z;
	float yt = qn.data.y * qn.data.w;
	float zz = qn.data.z * qn.data.z;
	float zt = qn.data.z * qn.data.w;

	mat4 matrix(
		1.0f - 2.0f * (yy + zz),	2.0f * (xy - zt),			2.0f * (xz + yt),			0.0f,
		2.0f * (xy + zt),			1.0f - 2.0f * (xx + zz),	2.0f * (yz - xt),			0.0f,
		2.0f * (xz - yt),			2.0f * (yz + xt),			1.0f - 2.0f * (xx + yy),	0.0f,
		0.0f,						0.0f,						0.0f,						1.0f);

	matrix.clean();
	return matrix;
}

void Quaternion::toAngleAxis(GLfloat& theta, vec3& axis) const
{
	Quaternion qn = normalize(*this);
	theta = deg2rad(2.0f * acos(qn.data.w));
	float s = sqrt(1.0f - qn.data.w*qn.data.w);
	if (s < EPSILON) {
		axis.x = 1.0f;
		axis.y = 0.0f;
		axis.z = 0.0f;
	}
	else {
		axis.x = qn.data.x / s;
		axis.y = qn.data.y / s;
		axis.z = qn.data.z / s;
	}
}

Quaternion Quaternion::operator=(const Quaternion& q)
{
	data = q.data;
	return *this;
}

Quaternion engine::Lerp(const Quaternion& q0, const Quaternion& q1, float k)
{
	float cos_angle = q0.data.x*q1.data.x + q0.data.y*q1.data.y + q0.data.z*q1.data.z + q0.data.w*q1.data.w;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	Quaternion qi = q0 * k0 + q1 * k1;
	return normalize(qi);
}

Quaternion engine::Slerp(const Quaternion& q0, const Quaternion& q1, float k)
{
	float angle = acos(q0.data.x*q1.data.x + q0.data.y*q1.data.y + q0.data.z*q1.data.z + q0.data.w*q1.data.w);
	float k0 = sin((1 - k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	Quaternion qi = q0 * k0 + q1 * k1;
	return normalize(qi);
}

bool engine::operator==(const Quaternion& q0, const Quaternion& q1)
{
	return (fabs(q0.data.w - q1.data.w) < EPSILON && fabs(q0.data.x - q1.data.x) < EPSILON &&
		fabs(q0.data.y - q1.data.y) < EPSILON && fabs(q0.data.z - q1.data.z) < EPSILON);
}

bool engine::operator!=(const Quaternion& q0, const Quaternion& q1)
{
	return !(q0 == q1);
}

std::ostream& engine::operator<<(std::ostream& ostream, const Quaternion& q)
{
	ostream << "(" << q.data.w << ", " << q.data.x << ", " << q.data.y << ", " << q.data.z << ")";
	return ostream;
}

void engine::Print(const std::string& s, const Quaternion& q)
{
	std::cout << s << " = " << q << std::endl;
}

void engine::PrintAngleAxis(const std::string& s, const Quaternion& q)
{
	std::cout << s << " = [" << std::endl;

	float thetaf;
	vec3 axis_f;

	q.toAngleAxis(thetaf, axis_f);
	std::cout << "  angle = " << thetaf << std::endl;
	std::cout << "  axis = " << axis_f << std::endl;
	std::cout << "]" << std::endl;
}
