#include <GL/glew.h>
#include "vector.h"

namespace engine
{
	vec4::vec4()
	{
		x = y = z = w = 0;
	}

	vec4::vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
		: x(x), y(y), z(z), w(w) {}

	vec4::vec4(const vec4& v)
		: vec4(v.x, v.y, v.z, v.w) {}

	vec4 vec4::clean()
	{
		if (fabs(x) < EPSILON)
			x = 0;
		if (fabs(y) < EPSILON)
			y = 0;
		if (fabs(z) < EPSILON)
			z = 0;
		if (fabs(w) < EPSILON)
			w = 0;

		return *this;
	}

	vec4 vec4::operator=(const vec4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	GLboolean operator==(const vec4& v1, const vec4& v2)
	{
		return fabs(v1.x - v2.x) < EPSILON &&
			fabs(v1.y - v2.y) < EPSILON &&
			fabs(v1.z - v2.z) < EPSILON &&
			fabs(v1.w - v2.w) < EPSILON;
	}

	GLboolean operator!=(const vec4& v1, const vec4& v2)
	{
		return !(v1 == v2);
	}

	vec4 operator+(const vec4& v1, const vec4& v2)
	{
		return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
	}

	vec4 operator-(const vec4& v1, const vec4& v2)
	{
		return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
	}

	vec4 operator-(const vec4& v)
	{
		return vec4(-v.x, -v.y, -v.z, -v.w);
	}

	vec4 operator*(const vec4& v1, const GLfloat s)
	{
		return vec4(s * v1.x, s * v1.y, s * v1.z, s * v1.w);
	}

	vec4 operator*(const GLfloat s, const vec4& v1)
	{
		return v1 * s;
	}

	vec4 operator/(const vec4& v1, const GLfloat s)
	{
		return vec4(v1.x / s, v1.y / s, v1.z / s, v1.w / s);
	}

	vec4 operator+=(vec4& v1, const vec4& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		v1.z += v2.z;
		v1.w += v2.w;
		return v1;
	}

	vec4 operator-=(vec4& v1, const vec4& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		v1.z -= v2.z;
		v1.w -= v2.w;
		return v1;
	}

	vec4 operator*=(vec4& v1, const GLfloat s)
	{
		v1.x *= s;
		v1.y *= s;
		v1.z *= s;
		v1.w *= s;
		return v1;
	}

	vec4 operator/=(vec4& v1, const GLfloat s)
	{
		v1.x /= s;
		v1.y /= s;
		v1.z /= s;
		v1.w /= s;
		return v1;
	}

	std::istream& operator>>(std::istream& stream, vec4& v)
	{
		stream >> v.x >> v.y >> v.z >> v.w;
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const vec4& v)
	{
		stream << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
		return stream;
	}

	GLfloat dot(const vec4& v1, const vec4& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	GLfloat norm(const vec4& v)
	{
		return sqrt(quadrance(v));
	}

	vec4 normalize(const vec4& v)
	{
		GLfloat n = norm(v);

		if (n == 0)
			throw std::exception("Division by zero");

		return v / n;
	}

	GLfloat quadrance(const vec4& v)
	{
		return dot(v, v);
	}
}
