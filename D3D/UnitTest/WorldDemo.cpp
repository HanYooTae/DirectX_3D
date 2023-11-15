#include "stdafx.h"
#include "WorldDemo.h"

void WorldDemo::Initialize()
{
	shader = new Shader(L"04_World.fxo");

	// Polygon1
	{
		vertices[0].Position = Vector3(-0.5f, -0.5f, +0.0f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, +0.0f);
		vertices[2].Position = Vector3(+0.5f, -0.5f, +0.0f);
		vertices[3].Position = Vector3(+0.5f, -0.5f, +0.0f);
		vertices[4].Position = Vector3(-0.5f, +0.5f, +0.0f);
		vertices[5].Position = Vector3(+0.5f, +0.5f, +0.0f);

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

	D3DXMatrixIdentity(&world);
}

void WorldDemo::Destroy()
{
	SafeRelease(vertexBuffer);
	SafeDelete(shader);
}

void WorldDemo::Update()
{
	// x : world._41
	// y : world._42
	// z : world._43
#ifdef MatrixMember
	if (Keyboard::Get()->Press('D'))
		world._41 += 2.f * Time::Delta();
	else if (Keyboard::Get()->Press('A'))
		world._41 -= 2.f * Time::Delta();
	else if (Keyboard::Get()->Press('W'))
		world._42 += 2.f * Time::Delta();
	else if (Keyboard::Get()->Press('S'))
		world._42 -= 2.f * Time::Delta();
#endif // MatrixMember

	static Vector3 position = Vector3(0, 0, 0);
	static Vector3 scale = Vector3(1, 1, 1);

	if (Keyboard::Get()->Press(VK_LSHIFT))
	{
		if (Keyboard::Get()->Press('D'))
			scale.x += 2.f * Time::Delta();
		else if (Keyboard::Get()->Press('A'))
			scale.x -= 2.f * Time::Delta();
		else if (Keyboard::Get()->Press('W'))
			scale.y += 2.f * Time::Delta();
		else if (Keyboard::Get()->Press('S'))
			scale.y -= 2.f * Time::Delta();
	}

	else
	{
		if (Keyboard::Get()->Press('D'))
			position.x += 2.f * Time::Delta();
		else if (Keyboard::Get()->Press('A'))
			position.x -= 2.f * Time::Delta();
		else if (Keyboard::Get()->Press('W'))
			position.y += 2.f * Time::Delta();
		else if (Keyboard::Get()->Press('S'))
			position.y -= 2.f * Time::Delta();
	}

	Matrix S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	world = S * T;

	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void WorldDemo::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	static bool bWireFrame;
	ImGui::Checkbox("WireFrame", &bWireFrame);

	shader->Draw(0, bWireFrame ? 1 : 0, 6);
}