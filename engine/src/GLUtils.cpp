#include <GL/glew.h>
#include <iostream>

using namespace std;

namespace engine {
	bool isOpenGLError() {
		bool isError = false;
		GLenum errCode;
		const GLubyte *errString;
		while ((errCode = glGetError()) != GL_NO_ERROR) {
			isError = true;
			errString = gluErrorString(errCode);
			cerr << "OpenGL ERROR " << errCode << ": [" << errString << "]." << endl;
		}
		return isError;
	}

	void checkOpenGLError(string error)
	{
		if (isOpenGLError()) {
			cerr << error.c_str() << endl;
			throw std::exception(error.c_str());
		}
	}
}
