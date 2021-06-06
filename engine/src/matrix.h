#include <GL/glew.h>
#include <ostream>

namespace engine
{
	struct mat3;
	struct mat4;
	struct vec4;
	struct vec3;
	struct vec2;

	struct mat2
	{
		const static GLint MAT_SIZE = 4;
		GLfloat data[MAT_SIZE];

		mat2();
		mat2(GLfloat m[MAT_SIZE]);
		mat2(
			GLfloat m11, GLfloat m12,
			GLfloat m21, GLfloat m22);
		mat2(mat3 m);

		mat2 clean();

		mat2 operator=(const mat2& m);
		friend GLboolean operator==(const mat2& m1, const mat2& m2);
		friend GLboolean operator!=(const mat2& m1, const mat2& m2);

		friend mat2 operator+(const mat2& m1, const mat2& m2);
		friend mat2 operator-(const mat2& m1, const mat2& m2);
		friend mat2 operator-(const mat2& m1);

		friend mat2 operator*(const mat2& m1, const mat2& m2);
		friend mat2 operator*(const mat2& m1, const GLfloat s);
		friend mat2 operator*(const GLfloat s, const mat2& m1);
		friend vec2 operator*(const mat2& m1, const vec2& v);

		friend mat2 operator+=(mat2& m1, const mat2& m2);
		friend mat2 operator-=(mat2& m1, const mat2& m2);
		friend mat2 operator*=(mat2& m1, const mat2& m2);
		friend mat2 operator*=(mat2& m1, const GLfloat s);

		friend GLfloat determinant(const mat2& m);
		friend mat2 transpose(const mat2& m);
		friend mat2 inverse(const mat2& m);

		friend std::ostream& operator<<(std::ostream& ostream, const mat2& m);
		GLfloat* getGLMat();
	};

	struct mat3
	{
		const static GLint MAT_SIZE = 9;
		GLfloat data[MAT_SIZE];

		mat3();
		mat3(GLfloat m[MAT_SIZE]);
		mat3(
			const GLfloat m11, const GLfloat m12, const GLfloat m13,
			const GLfloat m21, const GLfloat m22, const GLfloat m23,
			const GLfloat m31, const GLfloat m32, const GLfloat m33);
		mat3(mat2 m);
		mat3(mat4 m);

		mat3 clean();

		mat3 operator=(const mat3& m);
		friend GLboolean operator==(const mat3& m1, const mat3& m2);
		friend GLboolean operator!=(const mat3& m1, const mat3& m2);

		friend mat3 operator+(const mat3& m1, const mat3& m2);
		friend mat3 operator-(const mat3& m1, const mat3& m2);
		friend mat3 operator-(const mat3& m1);

		friend mat3 operator*(const mat3& m1, const mat3& m2);
		friend mat3 operator*(const mat3& m1, const GLfloat s);
		friend mat3 operator*(const GLfloat s, const mat3& m1);
		friend vec3 operator*(const mat3& m1, const vec3& v);

		friend mat3 operator+=(mat3& m1, const mat3& m2);
		friend mat3 operator-=(mat3& m1, const mat3& m2);
		friend mat3 operator*=(mat3& m1, const mat3& m2);
		friend mat3 operator*=(mat3& m1, const GLfloat s);

		friend GLfloat determinant(const mat3& m);
		friend mat3 transpose(const mat3& m);
		friend mat3 minor(const mat3& m);
		friend mat3 adjoint(const mat3& m);
		friend mat3 inverse(const mat3& m);

		friend std::ostream& operator<<(std::ostream& ostream, const mat3& m);
		GLfloat* getGLMat();
	};

	struct mat4
	{
		const static GLint MAT_SIZE = 16;
		GLfloat data[MAT_SIZE];

		mat4();
		mat4(GLfloat m[MAT_SIZE]);
		mat4(
			GLfloat m11, GLfloat m12, GLfloat m13, GLfloat m14,
			GLfloat m21, GLfloat m22, GLfloat m23, GLfloat m24,
			GLfloat m31, GLfloat m32, GLfloat m33, GLfloat m34,
			GLfloat m41, GLfloat m42, GLfloat m43, GLfloat m44);
		mat4(mat3 m);

		mat4 clean();

		mat4 operator=(const mat4& m);
		friend GLboolean operator==(const mat4& m1, const mat4& m2);
		friend GLboolean operator!=(const mat4& m1, const mat4& m2);

		friend mat4 operator+(const mat4& m1, const mat4& m2);
		friend mat4 operator-(const mat4& m1, const mat4& m2);
		friend mat4 operator-(const mat4& m1);

		friend mat4 operator*(const mat4& m1, const mat4& m2);
		friend mat4 operator*(const mat4& m1, const GLfloat s);
		friend mat4 operator*(const GLfloat s, const mat4& m1);
		friend vec4 operator*(const mat4& m1, const vec4& v);

		friend mat4 operator+=(mat4& m1, const mat4& m2);
		friend mat4 operator-=(mat4& m1, const mat4& m2);
		friend mat4 operator*=(mat4& m1, const mat4& m2);
		friend mat4 operator*=(mat4& m1, const GLfloat s);

		friend GLfloat determinant(const mat4& m);
		friend mat4 transpose(const mat4& m);
		friend mat4 inverse(const mat4& m);

		friend std::ostream& operator<<(std::ostream& ostream, const mat4& m);
		GLfloat* getGLMat();
	};

	struct MatrixFactory
	{
		static mat2 mat2Identity();
		static mat2 mat2Rotation(const GLfloat angle);
		static mat2 mat2Scale(const GLfloat x, const GLfloat y);
		static mat2 mat2Scale(const vec2& v);
		static mat2 mat2Shear(const GLfloat x, const GLfloat y);
		static mat2 mat2Shear(const vec2& v);
		static mat3 mat2Translation(const GLfloat x, const GLfloat y);
		static mat3 mat2Translation(const vec2& v);
		
		static mat3 mat3Identity();
		static mat3 mat3Rotation(const GLfloat angle, const vec3& axis);
		static mat3 mat3Scale(const GLfloat x, const GLfloat y, const GLfloat z);
		static mat3 mat3Scale(const vec3& v);
		static mat3 mat3Shear(const GLfloat x, const GLfloat y, const GLfloat z);
		static mat3 mat3Shear(const vec3& v);
		static mat4 mat3Translation(const GLfloat x, const GLfloat y,const GLfloat z);
		static mat4 mat3Translation(const vec3& v);
		
		static mat4 mat4Identity();
		static mat4 mat4Rotation(const GLfloat angle, const vec3& axis);
		static mat4 mat4Scale(const GLfloat x, const GLfloat y, const GLfloat z);
		static mat4 mat4Scale(const vec3& v);
		static mat4 mat4Shear(const GLfloat x, const GLfloat y, const GLfloat z);
		static mat4 mat4Shear(const vec3& v);
		
		static mat3 dualMatrix(const vec3& v);
		static mat3 squaredDualMatrix(const vec3& v);

		static mat4 LookAtMatrix(const vec3& eye, const vec3& center, const vec3& up);
		static mat4 PerspectiveMatrix(const GLfloat fovy, const GLfloat width, const GLfloat heigth, const GLfloat zNear,
		                      const GLfloat zFar);
		static mat4 PerspectiveMatrix(const GLfloat fovy, const GLfloat aspect, const GLfloat zNear, const GLfloat zFar);
		static mat4 OrthoMatrix(
			const GLfloat left, const GLfloat right, 
			const GLfloat bottom, const GLfloat top, 
			const GLfloat near, const GLfloat far);
	};
}
