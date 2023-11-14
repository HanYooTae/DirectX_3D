#pragma once
#include "Systems/IExecute.h"

class PolygonDemo : public IExecute
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
	struct Vertex
	{
		Vector3 Position;
	};

private:
	Shader* shader = nullptr;

	Vertex vertices[3];
	Vertex vertices2[3];

	// ComInterface�� Ư¡
	// ->new, delete�� �� �� ����. => Create, Release�� ��ü
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* vertexBuffer2;
	
};