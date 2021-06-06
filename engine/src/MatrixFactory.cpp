#include "matrix.h"
#include "vector.h"
#include <iostream>
#include "MathUtils.h"

namespace engine
{
	struct vec2;

	mat2 MatrixFactory::mat2Identity()
	{
		return mat2(1, 0, 0, 1);
	}

	mat2 MatrixFactory::mat2Rotation(const GLfloat angle)
	{
		return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
	}

	mat2 MatrixFactory::mat2Scale(const GLfloat x, const GLfloat y)
	{
		return mat2(x, 0, 0, y);
	}

	mat2 MatrixFactory::mat2Scale(const vec2& v)
	{
		return mat2Scale(v.x, v.y);
	}

	mat2 MatrixFactory::mat2Shear(const GLfloat x, const GLfloat y)
	{
		return mat2(1, x, y, 0);
	}

	mat2 MatrixFactory::mat2Shear(const vec2& v)
	{
		return mat2Shear(v.x, v.y);
	}

	mat3 MatrixFactory::mat2Translation(const GLfloat x, const GLfloat y)
	{
		return mat3(
			1, 0, x,
			0, 1, y,
			0, 0, 1);
	}

	mat3 MatrixFactory::mat2Translation(const vec2& v)
	{
		return mat2Translation(v.x, v.y);
	}


	mat3 MatrixFactory::mat3Identity()
	{
		return mat3(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1);
	}

	mat3 MatrixFactory::mat3Rotation(const GLfloat angle, const vec3& axis)
	{
		mat3 A, A2;
		vec3 a = normalize(axis);

		A = dualMatrix(a);
		A2 = squaredDualMatrix(a);

		return mat3Identity() + sin(angle) * A + (1 - cos(angle)) * A2;
	}

	mat3 MatrixFactory::mat3Scale(const GLfloat x, const GLfloat y, const GLfloat z)
	{
		return mat3(
			x, 0, 0,
			0, y, 0,
			0, 0, z);
	}

	mat3 MatrixFactory::mat3Scale(const vec3& v)
	{
		return mat3Scale(v.x, v.y, v.z);
	}

	mat3 MatrixFactory::mat3Shear(const GLfloat x, const GLfloat y, const GLfloat z)
	{
		throw std::exception("Not implemented exception");
	}

	mat3 MatrixFactory::mat3Shear(const vec3& v)
	{
		return mat3Shear(v.x, v.y, v.z);
	}

	mat4 MatrixFactory::mat3Translation(const GLfloat x, const GLfloat y, const GLfloat z)
	{
		return mat4(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1);
	}

	mat4 MatrixFactory::mat3Translation(const vec3& v)
	{
		return mat3Translation(v.x, v.y, v.z);
	}

	mat4 MatrixFactory::mat4Identity()
	{
		return mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}

	mat4 MatrixFactory::mat4Rotation(const GLfloat angle, const vec3& axis)
	{
		return mat4(mat3Rotation(angle, axis));
	}

	mat4 MatrixFactory::mat4Scale(const GLfloat x, const GLfloat y, const GLfloat z)
	{
		return mat3Scale(x, y, z);
	}

	mat4 MatrixFactory::mat4Scale(const vec3& v)
	{
		return mat4Scale(v.x, v.y, v.z);
	}

	mat4 MatrixFactory::mat4Shear(const GLfloat x, const GLfloat y, const GLfloat z)
	{
		throw std::exception("Not implemented exception");
	}

	mat4 MatrixFactory::mat4Shear(const vec3& v)
	{
		throw std::exception("Not implemented exception");
	}

	mat3 MatrixFactory::dualMatrix(const vec3& v)
	{
		return mat3(
			0, -v.z, v.y,
			v.z, 0, -v.x,
			-v.y, v.x, 0);
	}

	mat3 MatrixFactory::squaredDualMatrix(const vec3& v)
	{
		return mat3(
			-pow(v.z, 2) - pow(v.y, 2), v.x * v.y, v.x * v.z,
			v.x * v.y, -pow(v.z, 2) - pow(v.x, 2), v.y * v.z,
			v.x * v.z, v.y * v.z, -pow(v.y, 2) - pow(v.x, 2));
	}

	mat4 MatrixFactory::LookAtMatrix(const vec3& eye, const vec3& center, const vec3& up)
	{
		vec3 view = center - eye;
		vec3 v = normalize(view);
		vec3 side = cross(v, up);
		vec3 s = normalize(side);
		vec3 u = cross(s, v);

		return mat4(
			s.x, s.y, s.z, dot(-s, eye),
			u.x, u.y, u.z, dot(-u, eye),
			-v.x, -v.y, -v.z, dot(v, eye),
			0, 0, 0, 1);
	}

	mat4 MatrixFactory::PerspectiveMatrix(const GLfloat fovy, const GLfloat width, const GLfloat heigth, const GLfloat zNear, const GLfloat zFar)
	{
		return PerspectiveMatrix(fovy, width / heigth, zNear, zFar);
	}

	mat4 MatrixFactory::PerspectiveMatrix(const GLfloat fovy, const GLfloat aspect, const GLfloat zNear, const GLfloat zFar)
	{
		if (zNear <= 0)
			throw std::exception("Invalid zNear.");

		if (zFar <= 0)
			throw std::exception("Invalid zFar.");

		GLfloat angle, d;

		angle = fovy / 2;
		d = 1 / tan(angle);

		return mat4(
			d / aspect, 0, 0, 0,
			0, d, 0, 0,
			0, 0, (zNear + zFar) / (zNear - zFar), (2 * zNear * zFar) / (zNear - zFar),
			0, 0, -1, 0);
	}

	mat4 MatrixFactory::OrthoMatrix(
		const GLfloat left, const GLfloat right,
		const GLfloat bottom, const GLfloat top,
		const GLfloat near, const GLfloat far)
	{
		return mat4(
			2 / (right - left), 0, 0, (left + right) / (left - right),
			0, 2 / (top - bottom), 0, (bottom + top) / (bottom - top),
			0, 0, 2 / (near - far), (near + far) / (near - far),
			0, 0, 0, 1);
	}
}
