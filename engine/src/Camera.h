#pragma once
#include "engine.h"

namespace engine
{
	class Camera
	{
	public:
		Camera(GLuint UBO_BP);

		void SetViewMatrix(mat4 view);
		void SetProjectionMatrix(mat4 proj);
		mat4 GetMatrix();

	private:
		mat4 ViewMatrix;
		mat4 ProjectionMatrix;
		GLuint ubo_bp;
		GLuint ubo_id;
	};
}
