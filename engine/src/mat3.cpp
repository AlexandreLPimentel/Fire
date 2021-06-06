#include "matrix.h"
#include <cmath>
#include "vector.h"

namespace engine
{
	mat3::mat3()
	{
		for (int i = 0; i < MAT_SIZE; ++i)
		{
			data[i] = 0;
		}
	}

	mat3::mat3(GLfloat m[MAT_SIZE])
	{
		throw std::exception("Not Implemented.");
	}

	mat3::mat3(
		const GLfloat m11, const GLfloat m12, const GLfloat m13,
		const GLfloat m21, const GLfloat m22, const GLfloat m23,
		const GLfloat m31, const GLfloat m32, const GLfloat m33)
	{
		data[0] = m11; data[3] = m12; data[6] = m13;
		data[1] = m21; data[4] = m22; data[7] = m23;
		data[2] = m31; data[5] = m32; data[8] = m33;
	}

	mat3::mat3(mat2 m) :
		mat3(
			m.data[0], m.data[2], 0,
			m.data[1], m.data[3], 0,
			0, 0, 1) {}

	mat3::mat3(mat4 m) :
		mat3(
			m.data[0], m.data[4], m.data[8],
			m.data[1], m.data[5], m.data[9],
			m.data[2], m.data[6], m.data[10]) {}


	mat3 mat3::clean()
	{
		for (int i = 0; i < MAT_SIZE; ++i)
		{
			if (fabs(data[i]) < EPSILON)
			{
				data[i] = 0;
			}
		}
		return *this;
	}

	mat3 mat3::operator=(const mat3& m)
	{
		for (int i = 0; i < MAT_SIZE; ++i)
		{
			data[i] = m.data[i];
		}
		return *this;
	}

	GLboolean operator==(const mat3& m1, const mat3& m2)
	{
		for (int i = 0; i < mat3::MAT_SIZE; ++i)
		{
			if (fabs(m1.data[i] - m2.data[i]) > EPSILON)
				return false;
		}
		return true;
	}

	GLboolean operator!=(const mat3& m1, const mat3& m2)
	{
		return !(m1 == m2);
	}

	mat3 operator+(const mat3& m1, const mat3& m2)
	{
		mat3 r;
		for (int i = 0; i < mat3::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] + m2.data[i];
		}
		return r;
	}

	mat3 operator-(const mat3& m1, const mat3& m2)
	{
		mat3 r;
		for (int i = 0; i < mat3::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] - m2.data[i];
		}
		return r;
	}

	mat3 operator-(const mat3& m1)
	{
		mat3 r;
		for (int i = 0; i < mat3::MAT_SIZE; ++i)
		{
			r.data[i] = -m1.data[i];
		}
		return r;
	}

	mat3 operator*(const mat3& m1, const mat3& m2)
	{
		int c = mat3::MAT_SIZE / 3;
		int l = mat3::MAT_SIZE / 3;

		mat3 r;

		for (int i = 0; i < c; i++)
		{
			for (int j = 0; j < l; j++)
			{
				r.data[j + i * l] = 0;

				for (int k = 0; k < c; k++)
				{
					r.data[i * c + j] += m1.data[c * k + j] * m2.data[i * c + k];
				}
			}
		}
		return r;
	}

	mat3 operator*(const mat3& m1, const GLfloat s)
	{
		mat3 r;
		for (int i = 0; i < mat3::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] * s;
		}
		return r;
	}

	mat3 operator*(const GLfloat s, const mat3& m1)
	{
		return m1 * s;
	}

	vec3 operator*(const mat3& m1, const vec3& v)
	{
		return vec3(
			v.x * m1.data[0] + v.y * m1.data[3] + v.z * m1.data[6],
			v.x * m1.data[1] + v.y * m1.data[4] + v.z * m1.data[7],
			v.x * m1.data[2] + v.y * m1.data[5] + v.z * m1.data[8]);
	}

	mat3 operator+=(mat3& m1, const mat3& m2)
	{
		return m1 = m1 + m2;
	}

	mat3 operator-=(mat3& m1, const mat3& m2)
	{
		return m1 = m1 - m2;
	}

	mat3 operator*=(mat3& m1, const mat3& m2)
	{
		return m1 = m1 * m2;
	}

	mat3 operator*=(mat3& m1, const GLfloat s)
	{
		return m1 = m1 * s;
	}

	GLfloat determinant(const mat3& m)
	{
		return m.data[0] * m.data[4] * m.data[8]
			+ m.data[1] * m.data[5] * m.data[6]
			+ m.data[3] * m.data[7] * m.data[2]
			- m.data[6] * m.data[4] * m.data[2]
			- m.data[3] * m.data[1] * m.data[8]
			- m.data[5] * m.data[7] * m.data[0];
	}

	mat3 transpose(const mat3& m)
	{
		return mat3(
			m.data[0], m.data[1], m.data[2],
			m.data[3], m.data[4], m.data[5],
			m.data[6], m.data[7], m.data[8]);
	}

	mat3 minor(const mat3& m)
	{
		GLfloat
			m11, m12, m13,
			m21, m22, m23,
			m31, m32, m33;

		m11 = determinant(mat2(m.data[4], m.data[7], m.data[5], m.data[8]));
		m12 = determinant(mat2(m.data[1], m.data[7], m.data[2], m.data[8]));
		m13 = determinant(mat2(m.data[1], m.data[4], m.data[2], m.data[5]));

		m21 = determinant(mat2(m.data[3], m.data[6], m.data[5], m.data[8]));
		m22 = determinant(mat2(m.data[0], m.data[6], m.data[2], m.data[8]));
		m23 = determinant(mat2(m.data[0], m.data[3], m.data[2], m.data[5]));

		m31 = determinant(mat2(m.data[3], m.data[6], m.data[4], m.data[7]));
		m32 = determinant(mat2(m.data[0], m.data[6], m.data[1], m.data[7]));
		m33 = determinant(mat2(m.data[0], m.data[3], m.data[1], m.data[4]));

		mat3 r(
			m11, -m12, m13,
			-m21, m22, -m23,
			m31, -m32, m33);
		return r;
	}

	mat3 adjoint(const mat3& m)
	{
		return transpose(minor(m));
	}

	mat3 inverse(const mat3& m)
	{
		GLfloat det = determinant(m);

		if (det == 0)
			throw std::invalid_argument("inverse: Determinant can not be zero");

		mat3 adj = adjoint(m);
		GLfloat s = 1 / det;
		return adj * s;
	}

	std::ostream& operator<<(std::ostream& ostream, const mat3& m)
	{
		ostream << "[ ";
		for (int i = 0; i < mat3::MAT_SIZE; ++i)
		{
			ostream << m.data[i] << " ";
		}
		ostream << "]" << std::endl;
		return ostream;
	}

	GLfloat* mat3::getGLMat()
	{
		return data;
	}
}
