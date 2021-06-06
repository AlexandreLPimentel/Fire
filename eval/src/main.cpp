#include <iostream>
#include "engine.h"
#include "Application.h"

using namespace engine;
using namespace std;

#define PI 3.14159265f

float deg2rad(float angle)
{
	return angle * PI / 180.0f;
}

void vecEval()
{
	vec3 array[] =
	{
		vec3(1,0,0),
		vec3(0,2,0),
		vec3(0,0,3)
	};

	float angle = deg2rad(90);

	for (int i = 0; i < 3; i++)
	{
		vec3 a = normalize(array[i]);
		for (int j = 0; j < 3; j++)
		{
			vec3 v = array[j];
			vec3 result = cos(angle) * v + sin(angle) * cross(a, v) + a * dot(a, v) * (1 - cos(angle));
			cout << "Rotation of " << v << " around " << a << " yields " << result.clean() << endl;
		}
	}
}

void matEval()
{
	mat4 T = MatrixFactory::mat3Translation(1, 0, 0);
	cout << "T = " << T << endl;
	mat4 R = MatrixFactory::mat4Rotation(deg2rad(90), vec3(0, 1, 0));
	cout << "R = " << R << endl;
	mat4 S = MatrixFactory::mat4Scale(2, 2, 2);
	cout << "S = " << S << endl;

	mat4 M = T * R * S;
	cout << "M = " << M << endl;

	mat3 N = transpose(inverse(mat3(M)));
	cout << "N = " << N << endl;

	vec4 vi(.5f, 0, 0, 1);
	vec3 ni(0, 1, 0);

	vec4 vf = M * vi;
	vec3 nf = N * ni;

	cout << "vi = " << vi << " -> vf = " << vf << endl;
	cout << "ni = " << ni << " -> ni = " << nf << endl;
}

int main(int argc, char* argv[])
{
	try
	{
		Application app;
		app.Create(argc, argv);
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

	cout << "Press Enter to continue..." << endl;
	getchar();

	return 0;
}
