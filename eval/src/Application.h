#pragma once
#include "OpenGLApplication.h"
#include "ShaderProgram.h"

using namespace engine;

class Application : public OpenGLApplication
{
public:
	Application()
		: OpenGLApplication("My Application", 800, 800)
	{
	}

	void Init() override;
	void Update(const GLfloat deltaTime) override;
	void Draw() override;
	void Destroy() override;

private:
	ShaderProgram * shaderProgram;
};