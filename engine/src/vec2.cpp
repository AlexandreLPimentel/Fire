#include <GL/glew.h>
#include "vector.h"

namespace engine
{
	vec2::vec2()
	{
		x = y = 0;
	}

	vec2::vec2(GLfloat x, GLfloat y)
		: x(x), y(y) {}

	vec2::vec2(const vec2& v)
		: vec2(v.x, v.y) {}

	vec2 vec2::clean()
	{
		if (fabs(x) < EPSILON)
			x = 0;
		if (fabs(y) < EPSILON)
			y = 0;

		return *this;
	}

	vec2 vec2::operator=(const vec2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	GLboolean operator==(const vec2& v1, const vec2& v2)
	{
		return fabs(v1.x - v2.x) < EPSILON && fabs(v1.y - v2.y) < EPSILON;
	}

	GLboolean operator!=(const vec2& v1, const vec2& v2)
	{
		return !(v1 == v2);
	}

	vec2 operator+(const vec2& v1, const vec2& v2)
	{
		return vec2(v1.x + v2.x, v1.y + v2.y);
	}

	vec2 operator-(const vec2& v1, const vec2& v2)
	{
		return vec2(v1.x - v2.x, v1.y - v2.y);
	}

	vec2 operator-(const vec2& v)
	{
		return vec2(-v.x, -v.y);
	}

	vec2 operator*(const vec2& v1, const GLfloat s)
	{
		return vec2(s * v1.x, s * v1.y);
	}

	vec2 operator*(const GLfloat s, const vec2& v1)
	{
		return v1 * s;
	}

	vec2 operator/(const vec2& v1, const GLfloat s)
	{
		return vec2(v1.x / s, v1.y / s);
	}

	vec2 operator+=(vec2& v1, const vec2& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	vec2 operator-=(vec2& v1, const vec2& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;
		return v1;
	}

	vec2 operator*=(vec2& v1, const GLfloat s)
	{
		v1.x *= s;
		v1.y *= s;
		return v1;
	}

	vec2 operator/=(vec2& v1, const GLfloat s)
	{
		v1.x /= s;
		v1.y /= s;
		return v1;
	}

	std::istream& operator>>(std::istream& stream, vec2& v)
	{
		stream >> v.x >> v.y;
		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& v)
	{
		stream << "[" << v.x << ", " << v.y << "]";
		return stream;
	}

	GLfloat dot(const vec2& v1, const vec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	GLfloat norm(const vec2& v)
	{
		return sqrt(quadrance(v));
	}

	vec2 normalize(const vec2& v)
	{
		GLfloat n = norm(v);

		if (n == 0)
			throw std::exception("Division by zero");

		return v / n;
	}

	GLfloat quadrance(const vec2& v)
	{
		return dot(v, v);
	}
}
