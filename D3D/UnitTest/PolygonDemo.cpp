#include "stdafx.h"
#include "PolygonDemo.h"

void PolygonDemo::Initialize()
{
	shader = new Shader(L"02_Pass.fxo");

	// Polygon1
	{
		vertices[0].Position = Vector3(-0.5f, +0.0f, +0.0f);
		vertices[1].Position = Vector3(+0.0f, +0.5f, +0.0f);
		vertices[2].Position = Vector3(+0.5f, +0.0f, +0.0f);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		//HRESULT result = D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer);
		//// S_OK가 아니라면 터짐
		//assert(SUCCEEDED(result));
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	// Polygon2
	{
		vertices2[0].Position = Vector3(-0.5f, +0.0f - 0.5f, +0.0f);
		vertices2[1].Position = Vector3(+0.0f, +0.5f - 0.5f, +0.0f);
		vertices2[2].Position = Vector3(+0.5f, +0.0f - 0.5f, +0.0f);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices2);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices2;

		//HRESULT result = D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer);
		//// S_OK가 아니라면 터짐
		//assert(SUCCEEDED(result));
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer2));
	}
}

void PolygonDemo::Destroy()
{
	SafeRelease(vertexBuffer2);
	SafeRelease(vertexBuffer);
	SafeDelete(shader);
}

void PolygonDemo::Update()
{
}

void PolygonDemo::Render()
{
	// 1번 polygon
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	shader->Draw(0, 0, 3);

	// 2번 polygon
	//UINT stride = sizeof(Vertex);
	//UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer2, &stride, &offset);
	//D3D::GetDC()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	shader->Draw(0, 1, 3);
}