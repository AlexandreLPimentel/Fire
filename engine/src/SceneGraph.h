#pragma once
#include <vector>
#include "engine.h"

namespace engine
{
	const string MODEL_MATRIX = "ModelMatrix";
	const string CAMERA_MATRIX = "Camera";

	class Camera;
	class SceneGraph;

	struct Transform
	{
		vec3 Position;
		vec3 Scale;
		Quaternion Rotation;

		Transform();
	};

	class SceneNode
	{
	public:
		Transform transform;

		SceneNode(SceneNode* parent);
		void SetMesh(Mesh* m);
		void SetMatrix(const mat4& m);
		void SetShaderProgram(ShaderProgram* p);
		void Draw();
		void Destroy();
		void AddChild(SceneNode* node);
		void SetActive(bool active);
		SceneNode* CreateNode();

		void SetGraph(SceneGraph* g);
	private:
		SceneNode *parent;
		std::vector<SceneNode*> nodes;
		Mesh* mesh;
		mat4 matrix;
		ShaderProgram* shaderProgram;
		SceneGraph* graph;
		bool isActive;

		ShaderProgram* getShaderProgram();
		mat4 getModelMatrix();
	};

	class SceneGraph
	{
	public:
		SceneGraph();

		SceneNode* CreateNode();
		void Draw();
		void Destroy();
		Camera* GetCamera();
		SceneNode * GetRoot();
		void SetCamera(Camera* camera);

	private:
		SceneNode* root;
		Camera* camera;
	};
}
