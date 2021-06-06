#include "SceneGraph.h"

using namespace engine;

Transform::Transform()
{
	Rotation = Quaternion();
	Position = vec3();
	Scale = vec3(1, 1, 1);
}

SceneNode::SceneNode(SceneNode* parent)
	: parent(parent)
{
	mesh = nullptr;
	matrix = MatrixFactory::mat4Identity();
	shaderProgram = nullptr;
	isActive = true;
	transform = Transform();
}

void SceneNode::SetMesh(Mesh* m)
{
	mesh = m;
}

void SceneNode::SetMatrix(const mat4& m)
{
	matrix = m;
}

void SceneNode::SetShaderProgram(ShaderProgram* p)
{
	shaderProgram = p;
}

void SceneNode::Draw()
{
	if (!isActive)
		return;

	for (SceneNode* node : nodes)
		node->Draw();

	if (mesh == nullptr)
		return;

	ShaderProgram* program = getShaderProgram();
	mat4 mat = getModelMatrix();

	program->Enable();
	program->SetUniformMatrix4(MODEL_MATRIX, mat);

	mesh->Draw();

	program->Disable();
}

void SceneNode::Destroy()
{
	mesh->Destroy();
	shaderProgram->Destroy();
}

void SceneNode::AddChild(SceneNode* node)
{
	nodes.push_back(node);
}

void SceneNode::SetActive(bool active)
{
	isActive = active;
}

SceneNode* SceneNode::CreateNode()
{
	SceneNode* node = new SceneNode(this);
	nodes.push_back(node);
	return node;
}

void SceneNode::SetGraph(SceneGraph* g)
{
	graph = g;
}

ShaderProgram* SceneNode::getShaderProgram()
{
	if (shaderProgram != nullptr)
		return shaderProgram;

	if (parent == nullptr)
		throw exception("No shader program found.");
	return parent->getShaderProgram();

}

mat4 SceneNode::getModelMatrix()
{
	matrix =
		MatrixFactory::mat3Translation(transform.Position) *
		transform.Rotation.GLMatrix() *
		MatrixFactory::mat4Scale(transform.Scale);

	if (parent != nullptr)
		return parent->getModelMatrix() * matrix;
	return matrix;
}
