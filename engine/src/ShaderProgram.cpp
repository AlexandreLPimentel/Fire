#include "ShaderProgram.h"
#include "GLUtils.h"
#include <iostream>
#include "matrix.h"
#include "vector.h"

using namespace engine;

void checkLinkage(const GLuint program_id) {
	GLint linked;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE) {
		GLint length;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetProgramInfoLog(program_id, length, &length, log);
		std::cerr << "[LINK] " << std::endl << log << std::endl;
		delete log;
	}
}

ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
	checkOpenGLError("ERROR: Could not create shader program.");
}

void ShaderProgram::LoadShader(string filename, GLenum type)
{
	Shader shader(filename, type);
	shader.Compile();
	AddShader(shader);
}

void ShaderProgram::AddShader(Shader shader)
{
	glAttachShader(id, shader.GetId());
	shaders.push_back(shader);
}

void ShaderProgram::RemoveShader(string filename)
{
	for (Shader shader : shaders)
	{
		if (shader.GetFilename() == filename)
		{
			glDetachShader(id, shader.GetId());
			shader.Destroy();
		}
	}
}

void ShaderProgram::RemoveShader(GLuint type)
{
	for (Shader shader : shaders)
	{
		if (shader.GetType() == type)
		{
			glDetachShader(id, shader.GetId());
			shader.Destroy();
		}
	}
}

void ShaderProgram::Link()
{
	for (auto& pair : attributes)
		glBindAttribLocation(id, pair.second, pair.first.c_str());

	glLinkProgram(id);

	for (auto& pair : uniforms)
		pair.second = glGetUniformLocation(id, pair.first.c_str());

	for (auto& pair : uniformBlocks)
	{
		pair.second = glGetUniformBlockIndex(id, pair.first.c_str());
		glUniformBlockBinding(id, pair.second, uniformBlocksBinding[pair.first]);
	}

	checkLinkage(id);

	for (Shader s : shaders)
	{
		glDetachShader(id, s.GetId());
	}
}

void ShaderProgram::Destroy()
{
	glUseProgram(0);
	for (Shader shader : shaders)
	{
		shader.Destroy();
	}
	glDeleteProgram(id);
}

GLint ShaderProgram::GetUniformLocation(string name)
{
	return uniforms[name];
}

void ShaderProgram::AddUniform(string name)
{
	uniforms[name] = -1;
}

void ShaderProgram::AddUniformBlock(string name, GLuint bp)
{
	uniformBlocks[name] = -1;
	uniformBlocksBinding[name] = bp;
}

void ShaderProgram::AddAttribute(string name, GLuint index)
{
	attributes[name] = index;
}

void ShaderProgram::SetUniformMatrix4(string name, const mat4& mat)
{
	glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, mat.data);
}

void ShaderProgram::SetUniformVector4(string name, const vec4& vec)
{
	glUniform4f(uniforms[name], vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::Enable()
{
	glUseProgram(id);
}

void ShaderProgram::Disable()
{
	glUseProgram(0);
}
