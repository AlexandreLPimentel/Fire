#pragma once
#include <vector>
#include <map>
#include "Shader.h"

namespace engine {
	struct vec4;
	struct mat4;

	class ShaderProgram
	{
	public:
		ShaderProgram();
		
		void LoadShader(string filename, GLenum type);
		void AddShader(Shader shader);
		void RemoveShader(string filename);
		void RemoveShader(GLuint type);
		void Link();
		void Destroy();
		GLint GetUniformLocation(string name);
		
		void AddUniform(string name);
		void AddUniformBlock(string name, GLuint bp);
		void AddAttribute(string name, GLuint index);
		
		void SetUniformMatrix4(string name, const mat4& mat);
		void SetUniformVector4(string name, const vec4& vec);

		void Enable();
		void Disable();

	private:
		map<string, GLint> uniforms;
		map<string, GLint> attributes;
		map<string, GLuint> uniformBlocks;
		map<string, GLuint> uniformBlocksBinding;
		vector<Shader> shaders;
		GLuint id;
	};
}
