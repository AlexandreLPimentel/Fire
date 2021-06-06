#include "Mesh.h"
#include <sstream>
#include "GLUtils.h"

using namespace engine;

Mesh::Mesh()
{
}

Mesh::Mesh(const std::string& filename)
	: filename(filename)
{
	loadMeshData();
	processMeshData();
	freeMeshData();
	createBufferObjects();
}

void Mesh::Draw()
{
	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
}

void Mesh::Destroy()
{
	glBindVertexArray(vaoId);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(TEXCOORDS);
	glDisableVertexAttribArray(NORMALS);
	glDeleteBuffers(1, &vboVertices);
	glDeleteBuffers(1, &vboTextureCoords);
	glDeleteBuffers(1, &vboNormals);
	glDeleteVertexArrays(1, &vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}


void Mesh::parseVertex(std::stringstream& sin)
{
	vec3 v;
	sin >> v;
	verticesData.push_back(v);
}

void Mesh::parseTextCoord(std::stringstream& sin)
{
	vec2 v;
	sin >> v;
	textureCoordsData.push_back(v);
}

void Mesh::parseNormal(std::stringstream& sin)
{
	vec3 v;
	sin >> v;
	normalsData.push_back(v);
}

void Mesh::parseFace(std::stringstream& sin)
{
	std::string token;
	for (int i = 0; i < 3; i++) {
		std::getline(sin, token, '/');
		if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
		std::getline(sin, token, '/');
		if (token.size() > 0) textCoordIdx.push_back(std::stoi(token));
		std::getline(sin, token, ' ');
		if (token.size() > 0) normalIdx.push_back(std::stoi(token));
	}
}

void Mesh::createBufferObjects()
{

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);
	{
		glGenBuffers(1, &vboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

		if (textCoordLoaded)
		{
			glGenBuffers(1, &vboTextureCoords);
			glBindBuffer(GL_ARRAY_BUFFER, vboTextureCoords);
			glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(vec2), &textureCoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), 0);
		}
		if (normalsLoaded)
		{
			glGenBuffers(1, &vboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void Mesh::parseLine(std::stringstream& sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTextCoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);
}

void Mesh::loadMeshData()
{
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::exception("Could not open OBJ file.");

	std::string line;
	while (std::getline(file, line))
	{
		parseLine(std::stringstream(line));
	}
	textCoordLoaded = textureCoordsData.size() > 0;
	normalsLoaded = normalsData.size() > 0;
}

void Mesh::processMeshData()
{
	for (unsigned int i = 0; i < vertexIdx.size(); i++) {
		unsigned int vi = vertexIdx[i];
		vec3 v = verticesData[vi - 1];
		vertices.push_back(v);
		if (textCoordLoaded) {
			unsigned int ti = textCoordIdx[i];
			vec2 t = textureCoordsData[ti - 1];
			textureCoords.push_back(t);
		}
		if (normalsLoaded) {
			unsigned int ni = normalIdx[i];
			vec3 n = normalsData[ni - 1];
			normals.push_back(n);
		}
	}
}

void Mesh::freeMeshData()
{
	verticesData.clear();
	textureCoordsData.clear();
	normalsData.clear();
	vertexIdx.clear();
	textCoordIdx.clear();
	normalIdx.clear();
}
