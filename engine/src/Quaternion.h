#pragma once
#include <ostream>
#include <GL/glew.h>
#include "vector.h"

namespace engine
{
	struct mat4;

	class Quaternion
	{
	public:
		vec4 data;

		Quaternion(GLfloat theta, vec3 axis);
		Quaternion();
		Quaternion(const vec4& q);
		Quaternion(const Quaternion& q);
		Quaternion(const GLfloat t, const GLfloat x, const GLfloat y, const GLfloat z);
		
		void clean();

		void toAngleAxis(GLfloat& theta, vec3& axis) const;
		Quaternion operator=(const Quaternion& q);
		mat4 GLMatrix();

		friend float quadrance(const Quaternion& q);
		friend float norm(const Quaternion& q);
		friend Quaternion normalize(const Quaternion& q);
		friend Quaternion conjugate(const Quaternion& q);
		friend Quaternion inverse(const Quaternion& q);

		friend Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
		friend Quaternion operator*(const Quaternion& q, const float s);
		friend Quaternion operator*(const Quaternion& q0, const Quaternion& q1);

		friend Quaternion Lerp(const Quaternion& q0, const Quaternion& q1, float k);
		friend Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float k);

		friend bool operator==(const Quaternion& q0, const Quaternion& q1);
		friend bool operator!=(const Quaternion& q0, const Quaternion& q1);
		friend std::ostream& operator<<(std::ostream& ostream, const Quaternion& q);
		friend void Print(const std::string& s, const Quaternion& q);
		friend void PrintAngleAxis(const std::string& s, const Quaternion& q);
	};
}
