#include "matrix.h"
#include <cmath>
#include "vector.h"

namespace engine
{
	mat2::mat2()
	{
		for (int i = 0; i < MAT_SIZE; ++i)
		{
			data[i] = 0;
		}
	}

	mat2::mat2(GLfloat m[MAT_SIZE])
	{
		throw std::exception("Not Implemented.");
	}

	mat2::mat2(
		GLfloat m11, GLfloat m12,
		GLfloat m21, GLfloat m22)
	{
		data[0] = m11; data[2] = m12;
		data[1] = m21; data[3] = m22;
	}

	mat2::mat2(mat3 m) :
		mat2(
			m.data[0], m.data[3],
			m.data[1], m.data[4]) {}

	mat2 mat2::clean()
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

	mat2 mat2::operator=(const mat2& m)
	{
		for (int i = 0; i < MAT_SIZE; ++i)
		{
			data[i] = m.data[i];
		}
		return *this;
	}

	GLboolean operator==(const mat2& m1, const mat2& m2)
	{
		for (int i = 0; i < mat2::MAT_SIZE; ++i)
		{
			if (fabs(m1.data[i] - m2.data[i]) > EPSILON)
				return false;
		}
		return true;
	}

	GLboolean operator!=(const mat2& m1, const mat2& m2)
	{
		return !(m1 == m2);
	}

	mat2 operator+(const mat2& m1, const mat2& m2)
	{
		mat2 r;
		for (int i = 0; i < mat2::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] + m2.data[i];
		}
		return r;
	}

	mat2 operator-(const mat2& m1, const mat2& m2)
	{
		mat2 r;
		for (int i = 0; i < mat2::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] - m2.data[i];
		}
		return r;
	}

	mat2 operator-(const mat2& m1)
	{
		mat2 r;
		for (int i = 0; i < mat2::MAT_SIZE; ++i)
		{
			r.data[i] = -m1.data[i];
		}
		return r;
	}

	mat2 operator*(const mat2& m1, const mat2& m2)
	{
		int c = mat2::MAT_SIZE / 2;
		int l = mat2::MAT_SIZE / 2;

		mat2 r;

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

	mat2 operator*(const mat2& m1, const GLfloat s)
	{
		mat2 r;
		for (int i = 0; i < mat2::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] * s;
		}
		return r;
	}

	mat2 operator*(const GLfloat s, const mat2& m1)
	{
		return m1 * s;
	}

	vec2 operator*(const mat2& m1, const vec2& v)
	{
		return vec2(
			v.x * m1.data[0] + v.y * m1.data[2],
			v.x * m1.data[1] + v.y * m1.data[3]);
	}

	mat2 operator+=(mat2& m1, const mat2& m2)
	{
		return m1 = m1 + m2;
	}

	mat2 operator-=(mat2& m1, const mat2& m2)
	{
		return m1 = m1 - m2;
	}

	mat2 operator*=(mat2& m1, const mat2& m2)
	{
		return m1 = m1 * m2;
	}

	mat2 operator*=(mat2& m1, const GLfloat s)
	{
		return m1 = m1 * s;
	}

	GLfloat determinant(const mat2& m)
	{
		return m.data[0] * m.data[3] - m.data[1] * m.data[2];
	}

	mat2 transpose(const mat2& m)
	{
		return mat2(
			m.data[0], m.data[1],
			m.data[2], m.data[3]);
	}

	mat2 inverse(const mat2& m)
	{
		GLfloat det = determinant(m);

		if (det == 0)
			throw std::invalid_argument("inverse: Determinant can not be zero");

		det = 1 / det;
		return mat2(
			m.data[3] * det, -m.data[2] * det,
			-m.data[1] * det, m.data[0] * det);
	}

	std::ostream& operator<<(std::ostream& ostream, const mat2& m)
	{
		ostream << "[ ";
		for (int i = 0; i < mat2::MAT_SIZE; ++i)
		{
			ostream << m.data[i] << " ";
		}
		ostream << "]" << std::endl;
		return ostream;
	}

	GLfloat* mat2::getGLMat()
	{
		return data;
	}
}
