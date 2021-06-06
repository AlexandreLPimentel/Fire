#include "matrix.h"
#include <cmath>
#include "vector.h"

namespace engine
{
	mat4::mat4()
	{
		for (int i = 0; i < MAT_SIZE; ++i)
		{
			data[i] = 0;
		}
	}

	mat4::mat4(GLfloat m[MAT_SIZE])
	{
		throw std::exception("Not Implemented.");
	}

	mat4::mat4(
		const GLfloat m11, const GLfloat m12, const GLfloat m13, const GLfloat m14,
		const GLfloat m21, const GLfloat m22, const GLfloat m23, const GLfloat m24,
		const GLfloat m31, const GLfloat m32, const GLfloat m33, const GLfloat m34,
		const GLfloat m41, const GLfloat m42, const GLfloat m43, const GLfloat m44)
	{
		data[0] = m11; data[4] = m12; data[8] = m13; data[12] = m14;
		data[1] = m21; data[5] = m22; data[9] = m23; data[13] = m24;
		data[2] = m31; data[6] = m32; data[10] = m33; data[14] = m34;
		data[3] = m41; data[7] = m42; data[11] = m43; data[15] = m44;
	}

	mat4::mat4(mat3 m) :
		mat4(
			m.data[0], m.data[3], m.data[6], 0,
			m.data[1], m.data[4], m.data[7], 0,
			m.data[2], m.data[5], m.data[8], 0,
			0, 0, 0, 1) {}


	mat4 mat4::clean()
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

	mat4 mat4::operator=(const mat4& m)
	{
		for (int i = 0; i < MAT_SIZE; ++i)
		{
			data[i] = m.data[i];
		}
		return *this;
	}

	GLboolean operator==(const mat4& m1, const mat4& m2)
	{
		for (int i = 0; i < mat4::MAT_SIZE; ++i)
		{
			if (fabs(m1.data[i] - m2.data[i]) > EPSILON)
				return false;
		}
		return true;
	}

	GLboolean operator!=(const mat4& m1, const mat4& m2)
	{
		return !(m1 == m2);
	}

	mat4 operator+(const mat4& m1, const mat4& m2)
	{
		mat4 r;
		for (int i = 0; i < mat4::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] + m2.data[i];
		}
		return r;
	}

	mat4 operator-(const mat4& m1, const mat4& m2)
	{
		mat4 r;
		for (int i = 0; i < mat4::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] - m2.data[i];
		}
		return r;
	}

	mat4 operator-(const mat4& m1)
	{
		mat4 r;
		for (int i = 0; i < mat4::MAT_SIZE; ++i)
		{
			r.data[i] = -m1.data[i];
		}
		return r;
	}

	mat4 operator*(const mat4& m1, const mat4& m2)
	{
		int c = mat4::MAT_SIZE / 4;
		int l = mat4::MAT_SIZE / 4;

		mat4 r;

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

	mat4 operator*(const mat4& m1, const GLfloat s)
	{
		mat4 r;
		for (int i = 0; i < mat4::MAT_SIZE; ++i)
		{
			r.data[i] = m1.data[i] * s;
		}
		return r;
	}

	mat4 operator*(const GLfloat s, const mat4& m1)
	{
		return m1 * s;
	}

	vec4 operator*(const mat4& m1, const vec4& v)
	{
		return vec4(
			v.x * m1.data[0] + v.y * m1.data[4] + v.z * m1.data[8] + v.w * m1.data[12],
			v.x * m1.data[1] + v.y * m1.data[5] + v.z * m1.data[9] + v.w * m1.data[13],
			v.x * m1.data[2] + v.y * m1.data[6] + v.z * m1.data[10] + v.w * m1.data[14],
			v.x * m1.data[3] + v.y * m1.data[7] + v.z * m1.data[11] + v.w * m1.data[15]);
	}

	mat4 operator+=(mat4& m1, const mat4& m2)
	{
		return m1 = m1 + m2;
	}

	mat4 operator-=(mat4& m1, const mat4& m2)
	{
		return m1 = m1 - m2;
	}

	mat4 operator*=(mat4& m1, const mat4& m2)
	{
		return m1 = m1 * m2;
	}

	mat4 operator*=(mat4& m1, const GLfloat s)
	{
		return m1 = m1 * s;
	}

	GLfloat determinant(const mat4& m)
	{
		return m.data[12] * m.data[9] * m.data[6] * m.data[3] - m.data[8] * m.data[13] * m.data[6] * m.data[3] -
			m.data[12] * m.data[5] * m.data[10] * m.data[3] + m.data[4] * m.data[13] * m.data[10] * m.data[3] +
			m.data[8] * m.data[5] * m.data[14] * m.data[3] - m.data[4] * m.data[9] * m.data[14] * m.data[3] -
			m.data[12] * m.data[9] * m.data[2] * m.data[7] + m.data[8] * m.data[13] * m.data[2] * m.data[7] +
			m.data[12] * m.data[1] * m.data[10] * m.data[7] - m.data[0] * m.data[13] * m.data[10] * m.data[7] -
			m.data[8] * m.data[1] * m.data[14] * m.data[7] + m.data[0] * m.data[9] * m.data[14] * m.data[7] +
			m.data[12] * m.data[5] * m.data[2] * m.data[11] - m.data[4] * m.data[13] * m.data[2] * m.data[11] -
			m.data[12] * m.data[1] * m.data[6] * m.data[11] + m.data[0] * m.data[13] * m.data[6] * m.data[11] +
			m.data[4] * m.data[1] * m.data[14] * m.data[11] - m.data[0] * m.data[5] * m.data[14] * m.data[11] -
			m.data[8] * m.data[5] * m.data[2] * m.data[15] + m.data[4] * m.data[9] * m.data[2] * m.data[15] +
			m.data[8] * m.data[1] * m.data[6] * m.data[15] - m.data[0] * m.data[9] * m.data[6] * m.data[15] -
			m.data[4] * m.data[1] * m.data[10] * m.data[15] + m.data[0] * m.data[5] * m.data[10] * m.data[15];
	}

	mat4 transpose(const mat4& m)
	{
		return mat4(
			m.data[0], m.data[1], m.data[2], m.data[3],
			m.data[4], m.data[5], m.data[6], m.data[7],
			m.data[8], m.data[9], m.data[10], m.data[11],
			m.data[12], m.data[13], m.data[14], m.data[15]);
	}

	mat4 inverse(const mat4& m)
	{
		mat4 result;
		GLfloat det;

		det = determinant(m);

		if (det == 0)
			throw std::invalid_argument("can't result.dataert matrix with determinant = 0");

		det = 1.0f / det;

		result.data[0] = m.data[5] * m.data[10] * m.data[15] -
			m.data[5] * m.data[11] * m.data[14] -
			m.data[9] * m.data[6] * m.data[15] +
			m.data[9] * m.data[7] * m.data[14] +
			m.data[13] * m.data[6] * m.data[11] -
			m.data[13] * m.data[7] * m.data[10];

		result.data[4] = -m.data[4] * m.data[10] * m.data[15] +
			m.data[4] * m.data[11] * m.data[14] +
			m.data[8] * m.data[6] * m.data[15] -
			m.data[8] * m.data[7] * m.data[14] -
			m.data[12] * m.data[6] * m.data[11] +
			m.data[12] * m.data[7] * m.data[10];

		result.data[8] = m.data[4] * m.data[9] * m.data[15] -
			m.data[4] * m.data[11] * m.data[13] -
			m.data[8] * m.data[5] * m.data[15] +
			m.data[8] * m.data[7] * m.data[13] +
			m.data[12] * m.data[5] * m.data[11] -
			m.data[12] * m.data[7] * m.data[9];

		result.data[12] = -m.data[4] * m.data[9] * m.data[14] +
			m.data[4] * m.data[10] * m.data[13] +
			m.data[8] * m.data[5] * m.data[14] -
			m.data[8] * m.data[6] * m.data[13] -
			m.data[12] * m.data[5] * m.data[10] +
			m.data[12] * m.data[6] * m.data[9];

		result.data[1] = -m.data[1] * m.data[10] * m.data[15] +
			m.data[1] * m.data[11] * m.data[14] +
			m.data[9] * m.data[2] * m.data[15] -
			m.data[9] * m.data[3] * m.data[14] -
			m.data[13] * m.data[2] * m.data[11] +
			m.data[13] * m.data[3] * m.data[10];

		result.data[5] = m.data[0] * m.data[10] * m.data[15] -
			m.data[0] * m.data[11] * m.data[14] -
			m.data[8] * m.data[2] * m.data[15] +
			m.data[8] * m.data[3] * m.data[14] +
			m.data[12] * m.data[2] * m.data[11] -
			m.data[12] * m.data[3] * m.data[10];

		result.data[9] = -m.data[0] * m.data[9] * m.data[15] +
			m.data[0] * m.data[11] * m.data[13] +
			m.data[8] * m.data[1] * m.data[15] -
			m.data[8] * m.data[3] * m.data[13] -
			m.data[12] * m.data[1] * m.data[11] +
			m.data[12] * m.data[3] * m.data[9];

		result.data[13] = m.data[0] * m.data[9] * m.data[14] -
			m.data[0] * m.data[10] * m.data[13] -
			m.data[8] * m.data[1] * m.data[14] +
			m.data[8] * m.data[2] * m.data[13] +
			m.data[12] * m.data[1] * m.data[10] -
			m.data[12] * m.data[2] * m.data[9];

		result.data[2] = m.data[1] * m.data[6] * m.data[15] -
			m.data[1] * m.data[7] * m.data[14] -
			m.data[5] * m.data[2] * m.data[15] +
			m.data[5] * m.data[3] * m.data[14] +
			m.data[13] * m.data[2] * m.data[7] -
			m.data[13] * m.data[3] * m.data[6];

		result.data[6] = -m.data[0] * m.data[6] * m.data[15] +
			m.data[0] * m.data[7] * m.data[14] +
			m.data[4] * m.data[2] * m.data[15] -
			m.data[4] * m.data[3] * m.data[14] -
			m.data[12] * m.data[2] * m.data[7] +
			m.data[12] * m.data[3] * m.data[6];

		result.data[10] = m.data[0] * m.data[5] * m.data[15] -
			m.data[0] * m.data[7] * m.data[13] -
			m.data[4] * m.data[1] * m.data[15] +
			m.data[4] * m.data[3] * m.data[13] +
			m.data[12] * m.data[1] * m.data[7] -
			m.data[12] * m.data[3] * m.data[5];

		result.data[14] = -m.data[0] * m.data[5] * m.data[14] +
			m.data[0] * m.data[6] * m.data[13] +
			m.data[4] * m.data[1] * m.data[14] -
			m.data[4] * m.data[2] * m.data[13] -
			m.data[12] * m.data[1] * m.data[6] +
			m.data[12] * m.data[2] * m.data[5];

		result.data[3] = -m.data[1] * m.data[6] * m.data[11] +
			m.data[1] * m.data[7] * m.data[10] +
			m.data[5] * m.data[2] * m.data[11] -
			m.data[5] * m.data[3] * m.data[10] -
			m.data[9] * m.data[2] * m.data[7] +
			m.data[9] * m.data[3] * m.data[6];

		result.data[7] = m.data[0] * m.data[6] * m.data[11] -
			m.data[0] * m.data[7] * m.data[10] -
			m.data[4] * m.data[2] * m.data[11] +
			m.data[4] * m.data[3] * m.data[10] +
			m.data[8] * m.data[2] * m.data[7] -
			m.data[8] * m.data[3] * m.data[6];

		result.data[11] = -m.data[0] * m.data[5] * m.data[11] +
			m.data[0] * m.data[7] * m.data[9] +
			m.data[4] * m.data[1] * m.data[11] -
			m.data[4] * m.data[3] * m.data[9] -
			m.data[8] * m.data[1] * m.data[7] +
			m.data[8] * m.data[3] * m.data[5];

		result.data[15] = m.data[0] * m.data[5] * m.data[10] -
			m.data[0] * m.data[6] * m.data[9] -
			m.data[4] * m.data[1] * m.data[10] +
			m.data[4] * m.data[2] * m.data[9] +
			m.data[8] * m.data[1] * m.data[6] -
			m.data[8] * m.data[2] * m.data[5];

		result *= det;

		return result;
	}

	std::ostream& operator<<(std::ostream& ostream, const mat4& m)
	{
		ostream << "[ ";
		for (int i = 0; i < mat4::MAT_SIZE; ++i)
		{
			ostream << m.data[i] << " ";
		}
		ostream << "]" << std::endl;
		return ostream;
	}

	GLfloat* mat4::getGLMat()
	{
		return data;
	}
}
