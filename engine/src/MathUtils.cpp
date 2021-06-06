#include "MathUtils.h"

using namespace engine;

vec3 engine::Lerp(const vec3& v0, const vec3& v1, const GLfloat t)
{
	return v0 + t * (v1 - v0);
}

GLfloat engine::Clamp(const GLfloat val, const GLfloat min, const GLfloat max)
{
	if (max < min) throw std::exception("Invalid interval");

	GLfloat res = val;
	if (val < min)
		res = min;
	if (val > max)
		res = max;
	return res;
}

