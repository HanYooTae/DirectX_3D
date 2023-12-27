#pragma once
#include "Systems/IExecute.h"

#define MAX_Instance_Count 5000

class InstancingDemo : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:
	void CreateMesh();

private:
	Shader* shader;
	Material* material;

	vector<Mesh::VertexMesh> vertices;
	vector<UINT> indices;

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	VertexBuffer* instanceWorldBuffer;
	VertexBuffer* instanceColorBuffer;

	PerFrame* perFrame;
	Transform* transform[MAX_Instance_Count];
	Matrix worlds[MAX_Instance_Count];
	Color colors[MAX_Instance_Count];
};