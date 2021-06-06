#pragma once

#include <string>
#include <vector>
#include "vector.h"

namespace engine
{
	class Mesh
	{
	public:
		const GLuint VERTICES = 0;
		const GLuint TEXCOORDS = 1;
		const GLuint NORMALS = 2;

		Mesh();
		Mesh(const std::string& filename);

		void Draw();
		void Destroy();

	private:
		std::vector<vec3> vertices;
		std::vector<vec3> verticesData;
		std::vector<vec2> textureCoords;
		std::vector<vec2> textureCoordsData;
		std::vector<vec3> normals;
		std::vector<vec3> normalsData;
		std::vector<unsigned int> vertexIdx;
		std::vector<unsigned int> textCoordIdx;
		std::vector<unsigned int> normalIdx;
		std::string filename;
		bool textCoordLoaded = false;
		bool normalsLoaded = false;

		GLuint vaoId;
		GLuint vboVertices;
		GLuint vboNormals;
		GLuint vboTextureCoords;

		void loadMeshData();
		void processMeshData();
		void freeMeshData();
		void parseLine(std::stringstream& sin);
		void parseVertex(std::stringstream& sin);
		void parseTextCoord(std::stringstream& sin);
		void parseNormal(std::stringstream& sin);
		void parseFace(std::stringstream& sin);
		void createBufferObjects();
	};
}
