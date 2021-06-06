#pragma once
#include <string>
#include <GL/glew.h>

using namespace std;

namespace engine
{
	class Shader
	{
	public:
		Shader(string filename, GLenum shaderType);

		GLuint GetId() const;
		GLenum GetType() const;
		string GetFilename() const;

		void Compile();
		void Destroy();
	private:
		GLuint id;
		GLenum type;
		string code;
		string filename;

		void loadFile(string filename);
	};
}
