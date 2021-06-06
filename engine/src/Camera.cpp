#include "Camera.h"
#include "GLUtils.h"

using namespace engine;

Camera::Camera(GLuint UBO_BP)
	: ubo_bp(ubo_bp) {
	glGenBuffers(1, &ubo_id);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo_id);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(mat4) * 2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, ubo_id);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	SetViewMatrix(MatrixFactory::mat4Identity());
	SetProjectionMatrix(MatrixFactory::mat4Identity());
	checkOpenGLError("Camera");
}

void Camera::SetProjectionMatrix(mat4 proj)
{
	ProjectionMatrix = proj;
	glBindBuffer(GL_UNIFORM_BUFFER, ubo_id);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), ProjectionMatrix.data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Camera::SetViewMatrix(mat4 view)
{
	ViewMatrix = view;
	glBindBuffer(GL_UNIFORM_BUFFER, ubo_id);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), ViewMatrix.data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

mat4 Camera::GetMatrix()
{
	return ProjectionMatrix * ViewMatrix;
}
