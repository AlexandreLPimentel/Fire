#include "Application.h"
#include "engine.h"
#include "GLUtils.h"
#include <iostream>
#include <string>
#include "MathUtils.h"
#include "Animation.h"

using namespace std;

const int UBO_BP = 0;

GLfloat mediumScale = 1 / (sqrt(0.5f) / 0.5f);
GLfloat smallScale = 1 / sqrt(0.5f / 0.125f);

mat4 ViewMatrix;
mat4 OrthoMatrix;
mat4 PerspectiveMatrix;
mat4* ProjectionMatrix = &PerspectiveMatrix;

bool useOrtho = true;

float CameraDistance = 10.0f;
vec2 CameraAngles;
bool IsGimbal = true;

Quaternion Orientation;

Mesh* SphereMesh;
Mesh* QuadMesh;

SceneGraph* Graph;

void Reset()
{
	Orientation = Quaternion();
	CameraAngles = vec2();
	CameraDistance = 5.0f;
}

void SetupViewMatrix()
{
	ViewMatrix =
		MatrixFactory::mat3Translation(0, 0, -CameraDistance) *
		MatrixFactory::mat4Rotation(30, vec3(0, 1, 0));
}


void Application::Init()
{
	SphereMesh = new Mesh("src/resources/Sphere_Smooth_UV.obj");
	QuadMesh = new Mesh("src/resources/Quad_UV.obj");


	Graph = new SceneGraph();
	Graph->SetCamera(new Camera(UBO_BP));

	shaderProgram = new ShaderProgram();
	shaderProgram->LoadShader("src/Shaders/vertex.glsl", GL_VERTEX_SHADER);
	shaderProgram->LoadShader("src/Shaders/frag.glsl", GL_FRAGMENT_SHADER);
	shaderProgram->AddUniform("ModelMatrix");
	shaderProgram->AddUniform("Camera");
	shaderProgram->AddUniformBlock("Camera", UBO_BP);
	shaderProgram->Link(); 
	
	Graph->GetRoot()->SetShaderProgram(shaderProgram);

	SceneNode * SphereNode = Graph->CreateNode();
	SphereNode->SetMesh(SphereMesh);
	
	SceneNode * FloorNode = Graph->CreateNode();
	FloorNode->SetMesh(QuadMesh);
	FloorNode->transform.Position.y = -1;
	FloorNode->transform.Scale = vec3(2, 2, 2);

	SetupViewMatrix();

	float aspect = float(width) / height;
	PerspectiveMatrix = MatrixFactory::PerspectiveMatrix(70, aspect, 0.3f, 100);
	OrthoMatrix = MatrixFactory::OrthoMatrix(-aspect, aspect, -1, 1, 0, 100);

	Graph->GetCamera()->SetProjectionMatrix(*ProjectionMatrix);
	Graph->GetCamera()->SetViewMatrix(ViewMatrix);

	checkOpenGLError("ERROR: Init failed.");
}

void Application::Update(const GLfloat deltaTime)
{
	if (Input::GetKeyDown('x'))
	{
		Destroy();
		exit(EXIT_SUCCESS);
	}

	if (Input::GetKeyDown('p'))
	{
		if (useOrtho)
		{
			useOrtho = false;
			Graph->GetCamera()->SetProjectionMatrix(OrthoMatrix);
		}
		else
		{
			Graph->GetCamera()->SetProjectionMatrix(PerspectiveMatrix);
			useOrtho = true;
		}
	}

	if (Input::GetKeyDown('v'))
		Reset();
	if (Input::GetKeyDown('g'))
	{
		IsGimbal = !IsGimbal;
		Reset();
	}

	if (Input::GetKey('w'))
		CameraDistance -= 20 * deltaTime;
	if (Input::GetKey('s'))
		CameraDistance += 20 * deltaTime;

	vec2 mouse;
	if (Input::GetMouseButton(GLUT_LEFT_BUTTON))
	{
		CameraAngles += Input::GetMouseMovement() * deltaTime * 0.5f;
		mouse = Input::GetMouseMovement() * 30.0f * deltaTime;
	}
	float z = 0;
	if (Input::GetMouseButton(GLUT_RIGHT_BUTTON))
	{
		z = Input::GetMouseMovement().x * deltaTime * 30.0f;
	}

	if (IsGimbal)
	{
		ViewMatrix =
			MatrixFactory::mat3Translation(0, 0, -CameraDistance) *
			MatrixFactory::mat4Rotation(CameraAngles.y, vec3(1, 0, 0)) *
			MatrixFactory::mat4Rotation(CameraAngles.x, vec3(0, 1, 0));
	}
	else
	{
		Quaternion q1(mouse.x, vec3(0, 1, 0));
		Quaternion q2(mouse.y, vec3(1, 0, 0));
		Quaternion q3(z, vec3(0, 0, 1));
		Orientation = q3 * q2 * q1 * Orientation;
		Orientation = normalize(Orientation);
		ViewMatrix =
			MatrixFactory::mat3Translation(0, 0, -CameraDistance) *
			Orientation.GLMatrix();
	}

	Graph->GetCamera()->SetViewMatrix(ViewMatrix);

	string title = IsGimbal ? "Gimbal True" : "Gimbal False";
	title += " x = " + to_string(CameraAngles.x) + " y = " + to_string(CameraAngles.y);
	SetTitle(title);
}

void Application::Draw()
{
	
	Graph->Draw();
	checkOpenGLError("ERROR: Could not draw scene.");
}

void Application::Destroy()
{
	shaderProgram->Destroy();
	SphereMesh->Destroy();
}
