#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "GLUtils.h"

namespace engine
{
	const GLuint checkCompilation(const GLuint shader_id, const std::string& filename)
	{
		GLint compiled;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE) {
			GLint length;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
			GLchar* const log = new char[length];
			glGetShaderInfoLog(shader_id, length, &length, log);
			std::cerr << "[" << filename << "] " << std::endl << log;
			delete log;
		}
		return compiled;
	}

	Shader::Shader(string filename, GLenum shaderType) :
		type(shaderType), filename(filename)
	{
		loadFile(filename);
	}

	void Shader::Compile()
	{
		const char *source = code.c_str();

		id = glCreateShader(type);
		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		GLint isCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

		if (!isCompiled)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			stringstream ss;
			for (auto c : errorLog) ss << c;

			cerr << ss.str() << endl;

			Destroy();
			throw std::exception(("Shader " + filename + " was not compiled.").c_str());
		}
		checkOpenGLError("ERROR: Could not create shader " + filename);
	}

	void Shader::Destroy()
	{
		glDeleteShader(id);
	}

	void Shader::loadFile(string filename)
	{
		ifstream inFile;
		stringstream stream;
		inFile.open(filename);

		if (!inFile.is_open())
		{
			throw std::exception(("Shader file " + filename + " could not be opened.").c_str());
		}

		string line;
		while (getline(inFile, line))
		{
			stream << line << endl;
		}
		code = stream.str();
	}

	GLuint Shader::GetId() const
	{
		return id;
	}

	GLenum Shader::GetType() const
	{
		return type;
	}

	string Shader::GetFilename() const
	{
		return filename;
	}

}
