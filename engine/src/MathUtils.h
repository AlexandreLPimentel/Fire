#pragma once

#include "GL/glew.h"
#include "vector.h"

const GLfloat PI = 3.14159265f;

namespace engine
{
	inline GLfloat deg2rad(float angle)
	{
		return angle * PI / 180.0f;
	}

	inline GLfloat rad2deg(GLfloat angle)
	{
		return angle * 180.0f / PI;
	}

	vec3 Lerp(const vec3& v0, const vec3& v1, const GLfloat t);

	GLfloat Clamp(const GLfloat val, const GLfloat min, const GLfloat max);
}