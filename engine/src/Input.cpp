#include "Input.h"
#include <iostream>
#include <GL/freeglut_std.h>

using namespace engine;
using namespace std;

bool Input::GetKey(const unsigned char key)
{
	return getInstance().keysDown[key];
}

bool Input::GetKeyDown(const unsigned char key)
{
	return !getInstance().lastFrame[key] && getInstance().keysDown[key];
}

bool Input::GetKeyUp(const unsigned char key)
{
	return getInstance().lastFrame[key] && !getInstance().keysDown[key];
}

bool Input::GetMouseButton(const int button)
{
	return getInstance().mouseButton[button];
}

bool Input::GetMouseButtonDown(const int button)
{
	return !getInstance().mouseButtonLastFrame[button] && getInstance().mouseButton[button];
}

bool Input::GetMouseButtonUp(const int button)
{
	return getInstance().mouseButtonLastFrame[button] && !getInstance().mouseButton[button];
}

void Input::MouseButtonCallback(const int button, const int state, int x, int y)
{
	if (GLUT_DOWN == state)
		getInstance().mouseButton[button] = true;
	else
		getInstance().mouseButton[button] = false;
}

vec2 Input::GetMouseMovement()
{
	return getInstance().mouseMovement;
}

vec2 Input::GetMousePosition()
{
	return getInstance().mousePosition;
}

void Input::KeyboardDown(unsigned char key, int x, int y)
{
	getInstance().keysDown[key] = true;
}

void Input::KeyboardUp(unsigned char key, int x, int y)
{
	getInstance().keysDown[key] = false;
}

void Input::MouseMovement(int x, int y)
{
	getInstance().mousePosition.x = x;
	getInstance().mousePosition.y = y;
	float prevx = getInstance().prevMousePosition.x;
	float prevy = getInstance().prevMousePosition.y;

	getInstance().mouseMovement.x += x - prevx;
	getInstance().mouseMovement.y += y - prevy;

	getInstance().prevMousePosition.x = x;
	getInstance().prevMousePosition.y = y;
}

Input::Input()
{}

Input::~Input()
{}

Input& Input::getInstance()
{
	static Input instance; // Guaranteed to be destroyed.
						   // Instantiated on first use.
	return instance;
}

void Input::Update()
{
	getInstance().lastFrame = getInstance().keysDown;
	getInstance().mouseMovement = vec2();
	getInstance().mouseButtonLastFrame = getInstance().mouseButton;
}
