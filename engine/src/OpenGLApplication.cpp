#include "OpenGLApplication.h"

#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <ctime>
#include "Input.h"

using namespace engine;

OpenGLApplication* currentContext;
GLfloat prevTime = 0;

void cleanup()
{
	currentContext->Destroy();
}

void display()
{
	GLfloat currentTime = clock();
	currentContext->SetFrameCount(currentContext->GetFrameCount() + 1);

	currentContext->Update((currentTime - prevTime) / 1000.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Draw something
	currentContext->Draw();
	glutSwapBuffers();
	prevTime = currentTime;
	//glutWarpPointer(currentContext->GetWidth() / 2, currentContext->GetHeight() / 2);
	Input::Update();
}

void idle()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	currentContext->SetWindowSize(w, h);
	glViewport(0, 0, w, h);
}

void timer(int value)
{
	std::string s = currentContext->GetTitle();
	glutSetWindow(currentContext->GetWindowHandle());
	glutSetWindowTitle(s.c_str());
	currentContext->SetFrameCount(0);
	glutTimerFunc(1000, timer, 0);
}

void OpenGLApplication::SetupCallbacks()
{
	currentContext = this;
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(Input::KeyboardDown);
	glutKeyboardUpFunc(Input::KeyboardUp);
	glutPassiveMotionFunc(Input::MouseMovement);
	glutMotionFunc(Input::MouseMovement);
	glutMouseFunc(Input::MouseButtonCallback);
}

void OpenGLApplication::CheckOpenGLInfo()
{
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
	std::cerr << "OpenGL version " << version << std::endl;
	std::cerr << "GLSL version " << glslVersion << std::endl;
}

void OpenGLApplication::SetupOpenGL()
{
	CheckOpenGLInfo();
	glClearColor(100 / 255.0f, 149 / 255.0f, 237 / 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void OpenGLApplication::SetupGLEW()
{
	glewExperimental = GL_TRUE;
	// Allow extension entry points to be loaded even if the extension isn't 
	// present in the driver's extensions string.
	GLenum result = glewInit();
	if (result != GLEW_OK) {
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	}
	GLenum err_code = glGetError();
	// You might get GL_INVALID_ENUM when loading GLEW.
}

void OpenGLApplication::SetupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	//glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	//glutInitContextFlags(GLUT_DEBUG);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	windowHandle = glutCreateWindow(title.c_str());
	if (windowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void OpenGLApplication::Create(int argc, char* argv[])
{
	this->SetupGLUT(argc, argv);
	this->SetupGLEW();
	this->SetupOpenGL();
	this->SetupCallbacks();
	this->Init();
	glutMainLoop();
}

OpenGLApplication::OpenGLApplication(const std::string title, int width, int height)
	: title(title), width(width), height(height)
{
	windowHandle = 0;
	frameCount = 0;
}

OpenGLApplication::~OpenGLApplication()
{

}

void OpenGLApplication::SetTitle(const std::string title)
{
	std::ostringstream oss;
	oss << title << ": " << currentContext->GetFrameCount() << " FPS @ (" << currentContext->GetWidth() << "x" << currentContext->GetHeight() << ")";
	this->title = oss.str();

}

const std::string OpenGLApplication::GetTitle()
{
	return title;
}

void OpenGLApplication::SetWindowSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

int OpenGLApplication::GetWidth()
{
	return width;
}

int OpenGLApplication::GetHeight()
{
	return height;
}

int OpenGLApplication::GetFrameCount()
{
	return frameCount;
}

void OpenGLApplication::SetFrameCount(int count)
{
	frameCount = count;
}

void OpenGLApplication::SetWindowHandle(int handle)
{
	windowHandle = handle;
}

int OpenGLApplication::GetWindowHandle()
{
	return windowHandle;
}
