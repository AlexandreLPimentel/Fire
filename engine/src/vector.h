#pragma once
#include <GL/glew.h>
#include <fstream>

#define EPSILON (float)1.0e-5

namespace engine
{
	struct vec2
	{
		GLfloat x, y;

		vec2();
		vec2(GLfloat x, GLfloat y);
		vec2(const vec2& v);

		vec2 clean();

		vec2 operator=(const vec2& v);
		friend GLboolean operator==(const vec2& v1, const vec2& v2);
		friend GLboolean operator!=(const vec2& v1, const vec2& v2);

		friend vec2 operator+(const vec2& v1, const vec2& v2);
		friend vec2 operator-(const vec2& v1, const vec2& v2);
		friend vec2 operator-(const vec2& v);
		friend vec2 operator*(const vec2& v1, const GLfloat s);
		friend vec2 operator*(const GLfloat s, const vec2& v1);
		friend vec2 operator/(const vec2& v1, const GLfloat s);

		friend vec2 operator+=(vec2& v1, const vec2& v2);
		friend vec2 operator-=(vec2& v1, const vec2& v2);
		friend vec2 operator*=(vec2& v1, const GLfloat s);
		friend vec2 operator/=(vec2& v1, const GLfloat s);

		friend std::istream& operator>>(std::istream& stream, vec2& v);
		friend std::ostream& operator<<(std::ostream& stream, const vec2& v);

		friend GLfloat dot(const vec2& v1, const vec2& v2);
		friend GLfloat norm(const vec2& v);
		friend vec2 normalize(const vec2& v);
		friend GLfloat quadrance(const vec2& v);
	};

	struct vec3
	{
		GLfloat x, y, z;

		vec3();
		vec3(GLfloat x, GLfloat y, GLfloat z);
		vec3(const vec3& v);

		vec3 clean();

		vec3 operator=(const vec3& v);
		friend GLboolean operator==(const vec3& v1, const vec3& v2);
		friend GLboolean operator!=(const vec3& v1, const vec3& v2);

		friend vec3 operator+(const vec3& v1, const vec3& v2);
		friend vec3 operator-(const vec3& v1, const vec3& v2);
		friend vec3 operator-(const vec3& v);
		friend vec3 operator*(const vec3& v1, const GLfloat s);
		friend vec3 operator*(const GLfloat s, const vec3& v1);
		friend vec3 operator/(const vec3& v1, const GLfloat s);

		friend vec3 operator+=(vec3& v1, const vec3& v2);
		friend vec3 operator-=(vec3& v1, const vec3& v2);
		friend vec3 operator*=(vec3& v1, const GLfloat s);
		friend vec3 operator/=(vec3& v1, const GLfloat s);

		friend std::istream& operator>>(std::istream& stream, vec3& v);
		friend std::ostream& operator<<(std::ostream& stream, const vec3& v);

		friend GLfloat dot(const vec3& v1, const vec3& v2);
		friend vec3 cross(const vec3& v1, const vec3& v2);
		friend GLfloat norm(const vec3& v);
		friend vec3 normalize(const vec3& v);
		friend GLfloat quadrance(const vec3& v);
	};

	struct vec4
	{
		GLfloat x, y, z, w;

		vec4();
		vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		vec4(const vec4& v);

		vec4 clean();

		vec4 operator=(const vec4& v);
		friend GLboolean operator==(const vec4& v1, const vec4& v2);
		friend GLboolean operator!=(const vec4& v1, const vec4& v2);

		friend vec4 operator+(const vec4& v1, const vec4& v2);
		friend vec4 operator-(const vec4& v1, const vec4& v2);
		friend vec4 operator-(const vec4& v);
		friend vec4 operator*(const vec4& v1, const GLfloat s);
		friend vec4 operator*(const GLfloat s, const vec4& v1);
		friend vec4 operator/(const vec4& v1, const GLfloat s);

		friend vec4 operator+=(vec4& v1, const vec4& v2);
		friend vec4 operator-=(vec4& v1, const vec4& v2);
		friend vec4 operator*=(vec4& v1, const GLfloat s);
		friend vec4 operator/=(vec4& v1, const GLfloat s);

		friend std::istream& operator>>(std::istream& stream, vec4& v);
		friend std::ostream& operator<<(std::ostream& stream, const vec4& v);

		friend GLfloat dot(const vec4& v1, const vec4& v2);
		friend GLfloat norm(const vec4& v);
		friend vec4 normalize(const vec4& v);
		friend GLfloat quadrance(const vec4& v);
	};
}
