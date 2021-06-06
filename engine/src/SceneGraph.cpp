#include "SceneGraph.h"

using namespace engine;

SceneGraph::SceneGraph()
{
	root = new SceneNode(nullptr);
}

SceneNode* SceneGraph::CreateNode()
{
	return root->CreateNode();
}

void SceneGraph::Draw()
{
	root->Draw();
}

void SceneGraph::Destroy()
{
	root->Destroy();
}

Camera* SceneGraph::GetCamera()
{
	return camera;
}

SceneNode* SceneGraph::GetRoot()
{
	return root;
}

void SceneGraph::SetCamera(Camera* camera)
{
	this->camera = camera;
}
