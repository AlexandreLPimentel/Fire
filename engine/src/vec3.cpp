#include <GL/glew.h>
#include "vector.h"

namespace engine
{
	vec3::vec3()
	{
		x = y = z = 0;
	}

	vec3::vec3(GLfloat x, GLfloat y, GLfloat z)
		: x(x), y(y), z(z) {}

	vec3::vec3(const vec3& v)
		: vec3(v.x, v.y, v.z) {}

	vec3 vec3::clean()
	{
		if (fabs(x) < EPSILON)
			x = 0;
		if (fabs(y) < EPSILON)
			y = 0;
		if (fabs(z) < EPSILON)
			z = 0;

		return *this;
	}

	vec3 vec3::operator=(const vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	GLboolean operator==(const vec3& v1, const vec3& v2)
	{
		return fabs(v1.x - v2.x) < EPSILON && fabs(v1.y - v2.y) < EPSILON && fabs(v1.z - v2.z) < EPSILON;
	}

	GLboolean operator!=(const vec3& v1, const vec3& v2)
	{
		return !(v1 == v2);
	}

	vec3 operator+(const vec3& v1, const vec3& v2)
	{
		return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	vec3 operator-(const vec3& v1, const vec3& v2)
	{
		return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	vec3 operator-(const vec3& v)
	{
		return vec3(-v.x, -v.y, -v.z);
	}

	vec3 operator*(const vec3& v1, const GLfloat s)
	{
		return vec3(s * v1.x, s * v1.y, s * v1.z);
	}

	vec3 operator*(const GLfloat s, const vec3& v1)
	{
		return v1 * s;
	}

	vec3 operator/(const vec3& v1, const GLfloat s)
	{
		return vec3(v1.x / s, v1.y / s, v1.z / s);
	}

	vec3 operator+=(vec3& v1, const vec3& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;
		return v1;
	}

	vec3 operator-=(vec3& v1, const vec3& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;
		return v1;
	}

	vec3 operator*=(vec3& v1, const GLfloat s)
	{
		v1.x *= s;
		v1.y *= s;
		v1.z *= s;
		return v1;
	}

	vec3 operator/=(vec3& v1, const GLfloat s)
	{
		v1.x /= s;
		v1.y /= s;
		v1.z /= s;
		return v1;
	}

	std::istream& operator>>(std::istream& stream, vec3& v)
	{
		stream >> v.x >> v.y >> v.z;
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& v)
	{
		stream << "[" << v.x << ", " << v.y << ", " << v.z << "]";
		return stream;
	}

	GLfloat dot(const vec3& v1, const vec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	GLfloat norm(const vec3& v)
	{
		return sqrt(quadrance(v));
	}

	vec3 normalize(const vec3& v)
	{
		GLfloat n = norm(v);

		if (n == 0)
			throw std::exception("Division by zero");

		return v / n;
	}

	GLfloat quadrance(const vec3& v)
	{
		return dot(v, v);
	}

	vec3 cross(const vec3& v1, const vec3& v2)
	{
		return vec3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}
}
